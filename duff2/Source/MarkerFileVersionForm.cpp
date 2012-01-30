// FileVersionMarkerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileVersionForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileVersionMarkerForm dialog


CFileVersionMarkerForm::CFileVersionMarkerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileVersionMarkerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileVersionMarkerForm)
	//}}AFX_DATA_INIT
}


void CFileVersionMarkerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileVersionMarkerForm)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileVersionMarkerForm, CDialog)
	//{{AFX_MSG_MAP(CFileVersionMarkerForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileVersionMarkerForm message handlers

BOOL CFileVersionMarkerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton (IDC_FILE_VERSION_OLDEST,IDC_PRODUCT_VERSION_NEWEST,IDC_FILE_VERSION_OLDEST);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileVersionMarkerForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFileVersionMarkerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}
