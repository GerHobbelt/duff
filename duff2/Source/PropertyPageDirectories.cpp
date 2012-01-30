// DirectoriesPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageDirectories.h"
#include "duffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	#include <sys/stat.h>
#include <afxdisp.h>	// OLE stuff
#include <shlwapi.h>	// Shell functions (PathFindExtension() in this case)
#include <afxpriv.h>	// ANSI to/from Unicode conversion macros

#include "GetFolder.h"


/////////////////////////////////////////////////////////////////////////////
// CDirectoriesPropertyPage property page

IMPLEMENT_DYNCREATE(CDirectoriesPropertyPage, CResizablePage)

CDirectoriesPropertyPage::CDirectoriesPropertyPage() : CResizablePage(CDirectoriesPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CDirectoriesPropertyPage)
	//}}AFX_DATA_INIT
//	m_DuffObjectName = "Directories Property Page";
}

CDirectoriesPropertyPage::~CDirectoriesPropertyPage()
{
}

void CDirectoriesPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectoriesPropertyPage)
	DDX_Control(pDX, IDC_FILE_MASKS, m_FileMasks);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectoriesPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CDirectoriesPropertyPage)
	ON_BN_CLICKED(IDC_BROWSE_INCLUDE, OnBrowseInclude)
	ON_BN_CLICKED(IDC_REMOVE_SELECTED_INCLUDE_DIRECTORY, OnRemoveSelectedIncludeDirectory)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_REMOVE_ALL_DIRECTORIES, OnRemoveAllDirectories)
	ON_BN_CLICKED(IDC_ATTRIBUTES_ANY, OnAttributesAny)
	ON_LBN_DBLCLK(IDC_INCLUDE_DIRECTORIES_LIST, OnDblclkIncludeDirectoriesList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoriesPropertyPage message handlers

BOOL CDirectoriesPropertyPage::OnInitDialog() 
{
	CResizablePage::OnInitDialog();
	
	// preset resize layout	
	AddAnchor(IDC_ATTRIBUTES_LIST,  TOP_LEFT,BOTTOM_LEFT);	
 AddAnchor(IDC_ATTRIBUTES_ANY	,  BOTTOM_LEFT);	
	AddAnchor(IDC_INCLUDE_DIRECTORIES_LIST,  TOP_LEFT,BOTTOM_RIGHT);	
	AddAnchor(IDC_REMOVE_SELECTED_INCLUDE_DIRECTORY,BOTTOM_LEFT);
	AddAnchor(IDC_REMOVE_ALL_DIRECTORIES,BOTTOM_LEFT);
	AddAnchor(IDC_BROWSE_INCLUDE,BOTTOM_LEFT);	
	//

 // subclass listbox to checklistbox
	m_IncludeDirectoriesList.SubclassDlgItem(IDC_INCLUDE_DIRECTORIES_LIST,this);
 //



	m_AttributesList.SubclassDlgItem(IDC_ATTRIBUTES_LIST,this);
	m_AttributesList.AddString( _T(" Hidden") );
	m_AttributesList.AddString( _T(" System") );
	m_AttributesList.AddString( _T(" Read-only") );
	m_AttributesList.AddString( _T(" Archived") );
	m_AttributesList.AddString( _T(" Compressed") );
	m_AttributesList.AddString( _T(" Encrypted") );
 m_AttributesList.SetCheckStyle(BS_AUTO3STATE);

 OnAttributesAny() ;


	// some default values
	m_FileMasks.SetWindowText( _T("*.*") );
	//

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
void CDirectoriesPropertyPage::OnIncludeHidden() 
{
	CString Temp;
	Temp.Format("Directories->Include hidden set to %s", m_IncludeHidden.GetCheck() == BST_CHECKED ? "YES" : "NO");
	((CDuffDlg*)GetParent()->GetParent())->Log(Temp);
	
}

void CDirectoriesPropertyPage::OnIncludeSystem() 
{
	CString Temp;
	Temp.Format("Directories->Include system set to %s", m_IncludeSystem.GetCheck() == BST_CHECKED ? "YES" : "NO");
	((CDuffDlg*)GetParent()->GetParent())->Log(Temp);
	
}

void CDirectoriesPropertyPage::OnIncludeReadonly() 
{
	CString Temp;
	Temp.Format("Directories->Include read-only set to %s", m_IncludeReadOnly.GetCheck() == BST_CHECKED ? "YES" : "NO");
	((CDuffDlg*)GetParent()->GetParent())->Log(Temp);
	
}


void CDirectoriesPropertyPage::OnIncludeArchive() 
{
	CString Temp;
	Temp.Format("Directories->Include archive set to %s", m_IncludeArchived.GetCheck() == BST_CHECKED ? "YES" : "NO");
	((CDuffDlg*)GetParent()->GetParent())->Log(Temp);
	
}

void CDirectoriesPropertyPage::OnIncludeCompressed() 
{
	CString Temp;
	Temp.Format("Directories->Include compressed set to %s", m_IncludeCompressed.GetCheck() == BST_CHECKED ? "YES" : "NO");
	((CDuffDlg*)GetParent()->GetParent())->Log(Temp);
	
}
*/
BOOL CDirectoriesPropertyPage::PreTranslateMessage(MSG* pMsg) 
{
	bool ret;
	if ( IsDialogMessage( pMsg ) )        
	{
		if ( TranslateAccelerator ( GetSafeHwnd(),((CDuffDlg*)GetParent()->GetParent())->m_hAccel,pMsg) )
  {
   TranslateMessage(pMsg); 
   DispatchMessage(pMsg); 
   ret = false;
		}
		ret = true;
	}
	else        
	{
		ret = ( CWnd::PreTranslateMessage( pMsg ) != 0);
	}
	return ret;
}

void CDirectoriesPropertyPage::OnBrowseInclude() 
{
	CString strFolderPath;
	if (GetFolder(&strFolderPath, _T("Browse for folder to include in search") , this->m_hWnd, NULL, NULL) && !strFolderPath.IsEmpty() )
	{
	//	CString Temp;
//	 m_IncludeDirs.GetWindowText(Temp);
//  if (!Temp.IsEmpty()) Temp += "\r\n";
//		Temp += strFolderPath;
//	 m_IncludeDirs.SetWindowText(Temp);


m_IncludeDirectoriesList.AddString(strFolderPath);
		//m_IncDirsList.InsertItem(0,Temp);
	}
}


void CDirectoriesPropertyPage::LoadSettings()
{
	/*
 TCHAR buffer[MAX_PATH + 80];
	CString TempStr;
	DWORD count;

	TempStr.Format( "%d",m_IncludeCompressed.GetCheck() );
	count = GetPrivateProfileString(_T("Directories"),_T("IncludeCompressed"), TempStr,buffer,MAX_PATH+80,"duff.dff");
 switch(buffer[
*/

}

void CDirectoriesPropertyPage::SaveSettings()
{
/*// MessageBox("save settings");
	CString Temp;
Temp.Format("%i",m_IncludeCompressed.GetCheck());
	WriteProfileString("FUNK_MASTA","IncludeCompressed", "Temp");
*/
}



void CDirectoriesPropertyPage::OnRemoveSelectedIncludeDirectory() 
{
	int selcount = m_IncludeDirectoriesList.GetSelCount();
 int count;
	int i;
	if (!selcount) return;

	LPINT SelectedIndexes = new int[selcount];

	count = m_IncludeDirectoriesList.GetSelItems( selcount, SelectedIndexes );

	if ( count == LB_ERR ) 
	{

	delete[] SelectedIndexes;

		return;
	}
	for (i = count-1; i >=0; i--)
	{
   m_IncludeDirectoriesList.DeleteString( SelectedIndexes[i] );
	}

	delete[] SelectedIndexes;

/*

 int Selected = m_IncludeDirectoriesList.GetCurSel();
	if (Selected != LB_ERR )
	{
  m_IncludeDirectoriesList.DeleteString(Selected);
		if ( Selected < m_IncludeDirectoriesList.GetCount() ) m_IncludeDirectoriesList.SetCurSel(Selected);
	}
		*/
}


void CDirectoriesPropertyPage::OnRemoveAllDirectories() 
{
	m_IncludeDirectoriesList.ResetContent();
}

int CDirectoriesPropertyPage::InitDupeFileFind(CDuplicateFileFind & dff)
{
 int i;
 CString TempStr;
 CString strMask;
 int nPos = 0;
 int nNextPos = 0;

	// get dir settings from dlg and save
	dff.IncludeHiddenDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_HIDDEN) );
	dff.IncludeSystemDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_SYSTEM) );
	dff.IncludeReadOnlyDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_READONLY) );
	dff.IncludeCompressedDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_COMPRESSED) );
	dff.IncludeArchivedDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_ARCHIVED) );
 dff.IncludeEncryptedDirs( m_AttributesList.GetCheck(DIR_ATTRIBUTE_ENCRYPTED) );
	//

	
 // Build include directory list
	dff.RemoveAllSearchPaths();
	for (i = 0; i < m_IncludeDirectoriesList.GetCount(); i++)
	{
		m_IncludeDirectoriesList.GetText(i,TempStr);
		dff.AddSearchPath(TempStr, m_IncludeDirectoriesList.GetCheck(i) == BST_CHECKED);
	}
	//


 
 
 // add file masks
 dff.RemoveAllFileMasks();
	m_FileMasks.GetWindowText(TempStr);
 while (nPos < TempStr.GetLength()) 
	{
  nNextPos = TempStr.Find( _T(";") ,nPos);
  if (nNextPos == -1) nNextPos = TempStr.GetLength();
  strMask = TempStr.Mid(nPos, nNextPos-nPos);
  strMask.TrimLeft();
  strMask.TrimRight();
  if (strMask != "") dff.AddFileMask(strMask);
  nPos = nNextPos + 1;
 }
 //
	
	if ( TempStr.IsEmpty() || m_IncludeDirectoriesList.GetCount() == 0 )
	{
		return 0;
	}
	else
		return -1;
	
}




	enum DLDropFlags
	{
		DL_ACCEPT_FILES =       0x01,	// Allow files to be dropped
		DL_ACCEPT_FOLDERS =		0x02,	// Allow folders to be droppped
		DL_ALLOW_DUPLICATES =	0x04,	// Allow a pathname to be dropped even if its already in the list (ignored if you specify a callback function)
		DL_FILTER_EXTENSION =	0x10,	// Only accept files with the specified extension. Specify in csFileExt
		DL_USE_CALLBACK =		0x20,	// Receive a callback for each item dropped, specified in pfnCallback (you have responsibility for inserting items into the list)

		DL_FOLDER_TYPE =		0x40,	// Returned to the callback function - indicating the type of path dropped
		DL_FILE_TYPE =			0x80
	};




