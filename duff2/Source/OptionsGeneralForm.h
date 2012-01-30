#if !defined(AFX_OPTIONSGENERALFORM_H__C565CD0B_1F78_48FB_B4D7_9372516D984F__INCLUDED_)
#define AFX_OPTIONSGENERALFORM_H__C565CD0B_1F78_48FB_B4D7_9372516D984F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneralForm.h : header file
//

#include "numedit.h"
#include "DuffOptionsConfigDlg.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneralForm dialog

class COptionsGeneralForm : public CDialog, public CDuffOptionsConfigDlg
{
// Construction
public:
	COptionsGeneralForm(CWnd* pParent = NULL);   // standard constructor


	virtual bool SaveOptions();
	virtual bool LoadOptions();

// Dialog Data
	//{{AFX_DATA(COptionsGeneralForm)
	enum { IDD = IDD_OPTIONS_GENERAL };
	CComboBox	m_ThreadPriority;
	CNumEdit	m_UpdateInterval;
	CButton	m_NoAccessRetry;
	CButton	m_AutoScrollDupeList;
	CListBox	m_ToolTipTexts;
	CEdit	m_ToolTipFormat;
	CButton	m_ShowToolTips;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsGeneralForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsGeneralForm)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnShowTooltips();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTooltipTexts();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSGENERALFORM_H__C565CD0B_1F78_48FB_B4D7_9372516D984F__INCLUDED_)
