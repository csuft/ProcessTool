#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "Psapi.lib")

using std::map;
using std::vector;
using std::string;
using std::wstring;

typedef struct _procEntry
{
	wstring procName;
	unsigned int procId;    // process id
	unsigned int procPid;   // parent process id
	unsigned short ctThread; // thread count
	unsigned int priorBase;
	unsigned int priorClass;
	wstring exePath;
}ProcEntry, *pProcEntry;

typedef struct _appEntry
{
	wstring appName;
	wstring appVer;
	wstring installDate;
	wstring location;
	wstring publisher;
}AppEntry, *pAppEntry;

typedef struct _moduleEntry
{
	DWORD glblcntUsage;
	DWORD proccntUsage;
	BYTE* modBaseAddr;
	DWORD modBaseSize;
	wstring modName;
	wstring exePath;
}ModuleEntry, *pModuleEntry;

class RetrieveHelper
{
public:
	RetrieveHelper(void);
	~RetrieveHelper(void);

	const vector<AppEntry>& getApplist() const { return m_appList; }
	const vector<ProcEntry>& getProclist() const { return m_procList; }
	const vector<ModuleEntry> getFullModules(unsigned int pid); 
private:
	RetrieveHelper& operator=(const RetrieveHelper& obj);
	RetrieveHelper(const RetrieveHelper& obj);

	void setApplist();
	void setProclist();
	bool RetrieveHelper::NormalizeNTPath(wchar_t* pszPath, size_t nMax);
	void retrieveAppkey(HKEY hKey, LPCTSTR szDesKeyItem, LONG flag);
	BOOL determineOSBit();
private:
	vector<AppEntry> m_appList;
	vector<ProcEntry> m_procList;
};

