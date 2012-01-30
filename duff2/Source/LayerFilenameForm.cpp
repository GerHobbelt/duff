// FilenameLayerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "LayerFilenameForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilenameLayerForm dialog


CFilenameLayerForm::CFilenameLayerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFilenameLayerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilenameLayerForm)
	//}}AFX_DATA_INIT
}


void CFilenameLayerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilenameLayerForm)
	DDX_Control(pDX, IDC_CASE_SENSITIVE, m_CaseSensitive);
	DDX_Control(pDX, IDC_WORD_COUNT, m_WordCountCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilenameLayerForm, CDialog)
	//{{AFX_MSG_MAP(CFilenameLayerForm)
	ON_BN_CLICKED(IDC_MATCH_FILENAMES, OnChangeRadio)
	ON_BN_CLICKED(IDC_MATCH_NOT_FILENAME, OnChangeRadio)
	ON_BN_CLICKED(IDC_MATCH_EXTENSIONS, OnChangeRadio)
	ON_BN_CLICKED(IDC_MATCH_NOT_EXTENSIONS, OnChangeRadio)
	ON_BN_CLICKED(IDC_MATCH_WORDS, OnChangeRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenameLayerForm message handlers


void CFilenameLayerForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFilenameLayerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CFilenameLayerForm::OnChangeRadio() 
{
 BOOL enable = GetCheckedRadioButton(IDC_MATCH_FILENAMES, IDC_MATCH_WORDS) == IDC_MATCH_WORDS;
	m_WordCountCtrl.EnableWindow(enable);
	GetDlgItem(IDC_STATIC_COMMON_WORDS)->EnableWindow(enable);
}

BOOL CFilenameLayerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CheckRadioButton(IDC_MATCH_FILENAMES, IDC_MATCH_WORDS,IDC_MATCH_FILENAMES);
 OnChangeRadio();	

	m_WordCountCtrl.SetWindowText( _T("2") );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
