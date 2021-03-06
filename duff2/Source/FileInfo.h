// FileInfo.h: interface for the CFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINFO_H__FA8991ED_8BDB_471F_95F2_CE4CEA45EE44__INCLUDED_)
#define AFX_FILEINFO_H__FA8991ED_8BDB_471F_95F2_CE4CEA45EE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxdisp.h>
#include <afxtempl.h>
#include "defines.h"
#include "util.h"

// all data is public to increase data access speed, so be careful!
class CFileInfo : public CObject
{
	DECLARE_DYNAMIC(CFileInfo);

public:
	CFileInfo();
	CFileInfo(const CFileInfo &);
 CFileInfo(const TCHAR *, const WIN32_FIND_DATA & , const VS_FIXEDFILEINFO &);
 CFileInfo(const TCHAR *, const WIN32_FIND_DATA &);
 virtual ~CFileInfo();

 CFileInfo & operator = ( CFileInfo & );
 CFileInfo & Copy(const CFileInfo &);
 void Init(const TCHAR *, const WIN32_FIND_DATA & , const VS_FIXEDFILEINFO &);
 void Init(const TCHAR* ParentDir, const WIN32_FIND_DATA & fd);

 CString GetParentDirName() const;

	CString GetFileVersionStr() ;
	void InitVersion();

	// from WIN32_FIND_DATA
 DWORD      Attributes;

 inline bool IsDirectory() const
 {
	 return 0 != (Attributes & FILE_ATTRIBUTE_DIRECTORY);
 }
 inline bool IsRegularFile() const
 {
	 return 0 == (Attributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_VIRTUAL));
 }

 COleDateTime   TimeCreated;
 COleDateTime   TimeLastAccessed;
 COleDateTime   TimeLastModified;
	ULONGLONG  Size;
	DWORD      Reserved0;
 DWORD      Reserved1;

	inline void SetFullName(LPCTSTR ParentDir, LPCTSTR filename)
	{
		// copy parent directory name to full file path name
		_FullName = ParentDir;

		// append a \ if nesessary
		if ( _FullName[ _tcslen(ParentDir) -1 ] != _T('\\') ) _FullName += _T("\\");

		// set the pointer to the filename
		_Name = _FullName.GetLength();

		// append the filename to the end of the parent directory name
		_FullName += filename;

		// set the pointer to the extension
		LPCTSTR ext = _tcsrchr(filename, '.');
		if (ext)
		{
			_Extension = _Name + (ext - filename) + 1; // set pointer to first character in extension, instead of the period ( so Extenstion is "TXT" instead of ".TXT" )
		}
		else
		{
			_Extension = 0;
		}
	}
	inline const CString &GetFullName() const
	{
		return _FullName;
	}
	// return the path / directory component with trailing '\\'
	inline CString GetDirPath() const 
	{
		CString rv = (_Name >= 0 ? _FullName.Left(_Name) : _FullName);
		return rv;
	}
	inline LPCTSTR GetName() const 
	{
		return _Name >= 0 ? _FullName.GetString() + _Name : NULL;
	}
	inline LPCTSTR GetExtension() const
	{
		return _Extension > 0 ? _FullName.GetString() + _Extension : NULL;
	}
	// return only the filename  without extension
	inline CString GetBaseName() const
	{
		CString rv = (_Name >= 0 ? _Extension > 0 ? _FullName.Mid(_Name, _Extension - _Name - 1) : _FullName.Mid(_Name) : NULL_STR);
		return rv;
	}

private:
	CString      _FullName;
	int _Name;
	int _Extension;

public:
	// from VS_FIXEDFILEINFO
	bool  VersionDataIsValid;
 DWORD VersionSignature;
 DWORD VersionStrucVersion;
 QWORD VersionFile;
	QWORD VersionProduct;
	DWORD VersionFlagsMask;
 DWORD VersionFlags;
 DWORD VersionOS;
 DWORD VersionType;
 DWORD VersionSubtype;
 DWORD VersionDateMS;
 DWORD VersionDateLS;

	// unique
	bool     FirstFile;
	bool     Duplicate;
	bool     Selected;
	bool     Unaccessible;

	UINT     SetID;

	// shell verbs
	struct sShellVerb
	{
		CString Name;
		CString Command;
	};

	CArray< sShellVerb, sShellVerb & > ShellVerbs;
 bool ShellVerbsValid;

	void InitShellVerbs();

CString TypeString;


 bool OpenedBefore;

#ifdef _DEBUG
 static UINT GetCount() { return Count; }
#endif

private:

#ifdef _DEBUG
 static UINT Count;
#endif

public:

#if defined(_DEBUG) || defined(_AFXDLL)
	// Diagnostic Support
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