//////////////////////////////////////////////////////////////////
//
//	ValidatePathname()
//
//	Checks if a pathname is valid based on these options set:
//		Allow directories to be dropped
//		Allow files to be dropped
//		Only allow files with a certain extension to be dropped
//
//	Return value:
//		TRUE:	the pathname is suitable for selection, or
//		FALSE:	the pathname failed the checks.
//
//		If successful, iPathType specifies the type of path
//		validated - either a file or a folder.

BOOL CDirectoriesPropertyPage::ValidatePathname(const CString& csPathname, UINT& /*iPathType*/) const
{
	CFileFind ff;
 bool bValid;

	if ( ff.FindFile(csPathname) )
	{
		ff.FindNextFile();
		bValid = ff.IsDirectory() != 0;
	}
	else
	{
  bValid = false;
	}

	return bValid;
}



void CDirectoriesPropertyPage::OnDropFiles(HDROP dropInfo)
{
	//
	// Get the number of pathnames (files or folders) dropped
	//
	UINT nNumFilesDropped = DragQueryFile(dropInfo, 0xFFFFFFFF, NULL, 0);


	UINT  m_dropMode = DL_ACCEPT_FOLDERS;

	//
	// Iterate through the pathnames and process each one
	//
	TCHAR szFilename[MAX_PATH + 1];
	CString csPathname;
	CString csExpandedFilename;

	for (UINT nFile = 0 ; nFile < nNumFilesDropped; nFile++)
	{
		//
		// Get the pathname
		//
		DragQueryFile(dropInfo, nFile, szFilename, MAX_PATH + 1);

		//
		// It might be shortcut, so try and expand it
		//
		csPathname = szFilename;
		csExpandedFilename = ExpandShortcut(csPathname);
		if(!csExpandedFilename.IsEmpty())
		{
			csPathname = csExpandedFilename;
		}


		//
		// Now see if its something we allow to be dropped
		//
		UINT iPathType = 0;
		if(ValidatePathname(csPathname, iPathType))
		{
			//
			// By default, we insert the filename into the list
			// ourselves, but if our parent wants to do something flashy
			// with it (maybe get the filesize and insert that as an extra
			// column), they will have installed a callback for each
			// droppped item
			//
			if(m_dropMode & DL_USE_CALLBACK)
			{
				//
				// Let them know about this list control and the item
				// droppped onto it
				//
				//if(m_dropMode.pfnCallback)
				//	m_dropMode.pfnCallback(this, csPathname, iPathType);
			}
			else
			{
				m_IncludeDirectoriesList.AddString(csPathname);
			}
		}
	}


	//
	// Free the dropped-file info that was allocated by windows
	//
	DragFinish(dropInfo);
}




