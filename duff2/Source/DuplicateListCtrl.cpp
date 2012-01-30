// DuplicateListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "DuplicateListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <math.h>
#include "FileInfo.h"
#include "util.h"
#include "TextClipboard.h"
#include "DuffDlg.h"



extern CDuffApp theApp;

CArray <CDuplicateListColumn *, CDuplicateListColumn* > CDuplicateListCtrl::m_Columns;

/////////////////////////////////////////////////////////////////////////////
// CDuplicateListCtrl

CDuplicateListCtrl::CDuplicateListCtrl()
{
	m_bToolTipCtrlCustomizeDone = false;
	m_pchTip = NULL;
	m_pwchTip = NULL;

	m_DuplicateBytesCounter = 0;
	m_DuplicateSetCounter = 0;
	m_DuplicateCounter = 0;
	m_TotalBytesCounter = 0;
	m_TotalFilesCounter = 0;
	m_MarkedCounter = 0;
	m_SelectedCounter = 0;
	m_SelectedBytesCounter = 0;
	m_MarkedBytesCounter = 0;
	m_MultiModifyInProgress = false;

	m_DupeFindDlg.Create(IDD_DUPE_FIND_DIALOG,NULL);
	m_DupeFindDlg.SetWindowPos(&wndTopMost , 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE );
	m_DupeFindDlg.SetDupeDlg(this);

	m_pTotalCheckedCtrl = NULL;
	m_pNumSelectedCtrl = NULL;
	m_pSelectedBytesCtrl = NULL;
	m_pMarkedBytesCtrl = NULL;
	m_pTotalCountCtrl = NULL;
	m_pTotalBytesCtrl = NULL;

	m_pTotalDupeCtrl = NULL;
	m_pDupeBytesCtrl = NULL;

	m_Columns.Add(&m_ColumnDupeSet);
	m_Columns.Add(&m_ColumnFilename);
	m_Columns.Add(&m_ColumnFullFilename);
	m_Columns.Add(&m_ColumnLocation);
	m_Columns.Add(&m_ColumnFileSize);
	m_Columns.Add(&m_ColumnFileVersion);
	m_Columns.Add(&m_ColumnAttributes);
	m_Columns.Add(&m_ColumnFileCreationDate);
	m_Columns.Add(&m_ColumnFileModifyDate);
	m_Columns.Add(&m_ColumnFileAccessDate);
	m_Columns.Add(&m_ColumnFileTypeDesc);
}

CDuplicateListCtrl::~CDuplicateListCtrl()
{
	// tool tip cleanup
 if(m_pchTip  != NULL) delete m_pchTip;
	if(m_pwchTip != NULL)	delete m_pwchTip;
 //

}

//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

BEGIN_MESSAGE_MAP(CDuplicateListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CDuplicateListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDoubleClickItem)
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDuplicateListCtrl message handlers

void CDuplicateListCtrl::PreSubclassWindow()
{
 CString sMsg;
	LOGFONT lfLogFont;
	long    lFontHeight = 11;
 RECT    rCtrlRect;

	CListCtrl::PreSubclassWindow();





	// initialize list view settings
	SetExtendedStyle(  LVS_REPORT | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP );
 //

	//subclass header control
//	m_HeaderCtrl.SubclassWindow( ::GetDlgItem(m_hWnd,0) );
 ASSERT( GetStyle() & LVS_REPORT );
	VERIFY( m_HeaderCtrl.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );

	// enable tool tips
	EnableToolTips(TRUE);
 //

	// get font height
	if ( CWnd::GetFont()->GetLogFont(&lfLogFont) )
	{
		lFontHeight = abs(lfLogFont.lfHeight);
		TRACE1("Font Height: %d" ,lFontHeight);
	}
	else
	{
		TRACE0("Unable to get font");
	}
	//

	// get window rectanle
	GetWindowRect(&rCtrlRect);
 //


	// insert the mark (check) column
	InsertColumn( 0 , _T("?") , LVCFMT_LEFT ,    (int)(lFontHeight * 1.9) );
	//

	// save the control width
	m_OldListWidth	= rCtrlRect.right - rCtrlRect.left;
 //

	// add the visible columns
	SetupColumns();
 //

 return;
}


// incomplete
void CDuplicateListCtrl::SetupColumns()
{
 int  iIndex;
 RECT rRectangle;
	int iNewColumnWidth = 100;
	CString sTemp;

	// get control rectangle
	GetWindowRect(&rRectangle);
	//

	// delete any existing columns
	while (DeleteColumn(1));
	//

	// add visible columns
	for (iIndex = 0; iIndex < m_Columns.GetSize(); iIndex++)
	{
   switch ( m_Columns.ElementAt(iIndex)->GetMode() )
			{
			 case CDuplicateListColumn::VM_FIXED:
				if ( m_Columns.ElementAt(iIndex)->GetPercentWidth() == -1 )
				{
					sTemp = m_Columns.ElementAt(iIndex)->GetName();
				 sTemp += "XXX";
				 iNewColumnWidth = GetStringWidth( sTemp );
				}
				else
				{
					iNewColumnWidth = (int)m_Columns.ElementAt(iIndex)->GetPercentWidth();
				}
				break;
			case CDuplicateListColumn::VM_VARIABLE:
			 // resize column as a percentage of list width
				iNewColumnWidth = static_cast<int>( m_Columns.ElementAt(iIndex)->GetPercentWidth() * (rRectangle.right - rRectangle.left));
    break;
			case CDuplicateListColumn::VM_AUTO:
				// auto-size column
			//	iNewColumnWidth = AutoSizeColumn(iIndex);

				break;
			}


		if ( m_Columns.ElementAt(iIndex)->IsVisible() )
  	InsertColumn(iIndex+1, m_Columns.ElementAt(iIndex)->GetName(), m_Columns.ElementAt(iIndex)->GetFormat(),iNewColumnWidth, iIndex+1);
	}
	//

	return;
}

////////////////////////////////////////////
// Tool Tip Text Functions                //
// Modified algorithm from codeguru.com   //
// by Kory Becker, kory@dummysoftware.com //
////////////////////////////////////////////
int CDuplicateListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	int row, col;
	RECT cellrect;
	row = CellRectFromPoint(point, &cellrect, &col );

	if ( row == -1 )
	{
		return -1;
	}

	pTI->hwnd = m_hWnd;
	pTI->uId = (UINT)((row<<10)+(col&0x3ff)+1);
	pTI->lpszText = LPSTR_TEXTCALLBACK;

	pTI->rect = cellrect;

	return pTI->uId;
}

