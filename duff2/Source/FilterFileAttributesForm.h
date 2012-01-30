#if !defined(AFX_FILEATTRIBUTESFILTERFORM_H__AB10BCDD_839A_4A8C_BC11_84268A18BABF__INCLUDED_)
#define AFX_FILEATTRIBUTESFILTERFORM_H__AB10BCDD_839A_4A8C_BC11_84268A18BABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAttributesFilterForm.h : header file
//

	
#define DIR_ATTRIBUTE_HIDDEN     0
#define DIR_ATTRIBUTE_SYSTEM     1
#define DIR_ATTRIBUTE_READONLY   2
#define DIR_ATTRIBUTE_ARCHIVED   3
#define DIR_ATTRIBUTE_COMPRESSED 4
#define DIR_ATTRIBUTE_ENCRYPTED  5
#define DIR_ATTRIBUTE_TEMPORARY  6


/////////////////////////////////////////////////////////////////////////////
// CFileAttributesFilterForm dialog

class CFileAttributesFilterForm : public CDialog
{

	friend class CFileAttributesFilter;

	// Construction
public:
	CFileAttributesFilterForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileAttributesFilterForm)
	enum { IDD = IDD_FILE_ATTRIBUTES_FILTER_FORM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileAttributesFilterForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 CCheckListBox m_AttributesList;

	// Generated message map functions
	//{{AFX_MSG(CFileAttributesFilterForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAttributesAny();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEATTRIBUTESFILTERFORM_H__AB10BCDD_839A_4A8C_BC11_84268A18BABF__INCLUDED_)
