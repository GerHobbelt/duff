// MarkerOptionsForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "OptionsMarkerForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// CMarkerOptionsForm dialog


CMarkerOptionsForm::CMarkerOptionsForm(CWnd* pParent /*=NULL*/)
	: CDialog(CMarkerOptionsForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMarkerOptionsForm)
	//}}AFX_DATA_INIT
	m_Name = StringFromResource(IDS_OPTIONS_MARKERS);
}


void CMarkerOptionsForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkerOptionsForm)
	DDX_Control(pDX, IDC_MARK_AT_LEAST_ONE, m_MarkAtLeastOne);
	DDX_Control(pDX, IDC_CLEAR_MARKS, m_ClearMarks);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMarkerOptionsForm, CDialog)
	//{{AFX_MSG_MAP(CMarkerOptionsForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkerOptionsForm message handlers

BOOL CMarkerOptionsForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadOptions();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMarkerOptionsForm::OnOK() 
{
}

void CMarkerOptionsForm::OnCancel() 
{
}


bool CMarkerOptionsForm::SaveOptions()
{

	// 'mark mode' ( radio button group )
	m_pDuffOptions->Marker.MarkMode = GetCheckedRadioButton(IDC_MODE_SINGLE,IDC_MODE_MULTIPLE);
	switch ( m_pDuffOptions->Marker.MarkMode )
	{
	 case IDC_MODE_SINGLE:
	 default:
   m_pDuffOptions->Marker.MarkMode = 0;
		break;

	 case IDC_MODE_MULTIPLE:
   m_pDuffOptions->Marker.MarkMode = 1;
	 break;
	}
 //

	// 'no difference option' ( checkbox )
	m_pDuffOptions->Marker.MarkAtLeastOne = m_MarkAtLeastOne.GetCheck() == BST_CHECKED;
	//
 
	// 'clear marks' ( checkbox )
	m_pDuffOptions->Marker.ClearMarks = m_ClearMarks.GetCheck() == BST_CHECKED;
	//

 return true;
}

bool CMarkerOptionsForm::LoadOptions()
{

	// 'mark mode' ( radio button group )
 switch ( m_pDuffOptions->Marker.MarkMode )
	{
	 case 1:
			CheckRadioButton(IDC_MODE_SINGLE,IDC_MODE_MULTIPLE,IDC_MODE_MULTIPLE);
  break;

	 case 0:
	 default:
			CheckRadioButton(IDC_MODE_SINGLE,IDC_MODE_MULTIPLE,IDC_MODE_SINGLE);
		break;
	}
	//
	
	// 'no difference option' ( checkbox )
	m_MarkAtLeastOne.SetCheck(m_pDuffOptions->Marker.MarkAtLeastOne ? BST_CHECKED : BST_UNCHECKED);
	//

	// 'clear marks' ( checkbox )
 m_ClearMarks.SetCheck(m_pDuffOptions->Marker.ClearMarks ? BST_CHECKED : BST_UNCHECKED);
 //

	return true;
}


