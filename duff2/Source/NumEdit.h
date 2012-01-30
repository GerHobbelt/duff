#if !defined(AFX_NUMEDIT_H__400A2507_D65B_4570_9DE1_E7C780751DB6__INCLUDED_)
#define AFX_NUMEDIT_H__400A2507_D65B_4570_9DE1_E7C780751DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEdit window

class CNumEdit : public CEdit
{
// Construction
public:
	CNumEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumEdit();

private:
	CString m_OldText;
	int     m_SelStart;
	int     m_SelEnd;

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumEdit)
	afx_msg void OnUpdate();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__400A2507_D65B_4570_9DE1_E7C780751DB6__INCLUDED_)
