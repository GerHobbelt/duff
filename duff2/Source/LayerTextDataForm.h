#if !defined(AFX_FileTextDataLayerFORM_H__338111C5_C04B_4E90_8A9D_3E22803E7D90__INCLUDED_)
#define AFX_FileTextDataLayerFORM_H__338111C5_C04B_4E90_8A9D_3E22803E7D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTextDataLayerForm.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CFileTextDataLayerForm dialog

class CFileTextDataLayerForm : public CDialog
{
// Construction
public:
	CFileTextDataLayerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileTextDataLayerForm)
	enum { IDD = IDD_FILE_TEXT_DATA_LAYER_FORM };
	CCheckListBox	m_TextEncodingFormats;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTextDataLayerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileTextDataLayerForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FileTextDataLayerFORM_H__338111C5_C04B_4E90_8A9D_3E22803E7D90__INCLUDED_)
