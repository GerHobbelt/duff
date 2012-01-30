#if !defined(AFX_DUPLICATELISTHEADERCTRL_H__4095E252_A326_4D46_A7A2_8C6EC19509DC__INCLUDED_)
#define AFX_DUPLICATELISTHEADERCTRL_H__4095E252_A326_4D46_A7A2_8C6EC19509DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DuplicateListHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDuplicateListHeaderCtrl window

class CDuplicateListHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	int SetSortImage( int , bool);
	CDuplicateListHeaderCtrl();
	virtual ~CDuplicateListHeaderCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDuplicateListHeaderCtrl)
	//}}AFX_VIRTUAL

// Implementation

protected:
	int	 m_nSortCol;
	bool m_bSortAsc;


	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );


	// Generated message map functions
protected:
	//{{AFX_MSG(CDuplicateListHeaderCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUPLICATELISTHEADERCTRL_H__4095E252_A326_4D46_A7A2_8C6EC19509DC__INCLUDED_)