//////////////////////////////////////////////////////////////////
//
//	ExpandShortcut()
//
//	Uses IShellLink to expand a shortcut.
//
//	Return value:
//		the expanded filename, or "" on error or if filename
//		wasn't a shortcut
//
//	Adapted from CShortcut, 1996 by Rob Warner
//	rhwarner@southeast.net
//	http://users.southeast.net/~rhwarner

CString CDirectoriesPropertyPage::ExpandShortcut(CString& csFilename) const
{
	USES_CONVERSION;		// For T2COLE() below
	CString csExpandedFile;

	//
    // Make sure we have a path
	//
	if(csFilename.IsEmpty())
	{
		ASSERT(FALSE);
		return csExpandedFile;
	}

	//
    // Get a pointer to the IShellLink interface
	//
    HRESULT hr;
    IShellLink* pIShellLink;

    hr = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
							IID_IShellLink, (LPVOID*) &pIShellLink);

    if (SUCCEEDED(hr))
    {

		//
        // Get a pointer to the persist file interface
		//
		IPersistFile* pIPersistFile;
        hr = pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pIPersistFile);

        if (SUCCEEDED(hr))
        {
			//
            // Load the shortcut and resolve the path
			//
            // IPersistFile::Load() expects a UNICODE string
			// so we're using the T2COLE macro for the conversion
			//
			// For more info, check out MFC Technical note TN059
			// (these macros are also supported in ATL and are
			// so much better than the ::MultiByteToWideChar() family)
			//
            hr = pIPersistFile->Load(T2COLE(csFilename), STGM_READ);
			
			if (SUCCEEDED(hr))
			{
				WIN32_FIND_DATA wfd;
				hr = pIShellLink->GetPath(csExpandedFile.GetBuffer(MAX_PATH),
										  MAX_PATH,
										  &wfd,
										  SLGP_UNCPRIORITY);

				csExpandedFile.ReleaseBuffer(-1);
            }
            pIPersistFile->Release();
        }
        pIShellLink->Release();
    }

    return csExpandedFile;
}



void CDirectoriesPropertyPage::OnAttributesAny() 
{
 for (register int i = 0; i < m_AttributesList.GetCount(); i++)
	{
		m_AttributesList.SetCheck(i,BST_INDETERMINATE);
	}	
}

void CDirectoriesPropertyPage::OnDblclkIncludeDirectoriesList() 
{
	CString strFolderPath;
	CString strOldPath;

	m_IncludeDirectoriesList.GetText(m_IncludeDirectoriesList.GetCurSel(), strOldPath);

	if (GetFolder(&strFolderPath, _T("Browse for folder to include in search") , this->m_hWnd, NULL, strOldPath) && !strFolderPath.IsEmpty() )
	{
		int index = m_IncludeDirectoriesList.GetCurSel();
  m_IncludeDirectoriesList.InsertString( index, strFolderPath);
  m_IncludeDirectoriesList.DeleteString( index+1);
  m_IncludeDirectoriesList.SetCurSel(index);

	}
	
}
