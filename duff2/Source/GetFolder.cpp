#include "stdafx.h"

#include <Shlobj.h>

#include <objidl.h>
#include <objbase.h>

CString strTmpPath;
//#define BIF_NEWDIALOGSTYLE     0x0040   // Use the new dialog layout with the ability to resize

//#define BIF_NONEWFOLDERBUTTON  0x0200   // Do not add the "New Folder" button to the dialog.  Only applicable with BIF_NEWDIALOGSTYLE.


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	TCHAR szDir[MAX_PATH];

	switch(uMsg)
	{
	case BFFM_VALIDATEFAILED :
		//strcpy(szDir, "");
			SendMessage(hwnd,BFFM_ENABLEOK ,0,0);
		break;
	case BFFM_INITIALIZED:
		if (lpData){
			_tcscpy(szDir, strTmpPath.GetBuffer(strTmpPath.GetLength()));
			SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
		}
		break;
	case BFFM_SELCHANGED: {
	   if (SHGetPathFromIDList((LPITEMIDLIST) lParam ,szDir)){
		  SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
	   }
	   break;
	}
	default:
	   break;
	}
         
	return 0;
}
BOOL GetFolder(CString* strSelectedFolder, const TCHAR* lpszTitle, const HWND hwndOwner, const TCHAR* strRootFolder, const TCHAR* strStartFolder)
{
	TCHAR pszDisplayName[MAX_PATH];
	LPITEMIDLIST lpID;
	BROWSEINFO bi;
	
	bi.hwndOwner = hwndOwner;
	if (strRootFolder == NULL)
	{
		bi.pidlRoot = NULL;
	}
	else
	{
	 LPITEMIDLIST  pIdl = NULL;
	 //IShellFolder* pDesktopFolder;
	 //char          szPath[MAX_PATH];
	 //OLECHAR       olePath[MAX_PATH];
	 //ULONG         chEaten;
	// ULONG         dwAttributes;

	 //strcpy(szPath, (LPCTSTR)strRootFolder);
	 //if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
	 if (SUCCEEDED( SHGetSpecialFolderLocation(NULL,CSIDL_DRIVES ,&pIdl) ))
		{
		// MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1, olePath, MAX_PATH);
	//	 pDesktopFolder->ParseDisplayName(NULL, NULL, olePath, &chEaten, &pIdl, &dwAttributes);
	//	 pDesktopFolder->Release();
	 }
	 bi.pidlRoot = pIdl;
	}
	bi.pszDisplayName = pszDisplayName;
	bi.lpszTitle = lpszTitle;
	bi.ulFlags = BIF_NONEWFOLDERBUTTON | BIF_VALIDATE | BIF_EDITBOX |/* BIF_NEWDIALOGSTYLE |*/ BIF_RETURNONLYFSDIRS ;//| BIF_STATUSTEXT;
	bi.lpfn = BrowseCallbackProc;
	if (strStartFolder == NULL)
	{
		bi.lParam = FALSE;
	}
	else
	{
		strTmpPath.Format( _T("%s") , strStartFolder);
		bi.lParam = TRUE;
	}
	bi.iImage = NULL;
	lpID = SHBrowseForFolder(&bi);
	if (lpID != NULL)
	{
		BOOL b = SHGetPathFromIDList(lpID, pszDisplayName);
		if (b == TRUE)
		{
			strSelectedFolder->Format( _T("%s") ,pszDisplayName);
			return TRUE;
		}
	}
	else
	{
		strSelectedFolder->Empty();
	}
	return FALSE;
}