// CellRectFromPoint	- Determine the row, col and bounding rect of a cell
// Returns		- row index on success, -1 otherwise
// point		- point to be tested.
// cellrect		- to hold the bounding rect
// col			- to hold the column index
int CDuplicateListCtrl::CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const
{
	int colnum;
	CHeaderCtrl* pHeader;
	int nColumnCount;

	// If not REPORT style for the list, then use 1 column
	// Otherwise, find the column in the report style view.
	if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
	{
		// Window is not Report style, so no headers. Deal with it!
		nColumnCount = 1;
	}
	else
	{
		// Get the number of columns in Report style.
		pHeader = (CHeaderCtrl*)GetDlgItem(0);
		nColumnCount = pHeader->GetItemCount();
	}

	// Get the top and bottom row visible
	int row = GetTopIndex();
	int bottom = row + GetCountPerPage();
	if( bottom > GetItemCount() )
		bottom = GetItemCount();

	// Loop through the visible rows
	for( ;row <=bottom;row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect rect, rectLabel;
		if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
		{
			// If not Report style, get label / icon boundaries.
			GetItemRect( row, &rect, LVIR_ICON );
			GetItemRect( row, &rectLabel, LVIR_LABEL );
		}
		else
		{
			// If Report style, get bounds of cell.
			GetItemRect( row, &rect, LVIR_BOUNDS );
		}

		if( rect.PtInRect(point) ||
			rectLabel.PtInRect(point))
		{
			bool InLabel = false;

			// Store which part user clicked on if in ICON view,
			// clicked the Label or the Icon?
			if (rect.PtInRect(point))
			{
				InLabel = false;
			}
			else if (rectLabel.PtInRect(point))
			{
				InLabel = true;
			}

			// Now find the column
			for( colnum = 0; colnum < nColumnCount; colnum++ )
			{
				// Getting column width
				int colwidth;
				if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
				{
					colwidth = 100000; // don't count colwidth.
				}
				else
				{
					// If REPORT, check inside column width.
					colwidth = GetColumnWidth(colnum);
				}

				if( (point.x >= rect.left
					&& point.x <= (rect.left + colwidth )) ||
					(point.x >= rectLabel.left
					&& point.x <= (rectLabel.left + colwidth )))
				{
					RECT rectClient;
					GetClientRect( &rectClient );
					if( col ) *col = colnum;
					rect.right = rect.left + colwidth;
					rectLabel.right = rectLabel.left + colwidth;

					// Make sure that the right extent does not exceed
					// the client area
					if ( rect.right > rectClient.right )
						rect.right = rectClient.right;
					if ( rectLabel.right > rectClient.right )
						rectLabel.right = rectClient.right;

					if (!InLabel)
					{
						*cellrect = rect;
					}
					else
					{
						*cellrect = rectLabel;
					}

					return row;
				}
				rect.left += colwidth;
				rectLabel.left += colwidth;
			}
		}
	}
	return -1;
}

//////////////////////////////////////////////////
// OnToolTipText()                              //
// Modify this function to change the text      //
// displayed in the Tool Tip.                   //
// Currently, it uses GetItemText() to just     //
// show the item's name. But you should change  //
// it to show other info like file size, etc.   //
//////////////////////////////////////////////////


BOOL CDuplicateListCtrl::OnToolTipText( UINT , NMHDR * pNMHDR, LRESULT * pResult )
{
	// need to handle both ANSI and UNICODE versions of the message
#ifdef UNICODE
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
#else
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
#endif
	CString strTip;
	UINT nID = pNMHDR->idFrom;

	if( nID == 0 )	  	// Notification in NT from automatically
		return FALSE;   	// created tooltip


if(!m_bToolTipCtrlCustomizeDone)
{
   ::SendMessage(pNMHDR->hwndFrom, TTM_SETMAXTIPWIDTH, 0, 500);
   m_bToolTipCtrlCustomizeDone = true;
}

if ( ! theApp.m_DuffOptions.General.UseToolTip )
 return FALSE;


	int row = ((nID-1) >> 10) & 0x3fffff ;
//	int col = (nID-1) & 0x3ff;


	/*
 CString AttribStr;


	// Use Item's name as the tool tip. Change this for something different.
	// Like use its file size, etc.
	//strTipText = GetItemText( row, col );
	TCHAR buffer[50];
	ulonglong2str(buffer, pFileInfo->Size);

	COleDateTime TimeC= pFileInfo->TimeCreated;
	COleDateTime TimeM= pFileInfo->TimeLastModified;
	COleDateTime TimeA= pFileInfo->TimeLastAccessed;


 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_READONLY   ) AttribStr += "R";
 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_HIDDEN     ) AttribStr += "H";
 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_SYSTEM     ) AttribStr += "S";
 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_ARCHIVE    ) AttribStr += "A";
 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_COMPRESSED ) AttribStr += "C";
 if ( pFileInfo->Attributes & FILE_ATTRIBUTE_ENCRYPTED  ) AttribStr += "E";


	strTip.Format("%s\n%s bytes\nCreated on %s\nLast Modified on %s\nLast Accessed on %s\nAttributes: %s",
		                 pFileInfo->GetFullName(),
																			 buffer,
																				TimeC.Format("%B %d %Y at %H:%M:%S"),
																				TimeM.Format("%B %d %Y at %H:%M:%S"),
																				TimeA.Format("%B %d %Y at %H:%M:%S"),
																				AttribStr
																				);


*/

	// format the tool tip
		CFileInfo* pFileInfo = (CFileInfo*)GetItemData(row);
		ASSERT_VALID(pFileInfo);

	strTip = theApp.m_DuffOptions.General.ToolTipText;

	CString sTemp;

	for (int i =0; i < m_Columns.GetSize(); i++)
	{
		sTemp.Format( _T("%%%c") ,_T('a') + i);
		strTip.Replace( sTemp,m_Columns.ElementAt(i)->GetColumnText(pFileInfo) );
	}

	//

#ifndef UNICODE
  if(pNMHDR->code == TTN_NEEDTEXTA)
  {
    if(m_pchTip != NULL)
      delete m_pchTip;

    m_pchTip = new CHAR[strTip.GetLength()+1];
    lstrcpyn(m_pchTip, strTip, strTip.GetLength());
    m_pchTip[strTip.GetLength()] = 0;
    pTTTA->lpszText = (LPSTR)m_pchTip;
  }
  else
  {
    if(m_pwchTip != NULL)
      delete m_pwchTip;

    m_pwchTip = new WCHAR[strTip.GetLength()+1];
    _mbstowcsz(m_pwchTip, strTip, strTip.GetLength());
    m_pwchTip[strTip.GetLength()] = 0; // end of text
    pTTTA->lpszText = (LPSTR)m_pwchTip;
  }
#else
  if(pNMHDR->code == TTN_NEEDTEXTA)
  {
    if(m_pchTip != NULL)
      delete m_pchTip;

    m_pchTip = new CHAR[strTip.GetLength()+1];
    _wcstombsz(m_pchTip, strTip, strTip.GetLength());
    m_pchTip[strTip.GetLength()] = 0; // end of text
    pTTTW->lpszText = (LPWSTR)m_pchTip;
  }
  else
  {
    if(m_pwchTip != NULL)
      delete m_pwchTip;

    m_pwchTip = new WCHAR[strTip.GetLength()+1];
    lstrcpyn(m_pwchTip, strTip, strTip.GetLength());
    m_pwchTip[strTip.GetLength()] = 0;
    pTTTW->lpszText = (LPWSTR) m_pwchTip;
  }
#endif


	*pResult = 0;

	return TRUE;    // message was handled
}


void CDuplicateListCtrl::OnRclick(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
 POINT ptCursorPos;
	GetCursorPos(&ptCursorPos);

	// show the list item context menu
	DoItemPopupMenu(ptCursorPos);
	//

	*pResult = 0;
}


void CDuplicateListCtrl::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CFileInfo *pFileInfo = NULL;

	pFileInfo = (CFileInfo*)GetItemData( pNMListView->iItem );

	// item data should always be set
	ASSERT( pFileInfo );
	//

	// update total counters
	m_TotalBytesCounter -= pFileInfo->Size;
	m_TotalFilesCounter --;

	if ( pFileInfo->FirstFile )
	{
		m_DuplicateSetCounter --;
	}
	else
	{
		m_DuplicateCounter --;
		m_DuplicateBytesCounter -= pFileInfo->Size;
	}

	// if this file is selected, decrease the number of selected
	if ( GetItemState(pNMListView->iItem, LVIS_SELECTED) )
	{
		m_SelectedCounter--;
		m_SelectedBytesCounter -= pFileInfo->Size;
	}

	if ( pFileInfo->Selected )
	{
		m_MarkedCounter --;
		m_MarkedBytesCounter -= pFileInfo->Size;
	}

 //

	// item data should always be set
	ASSERT( pFileInfo );
	//

#if 0 // should happen in CleanUp() as everybody uses references to that data...
	// delete the associated CFileInfo object
	delete pFileInfo;
	//
#endif

#ifdef _DEBUG
	SetItemData( pNMListView->iItem, NULL );
