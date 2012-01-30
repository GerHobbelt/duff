// FileMP3DataLayerForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "LayerMP3DataForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileMP3DataLayerForm dialog


CFileMP3DataLayerForm::CFileMP3DataLayerForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileMP3DataLayerForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileMP3DataLayerForm)
	//}}AFX_DATA_INIT
}


void CFileMP3DataLayerForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileMP3DataLayerForm)
	DDX_Control(pDX, IDC_SIZETEXT, m_SizeText);
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileMP3DataLayerForm, CDialog)
	//{{AFX_MSG_MAP(CFileMP3DataLayerForm)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnReleasedCaptureSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER, OnCustomDrawSlider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileMP3DataLayerForm message handlers

BOOL CFileMP3DataLayerForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 m_Slider.SetRangeMin(0);
	m_Slider.SetRangeMax(1001);
	m_Slider.SetTicFreq(10);
	m_Slider.SetPos(1);
	OnReleasedCaptureSlider(NULL,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileMP3DataLayerForm::OnReleasedCaptureSlider(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
// MessageBox(	"OnReleasedCaptureSlider");
 CString TempStr;
	int pos = m_Slider.GetPos();
	if (pos == 1001)
	{
		TempStr.Format( _T("Anything") );
	}
	else
	{
	 TempStr.Format( _T("%dKB ") ,pos);
	}
	m_SizeText.SetWindowText(TempStr);
	if (pResult) *pResult = 0;
}

void CFileMP3DataLayerForm::OnCustomDrawSlider(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedCaptureSlider(NULL,NULL);
	*pResult = 0;
}
