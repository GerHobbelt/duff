#if !defined(AFX_LAYERSPROPERTYPAGE_H__D57D1922_4899_4AD0_B379_191853D7C05F__INCLUDED_)
#define AFX_LAYERSPROPERTYPAGE_H__D57D1922_4899_4AD0_B379_191853D7C05F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayersPropertyPage.h : header file
//

#include "ResizableLib\ResizablePage.h"
#include "DuplicateFileFind.h"

/////////////////////////////////////////////////////////////////////////////
// CLayersPropertyPage dialog

class CLayersPropertyPage : public CResizablePage
{
	DECLARE_DYNCREATE(CLayersPropertyPage)

 friend class CDuffDlg;

// Construction
public:
	CLayersPropertyPage();
	~CLayersPropertyPage();
	CCheckListBox m_LayerCheckList;

private:
	void UpdateForm();
	int InitDupeFileFind(CDuplicateFileFind &);


// CDragListBox  m_DragListBox;
// Dialog Data
	//{{AFX_DATA(CLayersPropertyPage)
	enum { IDD = IDD_LAYERS_PAGE };
	CStatic	m_NoConfigText;
	CEdit	m_LayerDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLayersPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	// Generated message map functions
	//{{AFX_MSG(CLayersPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeLayerChecklist();
	afx_msg void OnLayerMoveUp();
	afx_msg void OnLayerMoveDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERSPROPERTYPAGE_H__D57D1922_4899_4AD0_B379_191853D7C05F__INCLUDED_)