#endif
/*

  UC_TOTAL_CHECKED =  1, UC_NUM_SELECTED =  2, UC_SELECTED_BYTES    =  4, UC_MARKED_BYTES = 8,
  UC_TOTAL_COUNT   = 16, UC_TOTAL_BYTES  = 32, UC_TOTAL_DUPELICATES = 64, UC_DUPELICATE_BYTES = 128
*/

	// update controls
	UpdateCtrls(	UC_TOTAL_COUNT | UC_TOTAL_BYTES | UC_TOTAL_DUPELICATES | UC_DUPELICATE_BYTES |
					UC_NUM_SELECTED | UC_SELECTED_BYTES | UC_TOTAL_CHECKED | UC_MARKED_BYTES
					);
	//

	*pResult = 0;
}

void CDuplicateListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString      sTemp;
	int          iColumnIndex;
	int          iIndex;
	CFileInfo   *pFileInfo;

	pFileInfo = (CFileInfo*) GetItemData( pNMListView->iItem );
	//ASSERT(pFileInfo->Size); // size may be 0

	// update total counters
	m_TotalBytesCounter += pFileInfo->Size;
	m_TotalFilesCounter ++;
	if ( pFileInfo->FirstFile )
	{
		m_DuplicateSetCounter ++;
	}
	else
	{
		m_DuplicateCounter ++;
	 m_DuplicateBytesCounter += pFileInfo->Size;
	}
 //

	// setup column texts
 //sTemp.Format( _T("%d") , m_DuplicateSetCounter);
 //SetItemText( pNMListView->iItem, 0, sTemp);
	iColumnIndex = 1;
	for ( iIndex = 0; iIndex < m_Columns.GetSize(); iIndex++)
	{
		if ( m_Columns.ElementAt(iIndex)->IsVisible() )
		{
   SetItemText( pNMListView->iItem, iColumnIndex, m_Columns.ElementAt(iIndex)->GetColumnText(pFileInfo) );
			iColumnIndex++;
		}
	}
 //

	// update controls
	UpdateCtrls( UC_TOTAL_COUNT | UC_TOTAL_BYTES | UC_TOTAL_DUPELICATES | UC_DUPELICATE_BYTES);
	//

	*pResult = 0;
}



void CDuplicateListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString      sTemp;
 CFileInfo   *pFileInfo;

	// return if we are within a multimodify process
 if (m_MultiModifyInProgress)
		return;
	//

	if ( pNMListView )
	{
		// if we were told about an item that was just added, we have nothing to do
		if ( (unsigned long)pNMListView->iItem == m_TotalFilesCounter )
		  return;
		//

		pFileInfo = (CFileInfo*)GetItemData(pNMListView->iItem);

		// if the selected state of the item has changed, update selection-related counts
		if ( (pNMListView->uChanged & LVIF_STATE  ) && ((pNMListView->uNewState & LVIS_SELECTED) != (pNMListView->uOldState & LVIS_SELECTED)))
		{
			if (pNMListView->uNewState & LVIS_SELECTED)
			{
				m_SelectedCounter += 1;
				m_SelectedBytesCounter += pFileInfo->Size;
			}
			else
			{
				m_SelectedCounter -= 1;
				m_SelectedBytesCounter -= pFileInfo->Size;
			}

		}

  // if the checked state of the item has changed, update check-related counts
		if ( (pNMListView->uChanged & LVIF_STATE  ) && ((pNMListView->uNewState & 4096) != (pNMListView->uOldState & 4096)))
		{

			if (pNMListView->uNewState & 4096)
			{
				m_MarkedCounter --;
				m_MarkedBytesCounter -= pFileInfo->Size;
				pFileInfo->Selected = false;
			}
			else
			{
				m_MarkedCounter ++;
				m_MarkedBytesCounter += pFileInfo->Size;
				pFileInfo->Selected = true;
			}
		}

		// update dialog controls with new info
		UpdateCtrls( UC_TOTAL_CHECKED | UC_NUM_SELECTED | UC_SELECTED_BYTES | UC_MARKED_BYTES);
		//

	}//endif



 if (pResult)	*pResult = 0;

	return;
}


void CDuplicateListCtrl::AddItem( CFileInfo * pFileInfo)
{
	ASSERT(pFileInfo);
	//ASSERT(pFileInfo->Size); // size may be 0

	// add file to list view
	InsertItem ( LVIF_PARAM | LVIF_TEXT , (int)m_TotalFilesCounter , _T("") , NULL , NULL , NULL , (DWORD)pFileInfo );
 //

	// resize columns if needed
	UpdateColumnWidths();
	//

	return;
}


void CDuplicateListCtrl::UpdateColumnWidths(int iNewListWidth , int iNewListHeight)
{
 RECT rRectangle;
 int  iColumnIndex;
 int  iIndex;
 int  iOldColumnWidth;
	int  iNewColumnWidth;
 bool bNeedToRedraw = false;

	// get control rectangle
	GetWindowRect(&rRectangle);
	//

 if ( iNewListWidth == -1 || iNewListHeight == -1 )
	{
		iNewListWidth  = rRectangle.right - rRectangle.left;
		iNewListHeight = rRectangle.bottom - rRectangle.top;
	}

	SetRedraw(FALSE);
// ModifyStyle(WS_VISIBLE,NULL);

	iColumnIndex = 1;
	for ( iIndex = 0; iIndex < m_Columns.GetSize(); iIndex++ )
	{
		if ( m_Columns.ElementAt(iIndex)->IsVisible() )
		{
   switch ( m_Columns.ElementAt(iIndex)->GetMode() )
			{
			case CDuplicateListColumn::VM_FIXED:
    // don't resize column
				break;
			case CDuplicateListColumn::VM_VARIABLE:
			 // resize column as a percentage of list width
				iNewColumnWidth = static_cast<int>( m_Columns.ElementAt(iIndex)->GetPercentWidth() * iNewListWidth);
				SetColumnWidth(iColumnIndex, iNewColumnWidth );
				bNeedToRedraw = true;
				break;
			case CDuplicateListColumn::VM_AUTO:
				// auto-size column
				iOldColumnWidth = GetColumnWidth(AbsoluteIndexToVisibleIndex(iIndex));
				AutoSizeColumn(iColumnIndex);
    iNewColumnWidth = GetColumnWidth(AbsoluteIndexToVisibleIndex(iIndex));
    if (iOldColumnWidth != iNewColumnWidth) bNeedToRedraw = true;
				break;
			}
		 iColumnIndex++;
		}
	}

	SetRedraw(TRUE);
 //ModifyStyle(NULL,WS_VISIBLE);
	if (bNeedToRedraw) Invalidate();

	// save current column width
	m_OldListWidth = iNewListWidth;
	//

}


void CDuplicateListCtrl::OnSize(UINT uiType, int iNewListWidth , int iNewListHeight)
{

	// do parent clas OnSize
	CListCtrl::OnSize(uiType, iNewListHeight, iNewListWidth);
	//

 // resize columns if needed
	UpdateColumnWidths(iNewListWidth, iNewListHeight);
 //

	return;
}




void CDuplicateListCtrl::UpdateListMarks()
{
 int	iIndex = GetItemCount() - 1;

	while ( iIndex > -1 )
	{
		SetCheck ( iIndex, ((CFileInfo*)GetItemData(iIndex))->Selected );
		iIndex--;
	}

	return;
}

