// FileLocationMarkerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileLocationForm.h"
#include "FilenameEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFileLocationMarkerForm dialog


CFileLocationMarkerForm::CFileLocationMarkerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileLocationMarkerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileLocationMarkerForm)
	//}}AFX_DATA_INIT
}


void CFileLocationMarkerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileLocationMarkerForm)
	DDX_Control(pDX, IDC_PATH, m_Path);
	DDX_Control(pDX, IDC_SUBDIRS, m_SubDirs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileLocationMarkerForm, CDialog)
	//{{AFX_MSG_MAP(CFileLocationMarkerForm)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileLocationMarkerForm message handlers


BOOL CFileLocationMarkerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton(IDC_IN_DIR,IDC_NOTIN_DIR,IDC_IN_DIR);
	m_SubDirs.SetCheck(BST_CHECKED);
	
/*
 CFileType ft;
	ft.Description = "All Files (*.*)";
	ft.Extensions  = "*.*";
	m_Path.AddFileType(ft);

	ft.Description = "Sound Files (*.mp3; *.wav)";
	ft.Extensions  = "*.mp3;*.wav";
	m_Path.AddFileType(ft);
*/
	m_Path.SetActionType( CFilenameEdit::AT_READ );
 m_Path.SetEditType( CFilenameEdit::ET_FOLDER );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileLocationMarkerForm::OnBrowse() 
{
 m_Path.Browse();
}

void CFileLocationMarkerForm::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CFileLocationMarkerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

