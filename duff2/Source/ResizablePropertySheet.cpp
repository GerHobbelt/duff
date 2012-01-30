// ResizablePropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "ResizablePropertySheet.h"
#include "DuffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizablePropertySheet

IMPLEMENT_DYNAMIC(CResizablePropertySheet, CPropertySheet)

CResizablePropertySheet::CResizablePropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CResizablePropertySheet::CResizablePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CResizablePropertySheet::~CResizablePropertySheet()
{
}

CResizablePropertySheet::CResizablePropertySheet(CWnd* /*pWndParent */)
{
}


BEGIN_MESSAGE_MAP(CResizablePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CResizablePropertySheet)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizablePropertySheet message handlers

void CResizablePropertySheet::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
}


void  CResizablePropertySheet::Resize()
{


	
	// Find parent
	CDuffDlg* pParent;
	CRect rectParent;

	pParent = (CDuffDlg*)GetParent();
	if (pParent == NULL)
		{
		TRACE0( "Cannot resize property sheet. Sheet has no parent" );
		return;
		}

	// Get parent's client area
	pParent->m_PropertySheetFrame.GetWindowRect(&rectParent); // .GetClientRect(&rectParent);
 //pParent->GetClientRect(&rectParent);

	// Resize the sheet
	// First find relative change
	CSize sizeRelChange;
	CRect rectWindow;

	GetWindowRect(&rectWindow);
	ScreenToClient(&rectWindow);
	sizeRelChange.cx = rectWindow.Width() - rectParent.Width();
	sizeRelChange.cy = rectWindow.Height() - rectParent.Height();

	rectWindow.right -= sizeRelChange.cx;
	rectWindow.bottom -= sizeRelChange.cy;
	// Then resize the sheet
	MoveWindow(&rectWindow);

	// Resize the CTabCtrl
	CTabCtrl* pTab = GetTabControl();
if (pTab)
{
	ASSERT(pTab);
	pTab->GetWindowRect(&rectWindow);
	ScreenToClient(&rectWindow);
	rectWindow.right -= sizeRelChange.cx;
	rectWindow.bottom -= sizeRelChange.cy;
	pTab->MoveWindow(&rectWindow);
}
	// Resize the active page
	CPropertyPage* pPage = GetActivePage();
	if (pPage)
	{
	ASSERT(pPage);
	// Store page size in m_rectPage
	pPage->GetWindowRect(&m_rectPage);
	ScreenToClient(&m_rectPage);
	m_rectPage.right -= sizeRelChange.cx;
	m_rectPage.bottom -= sizeRelChange.cy;
	pPage->MoveWindow(&m_rectPage);
	}
	

}
