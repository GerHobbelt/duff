// FileAttributesFilterForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "FilterFileAttributesForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileAttributesFilterForm dialog


CFileAttributesFilterForm::CFileAttributesFilterForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileAttributesFilterForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAttributesFilterForm)
	//}}AFX_DATA_INIT
}


void CFileAttributesFilterForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAttributesFilterForm)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAttributesFilterForm, CDialog)
	//{{AFX_MSG_MAP(CFileAttributesFilterForm)
	ON_BN_CLICKED(IDC_ATTRIBUTES_ANY, OnAttributesAny)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAttributesFilterForm message handlers

BOOL CFileAttributesFilterForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_AttributesList.SubclassDlgItem(IDC_ATTRIBUTES_LIST,this);
	m_AttributesList.AddString( _T(" Hidden") );
	m_AttributesList.AddString( _T(" System") );
	m_AttributesList.AddString( _T(" Read-only") );
	m_AttributesList.AddString( _T(" Archived") );
	m_AttributesList.AddString( _T(" Compressed") );
	m_AttributesList.AddString( _T(" Encrypted") );
	m_AttributesList.AddString( _T(" Temporary") );
 m_AttributesList.SetCheckStyle(BS_AUTO3STATE);

	OnAttributesAny();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileAttributesFilterForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFileAttributesFilterForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CFileAttributesFilterForm::OnAttributesAny() 
{
 for (register int i = 0; i < m_AttributesList.GetCount(); i++)
	{
		m_AttributesList.SetCheck(i,BST_INDETERMINATE);
	}	
}