bool CDuplicateListCtrl::DoFind()
{
 bool       bDone = false;
 CFileInfo *pFileInfo;
 CString    sTemp;
	int        iIndex = 0;
	bool       bFound = false;
 bool       bEverFound = false;
 int        iDirection;
 int        iColumnIndex = 0;

	// save dialog settings on find dialog
	m_DupeFindDlg.UpdateData(TRUE);
	//

 // clear all selections
	if ( m_DupeFindDlg.m_ClearCurSel )
	{
		iIndex = GetNextItem(-1,LVNI_SELECTED );
		m_MultiModifyInProgress = true;
		while (iIndex != LB_ERR)
		{
			SetItemState(iIndex, NULL ,LVIS_SELECTED);
			iIndex = GetNextItem(iIndex,LVNI_SELECTED );
		}
		m_MultiModifyInProgress = false;
		m_SelectedCounter = 0;
		m_SelectedBytesCounter = 0;
		OnItemchanged(NULL,NULL);
 }
	//

	if ( m_DupeFindDlg.m_Direction == 0)
	{
		// down
		iDirection = -1;
		iIndex = (int)m_TotalFilesCounter - 1;
	}
	else
	{
		// up
		iDirection = 1;
		iIndex = 0;
	}

	while( !bDone && iIndex >= 0 && iIndex < m_TotalFilesCounter )
	{

		pFileInfo = (CFileInfo*)GetItemData(iIndex);
		bFound = false;
  iColumnIndex = 0;

		// determine if the current item matches the find specifications
		switch ( m_DupeFindDlg.m_WholeWordOnly )
		{
			case TRUE:
				switch ( m_DupeFindDlg.m_MatchCase )
				{
				case TRUE:
					// search all the searchable column texts
					while ( !bFound && iColumnIndex < m_Columns.GetSize() )
					{
      if ( m_DupeFindDlg.m_Columns.GetCheck(iColumnIndex) )
						{
						 bFound = _tcscmp ( m_Columns.ElementAt(iColumnIndex)->GetColumnText(pFileInfo), m_DupeFindDlg.m_Text ) == 0;
			   }
						iColumnIndex++;
					}

					break;
				case FALSE:
					// search all the searchable column texts
					while ( !bFound && iColumnIndex < m_Columns.GetSize() )
					{
      if ( m_DupeFindDlg.m_Columns.GetCheck(iColumnIndex) )
						{
						 bFound = _tcsicmp ( m_Columns.ElementAt(iColumnIndex)->GetColumnText(pFileInfo), m_DupeFindDlg.m_Text ) == 0;
			   }
						iColumnIndex++;
					}

					break;
				}
				break;
			case FALSE:
				switch ( m_DupeFindDlg.m_MatchCase )
				{
				case TRUE:

					// search all the searchable column texts
					while ( !bFound && iColumnIndex < m_Columns.GetSize() )
					{
      if ( m_DupeFindDlg.m_Columns.GetCheck(iColumnIndex) )
						{
						 bFound = _tcsstr ( m_Columns.ElementAt(iColumnIndex)->GetColumnText(pFileInfo), m_DupeFindDlg.m_Text ) != 0;
			   }
						iColumnIndex++;
					}

					break;
				case FALSE:

					// search all the searchable column texts
					while ( !bFound && iColumnIndex < m_Columns.GetSize() )
					{
      if ( m_DupeFindDlg.m_Columns.GetCheck(iColumnIndex) )
						{
						 bFound = _tcsistr ( m_Columns.ElementAt(iColumnIndex)->GetColumnText(pFileInfo), m_DupeFindDlg.m_Text ) != 0;
			   }
						iColumnIndex++;
					}

					break;
				}
    break;
		}
		// switch


		// invert result if using NOT logic
		if ( m_DupeFindDlg.m_Not ) bFound = !bFound;
  //


		// if an item was found, select it and if it is the first found item, make sure its visible
		if ( bFound )
		{
			SetItemState ( iIndex , LVIS_SELECTED , LVIS_SELECTED );
		 if ( !bEverFound ) EnsureVisible ( iIndex , FALSE );
   if ( m_DupeFindDlg.m_SelectOption == 1 ) bDone = true;
   bEverFound = true;
	 }
  //

  iIndex += iDirection;
	}

	return bEverFound;
}

void CDuplicateListCtrl::SetTotalCheckedCtrl(CEdit *pEdit)
{
	m_pTotalCheckedCtrl = pEdit;
 UpdateCtrls(UC_TOTAL_CHECKED);
}

void CDuplicateListCtrl::SetNumSelectedCtrl(CEdit *pEdit)
{
	m_pNumSelectedCtrl = pEdit;
	UpdateCtrls(UC_NUM_SELECTED);
}

void CDuplicateListCtrl::SetSelectedBytesCtrl(CEdit *pEdit)
{
	m_pSelectedBytesCtrl = pEdit;
	UpdateCtrls(UC_SELECTED_BYTES);
}

void CDuplicateListCtrl::SetMarkedBytesCtrl(CEdit *pEdit)
{
	m_pMarkedBytesCtrl = pEdit;
	UpdateCtrls(UC_MARKED_BYTES);
}

void CDuplicateListCtrl::SetTotalCountCtrl(CEdit *pEdit)
{
	m_pTotalCountCtrl = pEdit;
	UpdateCtrls(UC_TOTAL_COUNT);
}

void CDuplicateListCtrl::SetTotalBytesCtrl(CEdit *pEdit)
{
	m_pTotalBytesCtrl = pEdit;
	UpdateCtrls(UC_TOTAL_BYTES);
}
void CDuplicateListCtrl::SetTotalDuplicateCtrl(CEdit *pEdit)
{
 m_pTotalDupeCtrl = pEdit;
	UpdateCtrls(UC_TOTAL_DUPELICATES);
}

void CDuplicateListCtrl::SetDuplicateBytesCtrl(CEdit *pEdit)
{
	m_pDupeBytesCtrl = pEdit;
	UpdateCtrls(UC_DUPELICATE_BYTES);
}

void CDuplicateListCtrl::UpdateCtrls(UINT uiFlags)
{
	TCHAR   tcBuffer[50];

	// update 'total marked' edit box
	if ( (uiFlags & UC_TOTAL_CHECKED) && m_pTotalCheckedCtrl )
	{
		ulonglong2str(tcBuffer, m_MarkedCounter);
	 m_pTotalCheckedCtrl->SetWindowText(tcBuffer);
	}

	// update 'num selected' edit box
	if ( (uiFlags & UC_NUM_SELECTED) && m_pNumSelectedCtrl )
	{
		ulonglong2str(tcBuffer, m_SelectedCounter);
		m_pNumSelectedCtrl->SetWindowText(tcBuffer);
	}

	// update 'selected bytes' edit box
 if ( (uiFlags & UC_SELECTED_BYTES) && m_pSelectedBytesCtrl )
	{
		ulonglong2str(tcBuffer, m_SelectedBytesCounter);
		m_pSelectedBytesCtrl->SetWindowText(tcBuffer);
	}

	// update 'marked bytes' edit box
	if ( (uiFlags & UC_MARKED_BYTES) && m_pMarkedBytesCtrl )
	{
		ulonglong2str(tcBuffer, m_MarkedBytesCounter);
		m_pMarkedBytesCtrl->SetWindowText(tcBuffer);
	}

	// update 'total files' edit box
	if ( (uiFlags & UC_TOTAL_COUNT) && m_pTotalCountCtrl )
	{
		ulonglong2str(tcBuffer, m_TotalFilesCounter);
 	m_pTotalCountCtrl->SetWindowText(tcBuffer);
	}

	// update 'total bytes' edit box
	if ( (uiFlags & UC_TOTAL_BYTES) && m_pTotalBytesCtrl )
	{
		ulonglong2str(tcBuffer, m_TotalBytesCounter);
	 m_pTotalBytesCtrl->SetWindowText(tcBuffer);
 }

	// update 'total duplicates' edit box
	if ( (uiFlags & UC_TOTAL_DUPELICATES) && m_pTotalDupeCtrl )
	{
		ulonglong2str(tcBuffer, m_DuplicateCounter);
	 m_pTotalDupeCtrl->SetWindowText(tcBuffer);
 }

	// update 'duplicate bytes' edit box
	if ( (uiFlags & UC_DUPELICATE_BYTES) && m_pDupeBytesCtrl )
	{
		ulonglong2str(tcBuffer, m_DuplicateBytesCounter);
	 m_pDupeBytesCtrl->SetWindowText(tcBuffer);
 }


 return;
}

