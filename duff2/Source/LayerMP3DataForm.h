#if !defined(AFX_FILEMP3DATALAYERFORM_H__26D49630_8ECF_4B9C_95DF_52247BA994B5__INCLUDED_)
#define AFX_FILEMP3DATALAYERFORM_H__26D49630_8ECF_4B9C_95DF_52247BA994B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileMP3DataLayerForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileMP3DataLayerForm dialog

class CFileMP3DataLayerForm : public CDialog
{
// Construction
public:
	CFileMP3DataLayerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileMP3DataLayerForm)
	enum { IDD = IDD_FILE_MP3DATA_LAYER_FORM };
	CStatic	m_SizeText;
	CSliderCtrl	m_Slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileMP3DataLayerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileMP3DataLayerForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedCaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDrawSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEMP3DATALAYERFORM_H__26D49630_8ECF_4B9C_95DF_52247BA994B5__INCLUDED_)
