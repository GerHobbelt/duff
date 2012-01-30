// FilenameSelectionForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "MarkerFilenameForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilenameMarkerForm dialog


CFilenameMarkerForm::CFilenameMarkerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFilenameMarkerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilenameMarkerForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFilenameMarkerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilenameMarkerForm)
	DDX_Control(pDX, IDC_CASE_SENSITIVE, m_CaseSensitive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilenameMarkerForm, CDialog)
	//{{AFX_MSG_MAP(CFilenameMarkerForm)
	ON_BN_CLICKED(IDC_LONGEST, OnLongest)
	ON_BN_CLICKED(IDC_CONTAIN, OnContain)
	ON_BN_CLICKED(IDC_LOWERCASE, OnLowercase)
	ON_BN_CLICKED(IDC_SHORTEST, OnShortest)
	ON_BN_CLICKED(IDC_DONTCONTAIN, OnDontcontain)
	ON_BN_CLICKED(IDC_UPPERCASE, OnUppercase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenameMarkerForm message handlers

BOOL CFilenameMarkerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	this->CheckRadioButton(IDC_LONGEST,IDC_UPPERCASE,IDC_LONGEST);
OnLongest() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFilenameMarkerForm::OnLongest() 
{
 if ( GetCheckedRadioButton(IDC_CONTAIN,IDC_DONTCONTAIN) == IDC_CONTAIN || 
		   GetCheckedRadioButton(IDC_CONTAIN,IDC_DONTCONTAIN) ==  IDC_DONTCONTAIN )
	{
	GetDlgItem(IDC_CONTAINTEXT)->EnableWindow(true);
		GetDlgItem(IDC_CASE_SENSITIVE)->EnableWindow(true);
	}
else
{
		GetDlgItem(IDC_CONTAINTEXT)->EnableWindow(false);
		GetDlgItem(IDC_CASE_SENSITIVE)->EnableWindow(false);

}

}

void CFilenameMarkerForm::OnContain() 
{
OnLongest() ;
}

void CFilenameMarkerForm::OnLowercase() 
{
	OnLongest() ;

}

void CFilenameMarkerForm::OnShortest() 
{
	OnLongest() ;

}

void CFilenameMarkerForm::OnDontcontain() 
{
	OnLongest() ;

}

void CFilenameMarkerForm::OnUppercase() 
{OnLongest() ;

}

void CFilenameMarkerForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFilenameMarkerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}
