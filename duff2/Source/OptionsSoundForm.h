#if !defined(AFX_SOUNDOPTIONSDLG_H__E82D8781_66CE_42E4_B62F_AEADFB996365__INCLUDED_)
#define AFX_SOUNDOPTIONSDLG_H__E82D8781_66CE_42E4_B62F_AEADFB996365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoundOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoundOptionsDlg dialog

#include "DuffOptionsConfigDlg.h"

class CSoundOptionsDlg : public CDialog, public CDuffOptionsConfigDlg
{

 friend class COptionsPropertyPage;

public:
	CSoundOptionsDlg(CWnd* pParent = NULL);   // standard constructor

	virtual bool SaveOptions();
	virtual bool LoadOptions();

private:
 bool GetWavFile(CEdit & EditBox);

// Dialog Data
	//{{AFX_DATA(CSoundOptionsDlg)
	enum { IDD = IDD_OPTIONS_SOUNDS_FORM };
	CButton	m_Enabled;
	CEdit	m_ProcessCompleteCtrl;
	CEdit	m_FoundDuplicateCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
//	CCheckListBox m_SoundsListBox;

	// Generated message map functions
	//{{AFX_MSG(CSoundOptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse1();
	afx_msg void OnBrowse2();
	afx_msg void OnPlay1();
	afx_msg void OnPlay2();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDOPTIONSDLG_H__E82D8781_66CE_42E4_B62F_AEADFB996365__INCLUDED_)
