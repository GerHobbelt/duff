// FilenameEdit.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "FilenameEdit.h"
#include "GetFolder.h"
#include "TextClipboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "defines.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit

CFilenameEdit::CFilenameEdit()
{
	m_EditType = ET_FOLDER;
	m_EnableMultipleSelections = false;
	m_ActionType = AT_READ;
}

CFilenameEdit::~CFilenameEdit()
{
}


BEGIN_MESSAGE_MAP(CFilenameEdit, CEdit)
	//{{AFX_MSG_MAP(CFilenameEdit)
	ON_WM_DROPFILES()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit message handlers

void CFilenameEdit::PreSubclassWindow() 
{
	ModifyStyle(NULL,WS_EX_ACCEPTFILES);
 m_PopupMenu.CreatePopupMenu();
 
 m_PopupMenu.InsertMenu(0, MF_BYPOSITION | MF_STRING    ,  1, StringFromResource(IDS_FILENAMEEDIT_BROWSE) );
 m_PopupMenu.InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR ,  2, NULL_STR );
 m_PopupMenu.InsertMenu(2, MF_BYPOSITION | MF_STRING    ,  3, StringFromResource(IDS_FILENAMEEDIT_UNDO) );
 m_PopupMenu.InsertMenu(3, MF_BYPOSITION | MF_SEPARATOR ,  4, NULL_STR );
	m_PopupMenu.InsertMenu(4, MF_BYPOSITION | MF_STRING    ,  5, StringFromResource(IDS_FILENAMEEDIT_CUT) );
 m_PopupMenu.InsertMenu(5, MF_BYPOSITION | MF_STRING    ,  6, StringFromResource(IDS_FILENAMEEDIT_COPY) );
 m_PopupMenu.InsertMenu(6, MF_BYPOSITION | MF_STRING    ,  7, StringFromResource(IDS_FILENAMEEDIT_PASTE) );
 m_PopupMenu.InsertMenu(7, MF_BYPOSITION | MF_STRING    ,  8, StringFromResource(IDS_FILENAMEEDIT_DELETE) );
 m_PopupMenu.InsertMenu(8, MF_BYPOSITION | MF_SEPARATOR ,  9, NULL_STR );
 m_PopupMenu.InsertMenu(9, MF_BYPOSITION | MF_STRING    , 10, StringFromResource(IDS_FILENAMEEDIT_SELECT_ALL) );

	CEdit::PreSubclassWindow();
}



void CFilenameEdit::AddFileType(CFileType & ft)
{
	m_FileTypes.Add(ft);

	if ( ft.Default )
	{
  for( int i = 0; i < m_FileTypes.GetSize()-1; i++)
		{
			m_FileTypes.ElementAt(i).Default = false;
		}
	}

}

LPCTSTR CFilenameEdit::GetDefaultExt()
{
 /*
	for( int i = 0; i < m_FileTypes.GetSize()-1; i++)
	{
	 if ( m_FileTypes.ElementAt(i).Default ) return 	
	}
	*/
	if ( m_DefaultExt.IsEmpty() )
  return NULL;
	else
  return m_DefaultExt;
}

CString CFilenameEdit::GetFilter()
{
 CString Filter;

	for( int i = 0; i < m_FileTypes.GetSize(); i++)
	{
	 Filter += m_FileTypes.ElementAt(i).Description;
		Filter += _T("|");
		Filter += m_FileTypes.ElementAt(i).Extensions;
		Filter += _T("|");
	}

	return Filter;
}

void CFilenameEdit::OnContextMenu(CWnd* pWnd, CPoint pt) 
{
	//CPoint pt;
 int SelStart, SelEnd;

	//GetCursorPos(&pt);
	GetSel(SelStart,SelEnd);

	m_PopupMenu.EnableMenuItem (  1 , MF_ENABLED | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  2 , MF_ENABLED | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  3 , (CanUndo() ? MF_ENABLED : MF_GRAYED)| MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  4 , MF_ENABLED | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  5 , (SelStart == SelEnd ? MF_GRAYED : MF_ENABLED) | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  6 , (SelStart == SelEnd ? MF_GRAYED : MF_ENABLED) | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  7 , (NTextClipboard::IsText() ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  8 , (SelStart == SelEnd ? MF_GRAYED : MF_ENABLED) | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem (  9 , MF_ENABLED | MF_BYCOMMAND );
	m_PopupMenu.EnableMenuItem ( 10 , MF_ENABLED | MF_BYCOMMAND );


	switch( m_PopupMenu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN,pt.x,pt.y,pWnd) )
{

	case 1: // browse
		Browse();
	break;

	case 2: // blank
	break;

	case 3: // undo
	 Undo();
	break;
	

	case 4: // blank 
	break;

	case 5: // cut 
	 Cut();
	break;

	case 6: // copy 
	 Copy();
	break;

	case 7: // paste 
	 Paste();
	break;

	case 8: // delete 
	 ReplaceSel(NULL_STR,TRUE);
	break;

	case 9: // blank 
	break;

	case 10: // select all
	 SetSel(0,-1);
	break;

 default:
	case 0:
	break;

}
	
}

void CFilenameEdit::Browse()
{
 CString strFolderPath;
 CString strOldPath;
 GetWindowText(strOldPath);

	switch ( m_EditType )
	{
	 case ET_FOLDER:

			if( GetFolder(&strFolderPath, m_sWindowTitle , GetParent()->m_hWnd, NULL, strOldPath ) )
			{
				// make sure there is a '\' at the end of the path name
				if ( strFolderPath.Right(1) != _T("\\") ) strFolderPath += _T("\\");

				SetWindowText(strFolderPath);
			}
  break;

		case ET_FILE:
			{	CFileDialog dlg(m_ActionType == AT_READ, GetDefaultExt(),m_DefaultFilename,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, GetFilter(),this);
			if ( dlg.DoModal() == IDOK )
			{
				SetWindowText( dlg.GetPathName() );
			}
			}
			break;
  default:
		 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);	
		break;
	}
}

bool CFilenameEdit::IsGood()
{
	// check for file/folder existence, stuff like that
 return true;
}