#endif // !defined(AFX_FILEINFO_H__FA8991ED_8BDB_471F_95F2_CE4CEA45EE44__INCLUDED_)


inline void CFileInfo::InitShellVerbs()
{
 sShellVerb sv;
 CString RegKeyName;
	CString TypeStringShort;
	if ( GetExtension() )
	{
		HKEY hkey;
		HKEY hkey2;

		int Ret, Ret2;
		RegKeyName.Format( _T(".%s"), GetExtension() );
		Ret = RegOpenKeyEx(HKEY_CLASSES_ROOT ,RegKeyName,0,KEY_QUERY_VALUE,&hkey);
		if ( Ret == ERROR_SUCCESS )
		{
 	 BYTE buffer [ MAX_PATH + 1];
   DWORD Size = MAX_PATH;
			DWORD RecvSize;
 		DWORD Type;
   FILETIME ft;
   RecvSize = Size;
			Ret = RegQueryValueEx(hkey,_T(""),0,&Type,buffer, &RecvSize);
			if (Ret == ERROR_SUCCESS)
			{
				RegCloseKey(hkey);
 			TypeStringShort = buffer;

				// get the full type name
  		Ret = RegOpenKeyEx(HKEY_CLASSES_ROOT ,TypeStringShort,0,KEY_QUERY_VALUE,&hkey);
				if ( Ret == ERROR_SUCCESS )
				{
					RecvSize = Size;
					Ret = RegQueryValueEx(hkey,_T(""),0,&Type,buffer, &RecvSize);
					if ( Ret == ERROR_SUCCESS)
						TypeString = buffer;
					RegCloseKey(hkey);
				}
    //

				// now look up the object shell key
		  RegKeyName.Format( _T("%s\\shell"), TypeStringShort );
  		Ret = RegOpenKeyEx(HKEY_CLASSES_ROOT ,RegKeyName,0,KEY_QUERY_VALUE| KEY_ENUMERATE_SUB_KEYS,&hkey);
  		if ( Ret == ERROR_SUCCESS )
				{
					int iIndex = 0;
					do
					{
								RecvSize = Size;

						Ret = RegEnumKeyEx(hkey, iIndex, (TCHAR*)buffer, &RecvSize, NULL, NULL, NULL, &ft);
						if (Ret == ERROR_SUCCESS)
	  			{
	 	   	sv.Name = buffer;
   		  RegKeyName.Format( _T("%s\\shell\\%s\\command"), TypeStringShort, (TCHAR*)buffer );
     		Ret2 = RegOpenKeyEx(HKEY_CLASSES_ROOT ,RegKeyName,0,KEY_QUERY_VALUE ,&hkey2);
    		 if ( Ret2 == ERROR_SUCCESS )
						 {
								sv.Name = buffer;
								RecvSize = Size;
  		  	 Ret2 = RegQueryValueEx(hkey2,_T(""),0,&Type,buffer, &RecvSize);
  		    if ( Ret2 == ERROR_SUCCESS )
								{

									sv.Command = buffer;
									ShellVerbs.Add(sv);
         RegCloseKey(hkey2);
								}

						else
						{
							TRACE1("%s\n",GetErrorStr(Ret));
						}

							}

						}
						else
						{
							TRACE1("%s\n",GetErrorStr(Ret));
							RegCloseKey(hkey);
						}
						iIndex++;
					}
     while ( Ret == ERROR_SUCCESS );

				}

			}
			else
			{
				RegCloseKey(hkey);
			}
		}


	}
	if ( !TypeString.GetLength() ) TypeString.Format( _T("%s File"), (GetExtension() ? GetExtension() : _T("???")));

 ShellVerbsValid = true;
}

inline CString CFileInfo::GetParentDirName() const
{
	CString DirName = GetFullName();
	DirName = DirName.Left(_Name);
	return DirName;
}

inline CFileInfo::CFileInfo()
{

	Attributes       = NULL;
 //TimeCreated      = 0;
 //TimeLastAccessed = 0;
 //TimeLastModified = 0;
	Size             = 0;
	Reserved0        = NULL;
 Reserved1        = NULL;

 _FullName = NULL_STR;
 _Name        = -1;
	_Extension   = 0;

 ////
 VersionDataIsValid  = false;
 VersionSignature    = 0;
 VersionStrucVersion = 0;
 VersionFile         = 0;
 VersionProduct      = 0;
 VersionFlagsMask    = 0;
 VersionFlags        = 0;
 VersionOS           = 0;
 VersionType         = 0;
 VersionSubtype      = 0;
 VersionDateMS       = 0;
 VersionDateLS       = 0;

	////

	FirstFile    = false;
	Duplicate    = false;
 Selected     = false;
	Unaccessible = false;

	ShellVerbs.RemoveAll();
	ShellVerbsValid = false;

	OpenedBefore = false;
}

