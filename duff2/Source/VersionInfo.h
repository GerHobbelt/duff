// VersionInfo.h 
 
#ifndef VERSIONINFO_H
#define VERSIONINFO_H 
#include "stdafx.h"
class CVersionInfo
{
public:
	CString m_strVersionInfo;
	CString m_strFixedFileVersion;
	CString m_strFixedProductVersion;
	CVersionInfo ();
	~CVersionInfo ();
	CVersionInfo (HMODULE hModule, LPCTSTR strLangID = NULL, LPCTSTR strInfoType = NULL);
	CVersionInfo (LPTSTR szFilename, LPCTSTR strLangID = NULL, LPCTSTR strInfoType = NULL);
	void GetVersionInfo (LPTSTR szFilename, LPCTSTR strLangID = NULL, LPCTSTR strInfoType = NULL);
	void GetVersionInfo (HMODULE hModule, LPCTSTR strLangID = NULL, LPCTSTR strInfoType = NULL);
}; 

#endif // VERSIONINFO_H
