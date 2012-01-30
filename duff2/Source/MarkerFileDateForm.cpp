// FileDateMarkerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileDateForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDateMarkerForm dialog


CFileDateMarkerForm::CFileDateMarkerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDateMarkerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDateMarkerForm)
	//}}AFX_DATA_INIT
}


void CFileDateMarkerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDateMarkerForm)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDateMarkerForm, CDialog)
	//{{AFX_MSG_MAP(CFileDateMarkerForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDateMarkerForm message handlers

BOOL CFileDateMarkerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 CheckRadioButton(IDC_MOST_RECENTLY_CREATED,IDC_LEAST_RECENTLY_ACCESSED,IDC_LEAST_RECENTLY_CREATED);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDateMarkerForm::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CFileDateMarkerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}
