// DupeFindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "DupeFindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDupeFindDlg dialog


#include "PropertyPageDuplicates.h"

CDupeFindDlg::CDupeFindDlg(CWnd* pParent)
	: CDialog(CDupeFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDupeFindDlg)
	m_MatchCase = FALSE;
	m_Text = _T("");
	m_WholeWordOnly = FALSE;
	m_SelectOption = -1;
	m_Direction = -1;
	m_ClearCurSel = FALSE;
	m_Not = FALSE;
	//}}AFX_DATA_INIT
 m_bShownBefore = false;
}


void CDupeFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDupeFindDlg)
	DDX_Control(pDX, IDC_COLUMNS, m_Columns);
	DDX_Check(pDX, IDC_MATCHCASE, m_MatchCase);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_Check(pDX, IDC_WHOLE_WORD_ONLY, m_WholeWordOnly);
	DDX_Radio(pDX, IDC_SELECT_ALL, m_SelectOption);
	DDX_Radio(pDX, IDC_DIRECTION_UP, m_Direction);
	DDX_Check(pDX, IDC_CLEAR_CURSEL, m_ClearCurSel);
	DDX_Check(pDX, IDC_NOT, m_Not);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDupeFindDlg, CDialog)
	//{{AFX_MSG_MAP(CDupeFindDlg)
	ON_BN_CLICKED(IDOK, OnFind)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDupeFindDlg message handlers

void CDupeFindDlg::OnFind() 
{
	UpdateData(TRUE);
 bool bAtLeastOne = false;
 int i = 0;

	while( i < ((CDuplicateListCtrl*)m_pDupePage)->m_Columns.GetSize() && !bAtLeastOne)
	{
		if ( m_Columns.GetCheck(i) == BST_CHECKED ) bAtLeastOne = true;
		i++;
	}

	if (!bAtLeastOne)
	{
		MessageBox(StringFromResource(IDS_SEARCHDIALOG_SELECTCOLUMN), StringFromResource(IDS_SEARCHDIALOG_SEARCH),MB_ICONINFORMATION | MB_OK);
	}
	else
	{
  if (! ((CDuplicateListCtrl*)m_pDupePage)->DoFind() )
		{
		 MessageBox( StringFromResource(IDS_SEARCHDIALOG_NOT_FOUND) , StringFromResource(IDS_SEARCHDIALOG_SEARCH) ,MB_ICONINFORMATION | MB_OK);
		}
	}

}

void CDupeFindDlg::SetDupeDlg(CWnd *pDlg)
{
 m_pDupePage = pDlg;
}

BOOL CDupeFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 m_Direction = 0;
	m_SelectOption = 0;

	


	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDupeFindDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);


	if (!m_bShownBefore)
	{
		for (int i = 0; i < ((CDuplicateListCtrl*)m_pDupePage)->m_Columns.GetSize(); i++)
		{
			
 		m_Columns.AddString( ((CDuplicateListCtrl*)m_pDupePage)->m_Columns.ElementAt(i)->GetName() );
		}
		m_bShownBefore = true;
	}

 GetDlgItem(IDC_TEXT)->SetFocus();	
}
