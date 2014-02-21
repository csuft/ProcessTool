#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

typedef struct _procEntry
{
	string procName;
	unsigned int procId;    // process id
	unsigned int procPid;   // parent process id
	unsigned short ctThread; // thread count
	unsigned int priorBase;
	unsigned int priorClass;
}ProcEntry, *pProcEntry;

typedef struct _appEntry
{
	string appName;
	string appVer;
	string installDate;
	string location;
	string publisher;
}AppEntry, *pAppEntry;

class RetrieveHelper
{
public:
	RetrieveHelper(void);
	~RetrieveHelper(void);

	const vector<AppEntry>& getApplist() const { return m_appList; }
	const vector<ProcEntry>& getProclist() const { return m_procList; }
private:
	RetrieveHelper& operator=(const RetrieveHelper& obj);
	RetrieveHelper(const RetrieveHelper& obj);

	void setApplist();
	void setProclist();

	void retrieveAppkey(HKEY hKey, LPCTSTR szDesKeyItem, LONG flag);
	BOOL determineOSBit();
private:
	vector<AppEntry> m_appList;
	vector<ProcEntry> m_procList;
};