int CDuplicateListCtrl::AbsoluteIndexToVisibleIndex(int AbsoluteIndex)
{
	int VisibleIndex = 0;
	for (int i = 0; i <= AbsoluteIndex; i++)
	{
		if ( m_Columns.ElementAt(i)->IsVisible() )
		 VisibleIndex++;
	}
	return VisibleIndex;
}


int CDuplicateListCtrl::VisibleIndexToAbsoluteIndex(int VisibleIndex)
{
	int iVisibleCount = 0;
 int iAbsoluteIndex = -1;

	if (VisibleIndex != -1)
	{
		iVisibleCount = 0;
		iAbsoluteIndex = 0;
		while ( iAbsoluteIndex < m_Columns.GetSize() && iVisibleCount != VisibleIndex)
		{
			if ( m_Columns.ElementAt(iAbsoluteIndex)->IsVisible() )
			{
				iVisibleCount++;
			}
			iAbsoluteIndex++;
		}
		iAbsoluteIndex--;
	}
 return iAbsoluteIndex;
}

//incomplete
void CDuplicateListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// int iColumnIndex;
 int iIndex;

 // if a valid column was clicked, sort the list based on that column's data
	if (pNMListView->iSubItem != -1)
	{
	/*	iColumnIndex = 0;
		iIndex = 0;
		while ( iIndex < m_Columns.GetSize() && iColumnIndex != pNMListView->iSubItem)
		{
			if ( m_Columns.ElementAt(iIndex)->IsVisible() )
				iColumnIndex++;

			iIndex++;
		}
		iIndex--;
  */

	iIndex = VisibleIndexToAbsoluteIndex(pNMListView->iSubItem);

  if ( iIndex <0 )
			return;

		// actual : 0 1 2 3 4 5 6 7 8
		// visible:   0 1   2 3   4

		//?? tricky - getting correc column index if some columns are not visible

		// must initialize the sort column
		m_Columns.ElementAt(iIndex)->InitSortColumn();
		//


		// perform the sort
	 SortItems( CompareItems, (LPARAM)m_Columns.ElementAt(iIndex) );
		//

		m_HeaderCtrl.SetSortImage( pNMListView->iSubItem, CDuplicateListColumn::IsSortAcending() );

	}

	*pResult = 0;
	return;
}

void CDuplicateListCtrl::OnDoubleClickItem(NMHDR* pNMHDR, LRESULT* pResult)
{
 NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// if a valid list item was double-clicked on, execute the file associated with it
	if ( pNMListView->iItem != -1 )
	{
 	ShellExecute( NULL , NULL, ((CFileInfo*)GetItemData(pNMListView->iItem))->GetFullName() , NULL_STR , NULL_STR , SW_SHOWNORMAL );
	}
 //

	*pResult = 0;
	return;
}


void CDuplicateListCtrl::RebuildColumns()
{
 int          iColumnIndex;
	unsigned int uiIndexX;
	int          iIndexY;

	for (uiIndexX = 0; uiIndexX < m_TotalFilesCounter; uiIndexX++)
	{
		iColumnIndex = 1;
		for(iIndexY = 0; iIndexY < m_Columns.GetSize(); iIndexY++)
		{
			if ( m_Columns.ElementAt(iIndexY)->IsVisible() )
			{
				SetItemText( uiIndexX , iColumnIndex, m_Columns.ElementAt(iIndexY)->GetColumnText((CFileInfo*)GetItemData(uiIndexX)) );
				iColumnIndex++;
			}
		}
 }

	return;
}



BOOL CDuplicateListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	//LPNMHDR pNH = (LPNMHDR) lParam;
 HD_NOTIFY   *pHDN = (HD_NOTIFY*)lParam;
 double dPercentWidth;

	switch( pHDN->hdr.code )
	{
		// prevent header resizing on 'auto width' columns
 	case HDN_BEGINTRACKW:
	 case HDN_BEGINTRACKA:
			TRACE1( "HDN_BEGINTRACK %d\n" ,pHDN->iItem);
			if ( pHDN->iItem > 0)
			switch ( m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(pHDN->iItem))->GetMode() )
			{
			 case CDuplicateListColumn::VM_AUTO:
     *pResult = TRUE;
     return TRUE;
			}
		break;

		// save the new column percent width after it is manually resized
		case HDN_ENDTRACKA:
		case HDN_ENDTRACKW:
			TRACE1( "HDN_ENDTRACK %d\n" ,pHDN->iItem);
			if ( pHDN->iItem > 0)
			{
				RECT rRectangle;
				GetWindowRect(&rRectangle);
				switch ( m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(pHDN->iItem))->GetMode() )
			 {
			  case CDuplicateListColumn::VM_VARIABLE:
  				dPercentWidth = (double)GetColumnWidth(pHDN->iItem) / (rRectangle.right - rRectangle.left);
  				m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(pHDN->iItem))->SetPercentWidth(dPercentWidth);
				 break;
			  case CDuplicateListColumn::VM_FIXED:
     m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(pHDN->iItem))->SetPercentWidth( GetColumnWidth(pHDN->iItem) );
					break;
				}
			}
		break;

		case HDN_DIVIDERDBLCLICKA:
		case HDN_DIVIDERDBLCLICKW:
			TRACE1( "HDN_DIVIDERDBLCLICK %d\n" ,pHDN->iItem);
			if ( pHDN->iItem > 0)
    AutoSizeColumn(pHDN->iItem);
			*pResult = TRUE;
   return TRUE;
  break;

		// show pop-up menu for column setings
		case NM_RCLICK:
			TRACE1( "NM_RCLICK %d\n" ,pHDN->iItem);
			// wParam is zero for Header ctrl
			if( wParam == 0 )
			{
				// Right button was clicked on header
				CPoint pt(GetMessagePos());
				CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
				pHeader->ScreenToClient(&pt);

				// Determine the column index
				int index = -1;
				CRect rcCol;
				for( int i=0; Header_GetItemRect(pHeader->m_hWnd, i, &rcCol); i++ )
				{
					if( rcCol.PtInRect( pt ) )
					{
						index = i;
						break;
					}
				}
				DoColumnPopupMenu(index);
			}
  break;
	}


	return CListCtrl::OnNotify(wParam, lParam, pResult);
}


