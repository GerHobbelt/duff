// LayersPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageLayers.h"
#include "duffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include "Layers.h"
#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;
//extern  int g_FileComparisonLayersCount;
//extern  CFileComparisonLayer g_FileComparisonLayers[];

/////////////////////////////////////////////////////////////////////////////
// CLayersPropertyPage property page

IMPLEMENT_DYNCREATE(CLayersPropertyPage, CResizablePage)

CLayersPropertyPage::CLayersPropertyPage() : CResizablePage(CLayersPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CLayersPropertyPage)
	//}}AFX_DATA_INIT
}

CLayersPropertyPage::~CLayersPropertyPage()
{
}

void CLayersPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayersPropertyPage)
	DDX_Control(pDX, IDC_NOCONFIG, m_NoConfigText);
	DDX_Control(pDX, IDC_LAYER_DESCRIPTION, m_LayerDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayersPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CLayersPropertyPage)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LAYER_CHECKLIST, OnSelchangeLayerChecklist)
	ON_BN_CLICKED(IDC_LAYER_MOVE_UP, OnLayerMoveUp)
	ON_BN_CLICKED(IDC_LAYER_MOVE_DOWN, OnLayerMoveDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayersPropertyPage message handlers
//CFilenameLayer theFilenameLayer;



BOOL CLayersPropertyPage::OnInitDialog() 
{
	CDialog* pConfigDlg;
	CFileComparisonLayer *pFCL;
	CRect rcSheet; 
 int Index;


	// base class init
	CResizablePage::OnInitDialog();
	//

	// preset resize layout
	AddAnchor(IDC_LAYER_CHECKLIST, TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_COMPARISON_LAYERS_FRAME,  TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_LAYER_INFO_FRAME,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_LAYER_DESCRIPTION,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_RADIO_LOGIC_OR,  BOTTOM_LEFT);
	AddAnchor(IDC_RADIO_LOGIC_AND,  BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_LOGIC,  BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_ORDER,  BOTTOM_LEFT);
	AddAnchor(IDC_LAYER_MOVE_UP,  BOTTOM_LEFT);
	AddAnchor(IDC_LAYER_MOVE_DOWN,  BOTTOM_LEFT);
	AddAnchor(IDC_LAYER_CONFIG_FRAME, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROPERTYSHEET,  TOP_LEFT, BOTTOM_RIGHT);
 //

 // subclass checklistbox
	m_LayerCheckList.SubclassDlgItem(IDC_LAYER_CHECKLIST,this);
 //
	
	// load the file comparison layers into the checklistbox
	for (Index = 0; Index < g_DupeFileFind.GetFileComparisonLayerArray()->GetSize(); Index++)
	{
		pFCL = g_DupeFileFind.GetFileComparisonLayerArray()->GetAt(Index);
		pConfigDlg = pFCL->GetForm();		
	 	
		if (pConfigDlg)
		{
			pConfigDlg->Create ( pFCL->GetFormID(), this );
			GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
			ScreenToClient( &rcSheet );
			pConfigDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
//?			pConfigDlg->UpdateData();
 	}
  m_LayerCheckList.AddString ( pFCL->GetName() );
		m_LayerCheckList.SetItemData ( Index,(DWORD)pFCL );

		if ( ! g_DupeFileFind.GetFileComparisonLayerArray()->GetAt(Index)->IsComplete() )
		{
			m_LayerCheckList.Enable(Index,false);
		}
	}


 // load initial config form
	if ( m_LayerCheckList.GetCount() != 0 )
	{
		m_LayerCheckList.SetCurSel(0);
  UpdateForm();	
	}
	//

	// select the 'or' logic radio button ( default )
	CheckRadioButton(IDC_RADIO_LOGIC_AND, IDC_RADIO_LOGIC_OR, IDC_RADIO_LOGIC_OR);
 //

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CLayersPropertyPage::UpdateForm()
{
	CDialog* pDlg;
 CFileComparisonLayer *pSelectedFCL;
 CFileComparisonLayer *pCurrentFCL;

	if ( m_LayerCheckList.GetCurSel()  != LB_ERR)
	{

		pSelectedFCL = 	(CFileComparisonLayer *)m_LayerCheckList.GetItemData( m_LayerCheckList.GetCurSel());
		m_LayerDescription.SetWindowText( pSelectedFCL->GetDescription()  );


		for (int Index = 0; Index < g_DupeFileFind.GetFileComparisonLayerArray()->GetSize(); Index++)
		{
			pCurrentFCL = g_DupeFileFind.GetFileComparisonLayerArray()->GetAt(Index);
			pDlg = pCurrentFCL->GetForm();
	
				
			if (pDlg )
			{
				pDlg->ShowWindow( pCurrentFCL == pSelectedFCL ? SW_SHOW : SW_HIDE);
		 }
		}

	
		pDlg = pSelectedFCL->GetForm();
		if (pDlg)
		{
			m_NoConfigText.ShowWindow(SW_HIDE);
		}
		else
		{
			m_NoConfigText.ShowWindow(SW_SHOW);
		}
	}

}

BOOL CLayersPropertyPage::PreTranslateMessage(MSG* pMsg) 
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


void CLayersPropertyPage::OnSize(UINT nType, int cx, int cy) 
{
	CResizablePage::OnSize(nType, cx, cy);
/*	
	
	CDialog* pDlg;
	
		if ( GetDlgItem( IDC_PROPERTYSHEET ) )
		for (int Index = 0; Index < g_DupeFileFind.m_FileComparisonLayers.GetSize(); Index++)
	{
				pDlg = g_DupeFileFind.m_FileComparisonLayers.ElementAt(Index)->m_pForm;
				
	if (pDlg)
		{
 		CRect rcSheet;
	//	pDlg->Create(g_DupeFileFind.m_FileComparisonLayers.ElementAt(Index)->m_FormID, this);
		GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
		ScreenToClient( &rcSheet );
		pDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
pDlg->RedrawWindow();
	// pDlg->UpdateData();
	}	
		}*/
}

void CLayersPropertyPage::OnSelchangeLayerChecklist() 
{
UpdateForm();	
}

void CLayersPropertyPage::OnLayerMoveUp() 
{
 int sel = m_LayerCheckList.GetCurSel();
	CString strTemp0;
	DWORD   dwTemp;
 int iCheck;
 
	if ( sel-1 >=0 )
	{
		m_LayerCheckList.GetText(sel,strTemp0);
		dwTemp = m_LayerCheckList.GetItemData(sel);
  iCheck = m_LayerCheckList.GetCheck(sel);

		m_LayerCheckList.DeleteString(sel);
  m_LayerCheckList.InsertString(sel-1,strTemp0);
  m_LayerCheckList.SetItemData(sel-1,dwTemp);
  m_LayerCheckList.SetCurSel(sel-1);
		m_LayerCheckList.SetCheck(sel-1,iCheck);
	}
}

void CLayersPropertyPage::OnLayerMoveDown() 
{
 int sel = m_LayerCheckList.GetCurSel();
	CString strTemp0, strTemp1, strTemp2;
	DWORD   dwTemp;
 int iCheck;

	if ( sel+1 < m_LayerCheckList.GetCount() )
	{
	 // temp = list2
		m_LayerCheckList.GetText(sel,strTemp0);
		dwTemp = m_LayerCheckList.GetItemData(sel);
  iCheck = m_LayerCheckList.GetCheck(sel);
  
		m_LayerCheckList.DeleteString(sel);
  m_LayerCheckList.InsertString(sel+1,strTemp0);
  m_LayerCheckList.SetItemData(sel+1,dwTemp);
  m_LayerCheckList.SetCurSel(sel+1);
		m_LayerCheckList.SetCheck(sel+1,iCheck);
	}

}

int CLayersPropertyPage::InitDupeFileFind(CDuplicateFileFind & dff)
{
 int x;
 bool Cancel = false;

	// save all dialog data for file comparison layers
	//for ( x = 0; x < m_LayerCheckList.GetCount(); x ++)
	x = 0;
	while ( !Cancel && x < m_LayerCheckList.GetCount() )
	{
		if ( ! dff.GetFileComparisonLayerArray()->GetAt(x)->UpdateData(true) )
		{
			((CResizablePropertySheet*)GetParent())->SetActivePage(this);
   m_LayerCheckList.SetCurSel(x);
			UpdateForm();	
			CDialog *pDlg = ((CFileComparisonLayer *)m_LayerCheckList.GetItemData(x))->GetForm();
			if (pDlg) pDlg->SetFocus();
			Cancel = true;
			break;
		}
		x++;
	}

	if ( Cancel ) 
		return x;

	// select the chosen file comparison layers
	for (x = 0; x < m_LayerCheckList.GetCount(); x++)
	{
		dff.SelectFileComparisonLayer(x, m_LayerCheckList.GetCheck(x) == BST_CHECKED );
	}
	//

	// set layer logic
	switch ( GetCheckedRadioButton(IDC_RADIO_LOGIC_AND, IDC_RADIO_LOGIC_OR) )
	{
	case IDC_RADIO_LOGIC_AND:
	 dff.SetLayerLogic( LOGIC_AND );
		break;
	case IDC_RADIO_LOGIC_OR:
	 dff.SetLayerLogic( LOGIC_OR );
  break;
	default:
	 dff.SetLayerLogic( LOGIC_OR );
  break;
	}
	//
 
	return -1;	
}
