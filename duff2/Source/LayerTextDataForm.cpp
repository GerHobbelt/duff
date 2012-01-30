// FileTextDataLayerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "LayerTextDataForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "CharEncSch.h"


/////////////////////////////////////////////////////////////////////////////
// CFileTextDataLayerForm dialog


CFileTextDataLayerForm::CFileTextDataLayerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTextDataLayerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileTextDataLayerForm)
	//}}AFX_DATA_INIT
}


void CFileTextDataLayerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTextDataLayerForm)
	DDX_Control(pDX, IDC_TEXT_ENCODING_FORMATS, m_TextEncodingFormats);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileTextDataLayerForm, CDialog)
	//{{AFX_MSG_MAP(CFileTextDataLayerForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTextDataLayerForm message handlers

BOOL CFileTextDataLayerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

/*
 for(int i = 0; i < sCharacterEncodingScheme::Count; i++)
	{
 	m_TextEncodingFormats.AddString(CharEncSchemes[i].Name);
	}
*/	

	m_TextEncodingFormats.AddString( _T(" ANSI") );
	m_TextEncodingFormats.AddString( _T(" UTF-8") );
	m_TextEncodingFormats.AddString( _T(" Unicode Little Endian (UTF-16LE)") );
	m_TextEncodingFormats.AddString( _T(" Unicode Big Endian (UTF-16BE)") );




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileTextDataLayerForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFileTextDataLayerForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}
