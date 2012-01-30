// DirectoryInfo.h: interface for the CDirectoryInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DirectoryInfo_H__2AE9F41D_5FF6_489A_83AF_156DC1833EFE__INCLUDED_)
#define AFX_DirectoryInfo_H__2AE9F41D_5FF6_489A_83AF_156DC1833EFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirectoryInfo
{
public:
	CDirectoryInfo();
 CDirectoryInfo(const TCHAR * fullname, bool sub);
	CDirectoryInfo(const TCHAR * dir, const TCHAR * parent, bool b) 
	{ 
		Init(dir, parent,b); 
	}
 CDirectoryInfo(const CString & fullname, bool subdirs);

 void Init(const TCHAR *name, const TCHAR * parent,bool subdirs);

	TCHAR  FullPathName[MAX_PATH];
	bool    SubDirs;
};

inline 	CDirectoryInfo::CDirectoryInfo()
{
 FullPathName[0] = 0;
	SubDirs = false; 
}

inline CDirectoryInfo::CDirectoryInfo(const TCHAR * fullname, bool subdirs)
{
	_tcscpy(FullPathName, fullname);
	SubDirs = subdirs;
}

inline CDirectoryInfo::CDirectoryInfo(const CString & fullname, bool subdirs)
{
	_tcscpy(FullPathName, fullname);
	SubDirs = subdirs;
}

inline void CDirectoryInfo::Init(const TCHAR * name, const TCHAR *  parent,bool subdirs)
{
//	PathName = DirName;
 SubDirs = subdirs;

	_tcscpy(FullPathName, parent);
	if ( FullPathName[ _tcslen( FullPathName ) - 1 ] != _T('\\') )  _tcscat(FullPathName, _T("\\") );
	_tcscat(FullPathName,name);
}

#endif // !defined(AFX_DirectoryInfo_H__2AE9F41D_5FF6_489A_83AF_156DC1833EFE__INCLUDED_)
