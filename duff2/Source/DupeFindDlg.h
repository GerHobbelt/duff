#if !defined(AFX_DUPEFINDDLG_H__D61D8419_10D7_4F38_83A3_30A57F467528__INCLUDED_)
#define AFX_DUPEFINDDLG_H__D61D8419_10D7_4F38_83A3_30A57F467528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DupeFindDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDupeFindDlg dialog



class CDupeFindDlg : public CDialog
{
// Construction
public:
	void SetDupeDlg(CWnd*);
	CDupeFindDlg(CWnd* pParent = NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDupeFindDlg)
	enum { IDD = IDD_DUPE_FIND_DIALOG };
	CCheckListBox	m_Columns;
	BOOL	m_MatchCase;
	CString	m_Text;
	BOOL	m_WholeWordOnly;
	int		m_SelectOption;
	int		m_Direction;
	BOOL	m_ClearCurSel;
	BOOL	m_Not;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDupeFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 CWnd *m_pDupePage;
 bool m_bShownBefore;
	// Generated message map functions
	//{{AFX_MSG(CDupeFindDlg)
	afx_msg void OnFind();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUPEFINDDLG_H__D61D8419_10D7_4F38_83A3_30A57F467528__INCLUDED_)
