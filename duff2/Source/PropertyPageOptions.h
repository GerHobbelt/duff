#if !defined(AFX_OPTIONSPROPERTYPAGE_H__203E2CD3_41C2_4D63_A69B_DC2DC3BDCE90__INCLUDED_)
#define AFX_OPTIONSPROPERTYPAGE_H__203E2CD3_41C2_4D63_A69B_DC2DC3BDCE90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPropertyPage.h : header file
//

#include "ResizableLib\ResizablePage.h"

// option forms
#include "OptionsGeneralForm.h"
#include "OptionsSoundForm.h"
#include "OptionsMarkerForm.h"
#include "OptionsProcessForm.h"

#include "DuffOptions.h"
#include "DuplicateFileFind.h"
#include "DuplicateFileFindConfigurer.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsPropertyPage dialog

class COptionsPropertyPage : public CResizablePage, public CDuplicateFileFindConfigurer
{
	DECLARE_DYNCREATE(COptionsPropertyPage)

	friend class CDuffDlg;
	friend class CMarkersPropertyPage;
 friend class COptionsPropertyPage;
 friend class CProcessesPropertyPage;

// Construction
public:
	COptionsPropertyPage();
	~COptionsPropertyPage();

private:
	COptionsGeneralForm m_OptionsGeneralForm;
	CSoundOptionsDlg    m_SoundOptionsDlg;
 CMarkerOptionsForm  m_MarkerOptionsForm;
 CProcessOptionsForm m_ProcessOptionsForm;
private:
	void UpdateForm();
	virtual int  InitDupeFileFind(CDuplicateFileFind &);

// Dialog Data
	//{{AFX_DATA(COptionsPropertyPage)
	enum { IDD = IDD_OPTIONS_PAGE };
	CButton	m_OptionTitle;
	CListBox	m_OptionList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(COptionsPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeOptionList();
	afx_msg void OnApplyChanges();
	afx_msg void OnAbortChanges();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPROPERTYPAGE_H__203E2CD3_41C2_4D63_A69B_DC2DC3BDCE90__INCLUDED_)