void CDuplicateListCtrl::DoColumnPopupMenu(int iColumnIndex)
{
	CString sTemp;
 int     iSelectedIndex;
	int     iIndex;
	bool    bRebuild = false;
	POINT   ptCursorPos;
	CMenu   mPopupMenu;

	// if we got an invalid column index, exit
	//if ( iColumnIndex == -1 )
	//	return;
	//

 // get cursor pos ( we will pop up the menu at the cursor position)
	GetCursorPos(&ptCursorPos);
	//

	// load the base menu
	mPopupMenu.LoadMenu(IDR_DUPE_HEADER_MENU);
	//

	if ( iColumnIndex > 0 )
	{
  UINT uiItem;
		switch(m_Columns.ElementAt( VisibleIndexToAbsoluteIndex(iColumnIndex) )->GetMode())
		{

		 default:
		 case CDuplicateListColumn::VM_FIXED:
		 	uiItem = IDM_COLUMN_FIXED_WIDTH;
   break;

			case CDuplicateListColumn::VM_VARIABLE:
    uiItem = IDM_COLUMN_VARIABLE_WIDTH;
			break;

   case CDuplicateListColumn::VM_AUTO:
    uiItem = IDM_COLUMN_AUTO_WIDTH;
			break;

		}

		// select the 'fixed with' or 'variable with' menu radio item
		mPopupMenu.CheckMenuRadioItem ( IDM_COLUMN_FIXED_WIDTH , IDM_COLUMN_AUTO_WIDTH , uiItem , MF_BYCOMMAND );
  //

	}
	else
	{

		// disable the column width menu options
		mPopupMenu.GetSubMenu(0)->EnableMenuItem(IDM_COLUMN_FIXED_WIDTH,MF_GRAYED);
		mPopupMenu.GetSubMenu(0)->EnableMenuItem(IDM_COLUMN_VARIABLE_WIDTH,MF_GRAYED);
		mPopupMenu.GetSubMenu(0)->EnableMenuItem(IDM_COLUMN_AUTO_WIDTH,MF_GRAYED);
		//

	}

	// append the column types to the end of the menu, and check the ones that are visible
	for( iIndex = 0; iIndex < m_Columns.GetSize(); iIndex++)
	{
		mPopupMenu.GetSubMenu(0)->InsertMenu(UINT_MAX,MF_BYPOSITION | MF_STRING, IDM_COLUMN_AUTO_WIDTH+iIndex+1, m_Columns.ElementAt(iIndex)->GetName() );
		mPopupMenu.GetSubMenu(0)->CheckMenuItem(IDM_COLUMN_AUTO_WIDTH+iIndex+1, m_Columns.ElementAt(iIndex)->IsVisible() ? MF_CHECKED  : MF_UNCHECKED );
	}
	//

	// pop up the menu
	iSelectedIndex = mPopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTALIGN, ptCursorPos.x, ptCursorPos.y, this);
	//

	// do what the user clicked
	switch(iSelectedIndex)
	{
	case 0:
		break;
	case IDM_COLUMN_FIXED_WIDTH:
		{
			m_Columns.ElementAt( VisibleIndexToAbsoluteIndex(iColumnIndex) )->SetMode( CDuplicateListColumn::VM_FIXED);
		double dPercentWidth = (double)GetColumnWidth(iColumnIndex);
		m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(iColumnIndex) )->SetPercentWidth(dPercentWidth);
 	}
		break;
	case IDM_COLUMN_VARIABLE_WIDTH:
		{
			double PercentWidth;
		RECT rRectangle;
	 GetWindowRect(&rRectangle);
		PercentWidth = (double)GetColumnWidth( iColumnIndex ) / (rRectangle.right - rRectangle.left);

		m_Columns.ElementAt( VisibleIndexToAbsoluteIndex(iColumnIndex) )->SetPercentWidth(PercentWidth);
		m_Columns.ElementAt( VisibleIndexToAbsoluteIndex(iColumnIndex) )->SetMode(CDuplicateListColumn::VM_VARIABLE);
 	}
		break;
	case IDM_COLUMN_AUTO_WIDTH:
		m_Columns.ElementAt( VisibleIndexToAbsoluteIndex(iColumnIndex) )->SetMode(CDuplicateListColumn::VM_AUTO);
  AutoSizeColumn(iColumnIndex);
		break;
	default:
		if ( m_Columns.ElementAt( iSelectedIndex-IDM_COLUMN_AUTO_WIDTH-1 )->IsVisible() )
		{
			DeleteColumn( AbsoluteIndexToVisibleIndex(iSelectedIndex-IDM_COLUMN_AUTO_WIDTH-1) );
 		bRebuild = false;
		}
		else
		{
			bRebuild = true;
		}
		m_Columns.ElementAt( iSelectedIndex-IDM_COLUMN_AUTO_WIDTH-1 )->SwitchVisible();
		break;
 }
	//

	// if we need to rebuild the colums, do it now
	if (bRebuild)
	{
		SetupColumns();
		RebuildColumns();
 }
	//

	return;
}