inline CFileInfo::CFileInfo(const CFileInfo & fi)
{
	#ifdef _DEBUG
	Count++;
	#endif

	Copy(fi);
}

inline  CFileInfo::CFileInfo(const TCHAR * ParentDir, const WIN32_FIND_DATA & fd, const VS_FIXEDFILEINFO & ver)
{
	#ifdef _DEBUG
	Count++;
	#endif

	Init(ParentDir,fd,ver);
}

inline  CFileInfo::CFileInfo(const TCHAR * ParentDir, const WIN32_FIND_DATA & fd)
{
	#ifdef _DEBUG
	Count++;
	#endif

	Init(ParentDir,fd);
}

inline CFileInfo & CFileInfo::operator = ( CFileInfo & fi)
{
	return Copy(fi);
}

inline CFileInfo & CFileInfo::Copy(const CFileInfo & fi)
{
	// simply copy all info
Attributes = fi.Attributes;
TimeCreated = fi.TimeCreated;
TimeLastAccessed = fi.TimeLastAccessed;
TimeLastModified = fi.TimeLastModified;
Size = fi.Size;
Reserved0 = fi.Reserved0;
Reserved1 = fi.Reserved1;
_FullName = fi._FullName;
_Name = fi._Name;
_Extension = fi._Extension;
VersionDataIsValid = fi.VersionDataIsValid;
VersionSignature = fi.VersionSignature;
VersionStrucVersion = fi.VersionStrucVersion;
VersionFile = fi.VersionFile;
VersionProduct = fi.VersionProduct;
VersionFlagsMask = fi.VersionFlagsMask;
VersionFlags = fi.VersionFlags;
VersionOS = fi.VersionOS;
VersionType = fi.VersionType;
VersionSubtype = fi.VersionSubtype;
VersionDateMS = fi.VersionDateMS;
VersionDateLS = fi.VersionDateLS;
FirstFile = fi.FirstFile;
Duplicate = fi.Duplicate;
Selected = fi.Selected;
Unaccessible = fi.Unaccessible;
SetID = fi.SetID;

ShellVerbs.Copy(fi.ShellVerbs);
ShellVerbsValid = fi.ShellVerbsValid;

TypeString = fi.TypeString;
OpenedBefore = fi.OpenedBefore;

	return (*this);
}




inline void CFileInfo::Init(const TCHAR* ParentDir, const WIN32_FIND_DATA & fd, const VS_FIXEDFILEINFO & ver)
{

	Attributes       = fd.dwFileAttributes;
 TimeCreated      = COleDateTime(fd.ftCreationTime);
 TimeLastAccessed = COleDateTime(fd.ftLastAccessTime);
 TimeLastModified = COleDateTime(fd.ftLastWriteTime);
	Size             = (fd.nFileSizeHigh * MAXDWORD) + fd.nFileSizeLow;
	Reserved0      = fd.dwReserved0;
 Reserved1      = fd.dwReserved1;

 SetFullName(ParentDir, fd.cFileName);

	SetID = 0;

	////

 VersionDataIsValid           = true;
 VersionSignature             = ver.dwSignature;
 VersionStrucVersion          = ver.dwStrucVersion;
 ((DWORD*)&VersionFile)[0]    = ver.dwFileVersionMS;
 ((DWORD*)&VersionFile)[1]    = ver.dwFileVersionLS;
 ((DWORD*)&VersionProduct)[0] = ver.dwProductVersionMS;
 ((DWORD*)&VersionProduct)[1] = ver.dwProductVersionLS;
 VersionFlagsMask             = ver.dwFileFlagsMask;
 VersionFlags                 = ver.dwFileFlags;
 VersionOS                    = ver.dwFileOS;
 VersionType                  = ver.dwFileType;
 VersionSubtype               = ver.dwFileSubtype;
 VersionDateMS                = ver.dwFileDateMS;
 VersionDateLS                = ver.dwFileDateLS;

	////

	FirstFile    = false;
	Duplicate    = false;
 Selected     = false;
	Unaccessible = false;

	ShellVerbs.RemoveAll();
	ShellVerbsValid = false;

OpenedBefore = false;
}



