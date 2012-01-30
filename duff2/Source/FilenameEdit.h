#if !defined(AFX_FILENAMEEDIT_H__12DC48C0_0109_45EF_B0D5_EC8729CD6993__INCLUDED_)
#define AFX_FILENAMEEDIT_H__12DC48C0_0109_45EF_B0D5_EC8729CD6993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilenameEdit.h : header file
//

#include <afxtempl.h>

class CFileType
{
public:
	CFileType();
	~CFileType();
	CString Extensions;
	CString Description;
	bool Default;
};

inline CFileType::CFileType()
{}
inline CFileType::~CFileType()
{}

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit window

class CFilenameEdit : public CEdit
{
// Construction
public:

	enum EditType { ET_FILE, ET_FOLDER };
	enum ActionType { AT_READ, AT_WRITE };
	CFilenameEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilenameEdit)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Browse();
	bool IsGood();
	LPCTSTR GetDefaultExt();
	CString GetFilter();
	virtual ~CFilenameEdit();
	void SetEditType(EditType et) { m_EditType = et; }
	void SetActionType(ActionType at) { m_ActionType = at; }
	void       AddFileType(CFileType &);
	// Generated message map functions
protected:
	CMenu      m_PopupMenu;
	EditType   m_EditType;
	bool       m_EnableMultipleSelections;
	ActionType m_ActionType;
 CArray<CFileType,CFileType&> m_FileTypes;
	CString m_DefaultFilename;
 CString m_DefaultExt;
 CString m_sWindowTitle;

	//{{AFX_MSG(CFilenameEdit)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMEEDIT_H__12DC48C0_0109_45EF_B0D5_EC8729CD6993__INCLUDED_)
