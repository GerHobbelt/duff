// SoundOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "OptionsSoundForm.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundOptionsDlg dialog


CSoundOptionsDlg::CSoundOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundOptionsDlg)
	//}}AFX_DATA_INIT
	m_Name = StringFromResource(IDS_OPTIONS_SOUNDS);
}


void CSoundOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundOptionsDlg)
	DDX_Control(pDX, IDC_ENABLED, m_Enabled);
	DDX_Control(pDX, IDC_PROCESS_COMPLETE, m_ProcessCompleteCtrl);
	DDX_Control(pDX, IDC_FOUND_DUPLICATE, m_FoundDuplicateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoundOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CSoundOptionsDlg)
	ON_BN_CLICKED(IDC_BROWSE1, OnBrowse1)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowse2)
	ON_BN_CLICKED(IDC_PLAY1, OnPlay1)
	ON_BN_CLICKED(IDC_PLAY2, OnPlay2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundOptionsDlg message handlers

BOOL CSoundOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadOptions();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



bool CSoundOptionsDlg::GetWavFile(CEdit & EditBox)
{
 CString File;
 
 CFileDialog dlg(TRUE, _T("wav") ,NULL,OFN_HIDEREADONLY, _T("WAV files (*.wav)|*.wav|All Files (*.*)|*.*|") ,this);
	if ( dlg.DoModal() == IDOK )
	{
  File = dlg.GetPathName();
		if ( File.GetLength() ) 
		{
			EditBox.SetWindowText(File);
			return true;
		}
	}
	return false;
}

void CSoundOptionsDlg::OnBrowse1() 
{
 GetWavFile(m_FoundDuplicateCtrl);
}

void CSoundOptionsDlg::OnBrowse2() 
{
 GetWavFile(m_ProcessCompleteCtrl);
}

void CSoundOptionsDlg::OnPlay1() 
{
	CString Temp;
	m_FoundDuplicateCtrl.GetWindowText(Temp);
	PlaySoundFile ( Temp );
}

void CSoundOptionsDlg::OnPlay2() 
{
	CString Temp;
	m_ProcessCompleteCtrl.GetWindowText(Temp);
	PlaySoundFile ( Temp );
	
}

void CSoundOptionsDlg::OnOK() 
{
}

void CSoundOptionsDlg::OnCancel() 
{
}


bool CSoundOptionsDlg::SaveOptions()
{
	CString sTemp;

	// 'enabled' ( checkbox )
	m_pDuffOptions->Sound.Enabled = m_Enabled.GetCheck() == BST_CHECKED;
 //

	// 'found duplicate' ( edit )
	m_FoundDuplicateCtrl.GetWindowText( sTemp ); 
 _tcscpy (m_pDuffOptions->Sound.FoundDuplicate,  sTemp);
 //

	// 'process complete' ( edit )
	m_ProcessCompleteCtrl.GetWindowText( sTemp );
 _tcscpy (m_pDuffOptions->Sound.ProcessComplete, sTemp);
 //

 return true;
}

bool CSoundOptionsDlg::LoadOptions()
{

	m_Enabled.SetCheck( m_pDuffOptions->Sound.Enabled ? BST_CHECKED : BST_UNCHECKED );
 m_FoundDuplicateCtrl.SetWindowText( m_pDuffOptions->Sound.FoundDuplicate );
	m_ProcessCompleteCtrl.SetWindowText( m_pDuffOptions->Sound.ProcessComplete );

	return true;
}