void CDuplicateListCtrl::DoItemPopupMenu(const POINT & ptMenuPoint)
{
 CMenu   mPopupMenu;
 int     iIndex;
 CMenu   *pMenu;
 int      iSelectionMade;
	CString  sTemp;
 SHELLEXECUTEINFO seiExecInfo;
 CFileInfo *pFileInfo;

	// get the index of the first selected item
	iIndex = GetNextItem (-1,LVNI_SELECTED );
	//

	// attempt to load the context menu
	if ( mPopupMenu.LoadMenu(IDR_MENU_DUPLICATES) )
	{
		pMenu = mPopupMenu.GetSubMenu(0);
	}
 else
	{
 	TRACE0("Unable to load context menu" );
		return;
	}
	//




  pMenu->EnableMenuItem ( ID_REMOVE_ALL, MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_REMOVEFROMLIST, MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_REMOVE_NONSELECTED, MF_GRAYED | MF_BYCOMMAND );

	// add column copy items (must be done before shell verbs add)
  int iColIndex;
	for (iColIndex = 0; iColIndex < m_Columns.GetSize(); iColIndex++)
	{
		pMenu->InsertMenu(IDM_COPY_ALL_VISIBLE_COLUMNS, MF_BYCOMMAND | MF_STRING,IDM_COPY_ALL_VISIBLE_COLUMNS+iColIndex+1, m_Columns.ElementAt(iColIndex)->GetName() );
	}
	pMenu->InsertMenu(IDM_COPY_ALL_VISIBLE_COLUMNS, MF_BYCOMMAND | MF_SEPARATOR,IDM_COPY_ALL_VISIBLE_COLUMNS+iColIndex+1, NULL_STR );
 //

	// if there were no selected items, disable some of the menu items
	if ( iIndex == LB_ERR )
	{
  pMenu->EnableMenuItem ( ID_COPYFILENAME , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_COPYFULLFILENAME , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_COPYDIRECTORYNAME , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_OPENFILES , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_OPENDIRS , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_PROPERTIES , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_REMOVEFROMLIST , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_REMOVE_NONSELECTED , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_INVERTSELECTION , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_MARK , MF_GRAYED | MF_BYCOMMAND );
  pMenu->EnableMenuItem ( ID_UNMARK , MF_GRAYED | MF_BYCOMMAND );
	}
 else
	{
  pFileInfo = (CFileInfo*)GetItemData(iIndex);
		// load shell verbs
		if ( !((CFileInfo*)GetItemData(iIndex))->ShellVerbsValid )
		{
   pFileInfo->InitShellVerbs();
		}
		//

		// add shell verbs
		int iShellIndex ;
		for (iShellIndex = 0; iShellIndex < pFileInfo->ShellVerbs.GetSize(); iShellIndex++)
		{
			pMenu->InsertMenu(ID_PROPERTIES, MF_BYCOMMAND | MF_STRING,IDM_COPY_ALL_VISIBLE_COLUMNS+iShellIndex+m_Columns.GetSize(), pFileInfo->ShellVerbs.ElementAt(iShellIndex).Name);
		}
		if (iShellIndex) pMenu->InsertMenu(ID_PROPERTIES, MF_BYCOMMAND | MF_SEPARATOR,IDM_COPY_ALL_VISIBLE_COLUMNS+iShellIndex+1+m_Columns.GetSize(), NULL_STR );
		//

	}
	//



/*

		// append the column types to the end of the menu, and check the ones that are visible
	for( iIndex = 0; iIndex < m_Columns.GetSize(); iIndex++)
	{
		mPopupMenu.GetSubMenu(0)->InsertMenu(UINT_MAX,MF_BYPOSITION | MF_STRING, IDM_COLUMN_AUTO_WIDTH+iIndex+1, m_Columns.ElementAt(iIndex)->GetName() );
		mPopupMenu.GetSubMenu(0)->CheckMenuItem(IDM_COLUMN_AUTO_WIDTH+iIndex+1, m_Columns.ElementAt(iIndex)->IsVisible() ? MF_CHECKED  : MF_UNCHECKED );
	}
	//
*/


 // pop up the menu and get a result
 iSelectionMade = pMenu->TrackPopupMenu( TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN , ptMenuPoint.x , ptMenuPoint.y , this , NULL);
 //

	// do whatever the user clicked on
	switch ( iSelectionMade )
	{

		// open the find dialog
 	case ID_FIND:
	 	m_DupeFindDlg.ShowWindow(SW_SHOW);
  break;

	 // copy the selected list item(s) filenames
		case ID_COPYFILENAME:
			while (iIndex != LB_ERR)
			{
				sTemp += ((CFileInfo*)GetItemData(iIndex))->GetName();
				sTemp += "\n";
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			sTemp.TrimRight();
			NTextClipboard::SetClipboardText(sTemp);
	 break;

		// copy the selected list item(s) full filenames (including path)
		case ID_COPYFULLFILENAME:
			while ( iIndex != LB_ERR )
			{
				sTemp += ((CFileInfo*)GetItemData(iIndex))->GetFullName();
				sTemp += "\n";
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			sTemp.TrimRight();
			NTextClipboard::SetClipboardText(sTemp);
 	break;

	 // copy the selected list item(s) parent directory name(s)
		case ID_COPYDIRECTORYNAME:
			while ( iIndex != LB_ERR )
			{
				sTemp += ((CFileInfo*)GetItemData(iIndex))->GetParentDirName();
				sTemp += "\n";
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			sTemp.TrimRight();
			NTextClipboard::SetClipboardText(sTemp);
	 break;

	 // shell execute (open) the selected list item(s)
		case ID_OPENFILES:
	 	while ( iIndex != LB_ERR )
	 	{
	 		ShellExecute( NULL , NULL , ((CFileInfo*)GetItemData(iIndex))->GetFullName() , NULL_STR , NULL_STR , SW_SHOWNORMAL);
    iIndex = GetNextItem ( iIndex , LVNI_SELECTED );
	 	}
 	break;

		// shell execute the selected item(s) parent directories
	 case ID_OPENDIRS:
			while ( iIndex != LB_ERR )
		 {
		  sTemp = ((CFileInfo*)GetItemData(iIndex))->GetFullName();
		  sTemp = sTemp.Left( sTemp.ReverseFind('\\') );
    ShellExecute( NULL , NULL , sTemp , NULL_STR , NULL_STR , SW_SHOWNORMAL );
    iIndex = GetNextItem ( iIndex, LVNI_SELECTED );
			}
  break;

		// open the shell properties dialog for the selected items
	 case ID_PROPERTIES:


		/*
		CString sAllFiles;
		memset( &seiExecInfo,0,sizeof(seiExecInfo) );
		seiExecInfo.cbSize = sizeof ( seiExecInfo ) ;
		seiExecInfo.fMask  = SEE_MASK_INVOKEIDLIST ;
		seiExecInfo.lpVerb = _T("properties") ;
	while ( iIndex != LB_ERR )
		{
			sTemp.Format( _T("\"%s\" "), ((CFileInfo*)GetItemData(iIndex))->GetFullName() );
			sAllFiles += sTemp;
			iIndex = GetNextItem(iIndex,LVNI_SELECTED );
		}
		seiExecInfo.lpFile = sAllFiles;
		MessageBox(sAllFiles);
			ShellExecuteEx ( &seiExecInfo ) ;
		}
		*/


		sTemp.Empty();
		memset( &seiExecInfo,0,sizeof(seiExecInfo) );
		seiExecInfo.cbSize = sizeof ( seiExecInfo ) ;
		seiExecInfo.fMask  = SEE_MASK_INVOKEIDLIST ;
		seiExecInfo.lpVerb = SHELL_VERB_PROPERTIES ;
		while ( iIndex != LB_ERR )
		{
			seiExecInfo.lpFile = ((CFileInfo*)GetItemData(iIndex))->GetFullName() ;
			ShellExecuteEx ( &seiExecInfo ) ;
			iIndex = GetNextItem(iIndex,LVNI_SELECTED );
		}
 	break;

	 // (un)mark ((un)check) all list item(s)
		case ID_MARK_ALL:
		case ID_MARK_NONE:
			m_MultiModifyInProgress = true;
			for (iIndex = 0; iIndex < GetItemCount(); iIndex++)
			{
				SetCheck ( iIndex , iSelectionMade == ID_MARK_ALL);
				((CFileInfo*)GetItemData(iIndex))->Selected = iSelectionMade == ID_MARK_ALL;
			}
			m_MultiModifyInProgress = false;
			if (iSelectionMade == ID_MARK_ALL)
			{
				m_MarkedCounter      = m_TotalFilesCounter;
				m_MarkedBytesCounter = m_TotalBytesCounter;
			}
			else
			{
				m_MarkedCounter = 0;
				m_MarkedBytesCounter = 0;
			}
			OnItemchanged(NULL,NULL);
		break;

  // mark (check) the selected list item(s)
		case ID_MARK:
			m_MultiModifyInProgress = true;
			while ( iIndex != LB_ERR)
			{
				if ( GetCheck(iIndex) == BST_UNCHECKED)
				{
					m_MarkedCounter++;
					m_MarkedBytesCounter += ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				SetCheck(iIndex, BST_CHECKED);
				((CFileInfo*)GetItemData(iIndex))->Selected = true;
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			m_MultiModifyInProgress = false;
			OnItemchanged(NULL,NULL);
			UpdateCtrls( UC_TOTAL_CHECKED | UC_MARKED_BYTES );
	//
		break;

  // unmark (uncheck) the selected list item(s)
		case ID_UNMARK:
			m_MultiModifyInProgress = true;
			while ( iIndex != LB_ERR)
			{
				if ( GetCheck(iIndex) == BST_CHECKED )
				{
					m_MarkedCounter--;
					m_MarkedBytesCounter -= ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				SetCheck(iIndex, BST_UNCHECKED);
				((CFileInfo*)GetItemData(iIndex))->Selected = false;
				iIndex = GetNextItem ( iIndex, LVNI_SELECTED );
			}
			m_MultiModifyInProgress = false;
			OnItemchanged(NULL,NULL);
			UpdateCtrls( UC_TOTAL_CHECKED | UC_MARKED_BYTES );
		break;


		// invert the marks (checks) on the selected list item(s)
		case ID_INVERTMARKS:
			m_MultiModifyInProgress = true;
			while ( iIndex != LB_ERR )
			{
				if ( GetCheck(iIndex) == BST_CHECKED )
				{
					m_MarkedCounter --;
					m_MarkedBytesCounter -= ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				else
				{
					m_MarkedCounter ++;
					m_MarkedBytesCounter += ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				SetCheck(iIndex,  GetCheck(iIndex) ? BST_UNCHECKED : BST_CHECKED);
				((CFileInfo*)GetItemData(iIndex))->Selected = (GetCheck(iIndex) == BST_CHECKED);
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			m_MultiModifyInProgress = false;
			OnItemchanged(NULL,NULL);
		break;

	 // invert the selection of all items
		case ID_INVERTSELECTION:
			m_MultiModifyInProgress = true;
			iIndex = GetItemCount() - 1;
			while ( iIndex > -1)
			{
				if ( GetItemState(iIndex, LVIS_SELECTED) )
				{
					SetItemState(iIndex,NULL, LVIS_SELECTED);
					m_SelectedCounter --;
					m_SelectedBytesCounter -= ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				else
				{
					SetItemState(iIndex,LVIS_SELECTED, LVIS_SELECTED);
					m_SelectedCounter ++;
					m_SelectedBytesCounter += ((CFileInfo*)GetItemData(iIndex))->Size;
				}
				iIndex--;
			}
			m_MultiModifyInProgress = false;
			OnItemchanged(NULL,NULL);
		break;

		// perform the checked file selections
		case ID_PERFORM_CHECKED_SELECTIONS:
//incomplete 		((CDuffDlg*)GetParent()->GetParent())->m_SelectionPage.PerformSelections();
		break;


		// select all items
		case ID_SELECT_ALL:
			m_MultiModifyInProgress = true;
			iIndex = GetItemCount() - 1;
			while ( iIndex > -1)
			{
				SetItemState(iIndex, LVIS_SELECTED ,LVIS_SELECTED);
				iIndex--;
			}
			m_MultiModifyInProgress = false;
			m_SelectedCounter = m_TotalFilesCounter;
			m_SelectedBytesCounter = m_TotalBytesCounter;
			OnItemchanged(NULL,NULL);
		break;

		// select no items
	 case ID_SELECT_NONE:
			m_MultiModifyInProgress = true;
			while (iIndex != LB_ERR)
			{
				SetItemState(iIndex, NULL ,LVIS_SELECTED);
				iIndex = GetNextItem(iIndex,LVNI_SELECTED );
			}
			m_MultiModifyInProgress = false;
			m_SelectedCounter = 0;
			m_SelectedBytesCounter = 0;
			OnItemchanged(NULL,NULL);
  break;

		// remove the selected items from the list
		case ID_REMOVEFROMLIST:
			if ( MessageBox( StringFromResource(IDS_DUPELIST_CONFIRM_DELETE_SELECTED), StringFromResource(IDS_CONFIRMATION) ,MB_YESNO | MB_ICONQUESTION ) == IDYES )
			{
				iIndex = GetItemCount() - 1;
				while ( iIndex > -1)
				{
					if ( GetItemState(iIndex,LVIS_SELECTED) == LVIS_SELECTED )
					{
						if ( GetCheck(iIndex) == BST_CHECKED )
						{
 						m_MarkedCounter--;
	 					m_MarkedBytesCounter -= ((CFileInfo*)GetItemData(iIndex))->Size;
						}
						DeleteItem(iIndex);
					}
					iIndex--;
				}
			}
			OnItemchanged(NULL,NULL);
		break;

  // remove all items from the list
	 case ID_REMOVE_ALL:
			DeleteAllItems();
			m_SelectedCounter = 0;
			m_SelectedBytesCounter = 0;
			m_MarkedCounter = 0;
			m_MarkedBytesCounter = 0;
			m_TotalFilesCounter = 0;
			m_DuplicateSetCounter = 0;
			m_DuplicateCounter = 0;
			m_DuplicateBytesCounter = 0;
			UpdateCtrls( UC_TOTAL_COUNT | UC_TOTAL_BYTES | UC_TOTAL_DUPELICATES | UC_DUPELICATE_BYTES);
		break;

		case IDM_COPY_ENTIRE_LIST:
		case IDM_COPY_ALL_VISIBLE_COLUMNS:

			if ( GetItemCount() )
			{
				sTemp.Empty();
				if ( iIndex == -1 || GetSelectionMark() == -1 )
				{
					// no items are selected, so process all items
					iIndex = GetItemCount() - 1;
					while ( iIndex > -1)
					{
						CFileInfo *pFileInfo = (CFileInfo*)GetItemData(iIndex);

						for (int iColIndex = 0; iColIndex < m_Columns.GetSize(); iColIndex++)
						{
							if ( iSelectionMade == IDM_COPY_ENTIRE_LIST || m_Columns.ElementAt(iColIndex)->IsVisible() )
							{
								sTemp += m_Columns.ElementAt(iColIndex)->GetColumnText(pFileInfo);
								sTemp += _T("\t");
							}
						}
						sTemp += _T("\r\n");
						iIndex--;
					}
					sTemp.TrimRight();
					NTextClipboard::SetClipboardText( sTemp );
				}
				else
				{
					// process only the selected items
					while (iIndex != LB_ERR)
					{
						CFileInfo *pFileInfo = (CFileInfo*)GetItemData(iIndex);

						for (int iColIndex = 0; iColIndex < m_Columns.GetSize(); iColIndex++)
						{
							if ( iSelectionMade == IDM_COPY_ENTIRE_LIST || m_Columns.ElementAt(iColIndex)->IsVisible() )
							{
								sTemp += m_Columns.ElementAt(iColIndex)->GetColumnText(pFileInfo);
								sTemp += _T("\t");
							}
						}
						sTemp += _T("\r\n");
						iIndex = GetNextItem(iIndex,LVNI_SELECTED );
					}
					sTemp.TrimRight();
					NTextClipboard::SetClipboardText( sTemp );
				}
			}
			break;


	 // process dynamically-added menu items
		default:
			if ( GetItemCount() )
			if (iSelectionMade > IDM_COPY_ALL_VISIBLE_COLUMNS && iSelectionMade < IDM_COPY_ALL_VISIBLE_COLUMNS+m_Columns.GetSize() )
			{
				sTemp.Empty();
 			if ( iIndex == -1 || GetSelectionMark() == -1 )
				{
 				// no items are selected, so process all items
					iIndex = GetItemCount() - 1;
					while ( iIndex > -1)
					{
						CFileInfo *pFileInfo = (CFileInfo*)GetItemData(iIndex);
						sTemp += m_Columns.ElementAt(iSelectionMade-IDM_COPY_ALL_VISIBLE_COLUMNS-1)->GetColumnText(pFileInfo);
						sTemp += _T("\r\n");
						iIndex--;
					}
				}
				else
				{
					// process only the selected items
					while (iIndex != LB_ERR)
					{
						CFileInfo *pFileInfo = (CFileInfo*)GetItemData(iIndex);
						sTemp += m_Columns.ElementAt(iSelectionMade-IDM_COPY_ALL_VISIBLE_COLUMNS-1)->GetColumnText(pFileInfo);
						sTemp += _T("\r\n");
						iIndex = GetNextItem(iIndex,LVNI_SELECTED );
					}
				}
				sTemp.TrimRight();
				NTextClipboard::SetClipboardText( sTemp );
			}
			else
			if ( iSelectionMade >= IDM_COPY_ALL_VISIBLE_COLUMNS+m_Columns.GetSize() )
			{
				pFileInfo = (CFileInfo*)GetItemData(iIndex);
				TRACE1( "index: %d\n", iSelectionMade - (IDM_COPY_ALL_VISIBLE_COLUMNS+m_Columns.GetSize()) );
    ShellExecute(NULL, pFileInfo->ShellVerbs.ElementAt(iSelectionMade - (IDM_COPY_ALL_VISIBLE_COLUMNS+m_Columns.GetSize()) ).Name, pFileInfo->GetFullName(),NULL,NULL,SW_SHOWDEFAULT );
			}
  break;

	}// end switch

 return;
}

void CDuplicateListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	RECT  rControlRectangle;
 POINT ptMenuPoint;

 // if the application menu was pressed, show the list item context menu
	if ( nChar == VK_APPS )
	{
		GetWindowRect(&rControlRectangle);
		ptMenuPoint.x = rControlRectangle.left + ((rControlRectangle.right  - rControlRectangle.left) / 2);
		ptMenuPoint.y = rControlRectangle.top  + ((rControlRectangle.bottom - rControlRectangle.top ) / 2);
		DoItemPopupMenu(ptMenuPoint);
	}

	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

int CALLBACK CDuplicateListCtrl::CompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
 return ((CDuplicateListColumn*)lParamSort)->CompareItems( (CFileInfo*)lParam1, (CFileInfo*)lParam2 );
}



int CDuplicateListCtrl::AutoSizeColumn(int iColumnIndex)
{
 int  iWidthMode1;
	int  iWidthMode2;
	int  iBiggestWidth;

	CString sTemp;
	sTemp = m_Columns.ElementAt(VisibleIndexToAbsoluteIndex(iColumnIndex))->GetName();
	sTemp += _T("XXX");
	iWidthMode1 = GetStringWidth( sTemp );
	SetColumnWidth (iColumnIndex,LVSCW_AUTOSIZE);
 iWidthMode2   = GetColumnWidth(iColumnIndex);

	/*
 // get the maximum width of the 2 width settings
	SetColumnWidth (iColumnIndex,LVSCW_AUTOSIZE);
 iWidthMode1   = GetColumnWidth(iColumnIndex);
 SetColumnWidth (iColumnIndex,LVSCW_AUTOSIZE_USEHEADER);
 iWidthMode2   = GetColumnWidth(iColumnIndex);
*/ iBiggestWidth = max(iWidthMode1,iWidthMode2);
 //


	// set the column width
	SetColumnWidth(iColumnIndex,iBiggestWidth);
 //

	// make sure that the control is redrawn
//	Invalidate();
	//
 return iBiggestWidth;
}



BOOL CDuplicateListCtrl::DestroyWindow()
{
	m_DupeFindDlg.DestroyWindow();

	return CListCtrl::DestroyWindow();
}
