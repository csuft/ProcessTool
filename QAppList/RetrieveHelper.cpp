#include "RetrieveHelper.h"
#include <WinError.h>

RetrieveHelper::RetrieveHelper(void)
{
	setApplist();
	setProclist();
}

RetrieveHelper::~RetrieveHelper(void)
{

}
/*
 * Retrieve the list of software installed.
 * Flags: KEY_WOW64_64KEY, KEY_WOW64_32KEY 
 */
void RetrieveHelper::setApplist()
{
	if (determineOSBit())  // the windows is 64bit
	{
		retrieveAppkey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_WOW64_32KEY);
	}
	// KEY_WOW64_64KEY will be ignored by 32bit windows.
	retrieveAppkey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_WOW64_64KEY);
}
/*
 * Retrieve the list of process running
 */
void RetrieveHelper::setProclist()
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;
	ProcEntry entry;
	TCHAR buffer[MAX_PATH];

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
	{
		return;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		CloseHandle( hProcessSnap );          // clean the snapshot object
		return ;
	}

	do
	{
		entry.procName = pe32.szExeFile ;
		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
		if(hProcess)
		{
			dwPriorityClass = GetPriorityClass(hProcess);
			CloseHandle( hProcess );
		}

		entry.procId =  pe32.th32ProcessID;
		entry.ctThread = pe32.cntThreads;
		entry.procPid = pe32.th32ParentProcessID;
		entry.priorBase = pe32.pcPriClassBase;
		if( dwPriorityClass )
			entry.priorClass = dwPriorityClass;
		m_procList.push_back(entry);

	} while( Process32Next( hProcessSnap, &pe32 ) );
}

/*
 * To determine whether we are running under Wow64
 * Returns: returns true if process running on Wow64.
 */
BOOL RetrieveHelper::determineOSBit()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	BOOL bIsWow64 = false; // assume 32 bit

	// can't call IsWow64Process on x32, so first look up the entry point in kernel32
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
	// if we have an entry point for IsWow64Process, we can call it
	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			bIsWow64 = FALSE;
		}
	}
	return bIsWow64;
}

/*
 * Enumerate the default registry key.
 * For Windows 32bit and 64bit, the default registry path is:
 *   HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall
 * While running under Windows 64bits, all 32bits applications are registered under:
 *   HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall
 */
void RetrieveHelper::retrieveAppkey(HKEY hKey, LPCTSTR szDesKeyItem, LONG flag)
{
	AppEntry entry;
	HKEY hSubKey;
	DWORD dwIndex = 0;
	long lResult;
	const unsigned int BUFSIZE = 1024;
	TCHAR s_name[256] = {0};				// application name			
	TCHAR buffer[BUFSIZE] = {'\0'};
	DWORD cbName = BUFSIZE*sizeof(TCHAR);	
	DWORD typeSZ = REG_SZ;	
	HKEY hItem;		// next level

	lResult = RegOpenKeyEx(hKey, szDesKeyItem, 0, KEY_READ|flag, &hSubKey);		// Open windows registry
	if(ERROR_SUCCESS == lResult) 
	{
		lResult = RegEnumKeyEx(hSubKey, dwIndex, s_name, &cbName, 0, NULL, NULL, NULL);		// enumerate keys
		while (lResult == ERROR_SUCCESS && lResult != ERROR_MORE_DATA)
		{
			cbName = BUFSIZE*sizeof(TCHAR);  // reset the value
			if(RegOpenKeyEx(hSubKey, s_name, 0, KEY_READ, &hItem) == ERROR_SUCCESS)
			{
				// the display name of application
				lResult = RegQueryValueEx(hItem, TEXT("DisplayName"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
				if (lResult == ERROR_SUCCESS)  // the registry value exist, so we continue
				{
					entry.appName = buffer;
					memset(buffer, 0, BUFSIZE);
					cbName = BUFSIZE*sizeof(TCHAR);
					// the publisher
					lResult = RegQueryValueEx(hItem, TEXT("Publisher"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.publisher = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.publisher = TEXT("/");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// Get the location of installation
					lResult = RegQueryValueEx(hItem, TEXT("InstallLocation"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.location = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.location = TEXT("/");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// installation date
					lResult = RegQueryValueEx(hItem, TEXT("InstallDate"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.installDate = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.installDate = TEXT("N/A");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// display version of application
					lResult = RegQueryValueEx(hItem, TEXT("DisplayVersion"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.appVer = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.appVer = TEXT("/");
					}
					m_appList.push_back(entry);
				}
				RegCloseKey(hItem);
			}

			dwIndex = dwIndex + 1;			// move to the next key
			cbName = BUFSIZE*sizeof(TCHAR);
			lResult = RegEnumKeyEx(hSubKey, dwIndex, s_name, &cbName, 0, NULL, NULL, NULL);
		}
		RegCloseKey(hSubKey);
	}
	RegCloseKey(hKey);
}