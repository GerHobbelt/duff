// FileSizeMarkerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileSizeForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSizeMarkerForm dialog


CFileSizeMarkerForm::CFileSizeMarkerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSizeMarkerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSizeMarkerForm)
	//}}AFX_DATA_INIT
}


void CFileSizeMarkerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSizeMarkerForm)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSizeMarkerForm, CDialog)
	//{{AFX_MSG_MAP(CFileSizeMarkerForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSizeMarkerForm message handlers

BOOL CFileSizeMarkerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 CheckRadioButton(IDC_SMALLEST,IDC_BIGGEST,IDC_SMALLEST);
 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CFileSizeMarkerForm::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CFileSizeMarkerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}
