#if !defined(AFX_DIRECTORIESPROPERTYPAGE_H__554BC87B_11E1_4C47_9E1E_9E2F8EB4501B__INCLUDED_)
#define AFX_DIRECTORIESPROPERTYPAGE_H__554BC87B_11E1_4C47_9E1E_9E2F8EB4501B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectoriesPropertyPage.h : header file
//
#include "DuplicateFileFind.h"
#include "ResizableLib\ResizablePage.h"
#include "DuffObject.h"
#include "DuplicateFileFindConfigurer.h"

#define DIR_ATTRIBUTE_HIDDEN     0
#define DIR_ATTRIBUTE_SYSTEM     1
#define DIR_ATTRIBUTE_READONLY   2
#define DIR_ATTRIBUTE_ARCHIVED   3
#define DIR_ATTRIBUTE_COMPRESSED 4
#define DIR_ATTRIBUTE_ENCRYPTED  5
#define DIR_ATTRIBUTE_TEMPORARY  6

/////////////////////////////////////////////////////////////////////////////
// CDirectoriesPropertyPage dialog

class CDirectoriesPropertyPage : public CResizablePage, protected CDuffObject, public CDuplicateFileFindConfigurer
{
	DECLARE_DYNCREATE(CDirectoriesPropertyPage)

		friend class CDuffDlg;
// Construction
public:
	virtual int InitDupeFileFind(CDuplicateFileFind &);
	CDirectoriesPropertyPage();
	~CDirectoriesPropertyPage();

// Dialog Data
	//{{AFX_DATA(CDirectoriesPropertyPage)
	enum { IDD = IDD_DIRECTORIES_PAGE };
	CEdit	m_FileMasks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDirectoriesPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 virtual void LoadSettings();
	virtual void SaveSettings();
	BOOL ValidatePathname(const CString& csPathname, UINT& iPathType) const;
	CString ExpandShortcut(CString& csFilename) const;

private:
	CCheckListBox m_IncludeDirectoriesList;
 CCheckListBox m_AttributesList;

	// Generated message map functions
	//{{AFX_MSG(CDirectoriesPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseInclude();
	afx_msg void OnRemoveSelectedIncludeDirectory();
	afx_msg void OnDropFiles(HDROP dropInfo);
	afx_msg void OnRemoveAllDirectories();
	afx_msg void OnAttributesAny();
	afx_msg void OnDblclkIncludeDirectoriesList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORIESPROPERTYPAGE_H__554BC87B_11E1_4C47_9E1E_9E2F8EB4501B__INCLUDED_)