inline void CFileInfo::Init(const TCHAR* ParentDir, const WIN32_FIND_DATA & fd)
{
	Attributes       = fd.dwFileAttributes;
 TimeCreated      = fd.ftCreationTime;
 TimeLastAccessed = fd.ftLastAccessTime;
 TimeLastModified = fd.ftLastWriteTime ;  // crash here


 Size             = (fd.nFileSizeHigh * MAXDWORD) + fd.nFileSizeLow;
	Reserved0      = fd.dwReserved0;
 Reserved1      = fd.dwReserved1;

 SetFullName(ParentDir, fd.cFileName);

	SetID = 0;

	// speed hack: don't read version info here
 //InitVersion();

	////
 VersionDataIsValid  = false;
 VersionSignature    = 0;
 VersionStrucVersion = 0;
 VersionFile         = 0;
 VersionProduct      = 0;
 VersionFlagsMask    = 0;
 VersionFlags        = 0;
 VersionOS           = 0;
 VersionType         = 0;
 VersionSubtype      = 0;
 VersionDateMS       = 0;
 VersionDateLS       = 0;

	////

	FirstFile    = false;
	Duplicate    = false;
 Selected     = false;
	Unaccessible = false;

		ShellVerbs.RemoveAll();
	ShellVerbsValid = false;

OpenedBefore = false;

}

#define WORD1(SomeQword) (((WORD*)&SomeQword)[0])
#define WORD2(SomeQword) (((WORD*)&SomeQword)[1])
#define WORD3(SomeQword) (((WORD*)&SomeQword)[2])
#define WORD4(SomeQword) (((WORD*)&SomeQword)[3])


inline CString CFileInfo::GetFileVersionStr()
{
	CString			  m_strFixedFileVersion;

	if ( !VersionDataIsValid)
	{
  InitVersion();
	}

	if ( VersionFile )
 	m_strFixedFileVersion.Format ( _T("%u.%u.%u.%u"),HIWORD (((DWORD*)&VersionFile)[1]),LOWORD (((DWORD*)&VersionFile)[1]), HIWORD (((DWORD*)&VersionFile)[0]),LOWORD (((DWORD*)&VersionFile)[0]));
	else
	 m_strFixedFileVersion = _T("");

	return m_strFixedFileVersion;
}

inline void CFileInfo::InitVersion()
{
	DWORD dwVerInfoSize;
	DWORD dwHnd;
	void* pBuffer;
	VS_FIXEDFILEINFO *pFixedInfo; // pointer to fixed file info structure
//	LPVOID  lpVersion;    // String pointer to 'version' text
	UINT    uVersionLen;   // Current length of full version string
//	TCHAR szGetName[500];
	 dwVerInfoSize = GetFileVersionInfoSize(GetFullName(), &dwHnd);
	 if (dwVerInfoSize)
	{
		  pBuffer = malloc(dwVerInfoSize);
		  if (pBuffer == NULL)
			   return;
		  GetFileVersionInfo(GetFullName(), dwHnd, dwVerInfoSize, pBuffer);
		  // get the fixed file info (language-independend)
		  VerQueryValue(pBuffer,_T("\\"),(void**)&pFixedInfo,(UINT *)&uVersionLen);

				/*
				m_strFixedProductVersion.Format ("%u,%u,%u,%u", HIWORD (pFixedInfo->dwProductVersionMS),
			              LOWORD (pFixedInfo->dwProductVersionMS),
			              HIWORD (pFixedInfo->dwProductVersionLS),
			              LOWORD (pFixedInfo->dwProductVersionLS));
		  m_strFixedFileVersion.Format ("%u,%u,%u,%u",HIWORD (pFixedInfo->dwFileVersionMS),
			             LOWORD (pFixedInfo->dwFileVersionMS),
			             HIWORD (pFixedInfo->dwFileVersionLS),
			             LOWORD (pFixedInfo->dwFileVersionLS));
				*/
			((DWORD*)&VersionProduct)[1] =	pFixedInfo->dwProductVersionMS;
			((DWORD*)&VersionProduct)[0] =	pFixedInfo->dwProductVersionLS;
 		((DWORD*)&VersionFile)[1]    =	pFixedInfo->dwFileVersionMS;
			((DWORD*)&VersionFile)[0]    =	pFixedInfo->dwFileVersionLS;

/*
		  // get the string file info (language-dependend)
		  if (strLangID != NULL || strInfoType != NULL)
		  {
			   lstrcpy(szGetName, "\\StringFileInfo\\");
			   lstrcat (szGetName, strLangID);
			   lstrcat (szGetName, "\\");
			   lstrcat (szGetName, strInfoType);
			   // copy version info, if desired entry exists
			   if (VerQueryValue(pBuffer,szGetName,(void**)&lpVersion,(UINT *)&uVersionLen) != 0)
				    m_strVersionInfo = (LPTSTR)lpVersion;
		  }
				*/
		  if (pBuffer != NULL)
			   free(pBuffer);
	}
		else
		{
		// m_strVersionInfo = "None";
	//  m_strFixedFileVersion = "None";
	//  m_strFixedProductVersion = "None";

		}
		VersionDataIsValid = true;
}

