#if !defined(AFX_DUPLICATELISTCTRL_H__3E6FA09A_F557_41E7_865B_DB182255DF78__INCLUDED_)
#define AFX_DUPLICATELISTCTRL_H__3E6FA09A_F557_41E7_865B_DB182255DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DuplicateListCtrl.h : header file
//

#include <afxtempl.h>

#include "FileInfo.h"
#include "DupeFindDlg.h"
#include "DuplicateListHeaderCtrl.h"
#include "ColumnFilename.h"
#include "ColumnFileSize.h"
#include "ColumnFileVersion.h"
#include "ColumnFileAttributes.h"
#include "ColumnFilenameFull.h"
#include "ColumnFileLocation.h"
#include "ColumnFileCreationDate.h"
#include "ColumnFileModifyDate.h"
#include "ColumnFileAccessDate.h"
#include "ColumnFileTypeDesc.h"
#include "ColumnDupeSet.h"

/////////////////////////////////////////////////////////////////////////////
// CDuplicateListCtrl window


class CDuplicateListCtrl : public CListCtrl
{

	friend class CDupeFindDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDuplicateListCtrl)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

public:
 enum ControlTypes {
		                  UC_TOTAL_CHECKED =  1, UC_NUM_SELECTED =  2, UC_SELECTED_BYTES    =  4, UC_MARKED_BYTES = 8, 
		                  UC_TOTAL_COUNT   = 16, UC_TOTAL_BYTES  = 32, UC_TOTAL_DUPELICATES = 64, UC_DUPELICATE_BYTES = 128
																			};

public:
	CDuplicateListCtrl();
	virtual ~CDuplicateListCtrl();
 void          AddItem( CFileInfo *);
	void          UpdateListMarks();
	void          SetTotalCheckedCtrl(CEdit *pEdit);
	void          SetNumSelectedCtrl(CEdit *pEdit) ;
	void          SetSelectedBytesCtrl(CEdit *pEdit);
	void          SetMarkedBytesCtrl(CEdit *pEdit);
	void          SetTotalCountCtrl(CEdit *pEdit);
	void          SetTotalBytesCtrl(CEdit *pEdit);

	void          SetTotalDuplicateCtrl(CEdit *pEdit);
	void          SetDuplicateBytesCtrl(CEdit *pEdit);

	ULONGLONG GetTotalFilesCounter() const { return m_TotalFilesCounter; }

 static	CArray <CDuplicateListColumn *, CDuplicateListColumn* > m_Columns;

private:
	CDuplicateListHeaderCtrl	m_HeaderCtrl;

	WCHAR     *m_pwchTip;
	CHAR      *m_pchTip;
	ULONGLONG  m_TotalBytesCounter;
	ULONGLONG  m_SelectedBytesCounter;
	ULONGLONG  m_MarkedBytesCounter;
	ULONGLONG  m_TotalFilesCounter;
	ULONGLONG  m_MarkedCounter;
	ULONGLONG  m_SelectedCounter;
	ULONGLONG  m_DuplicateSetCounter;
	ULONGLONG  m_DuplicateCounter;
	ULONGLONG  m_DuplicateBytesCounter;
	bool       m_MultiModifyInProgress;
	bool       m_bToolTipCtrlCustomizeDone;
	CEdit     *m_pTotalCheckedCtrl;
	CEdit     *m_pNumSelectedCtrl;
	CEdit     *m_pSelectedBytesCtrl;
	CEdit     *m_pMarkedBytesCtrl;
	CEdit     *m_pTotalCountCtrl;
	CEdit     *m_pTotalBytesCtrl;
	CEdit     *m_pTotalDupeCtrl;
	CEdit     *m_pDupeBytesCtrl;

	int           m_OldListWidth;

	CDupeFindDlg  m_DupeFindDlg;

	CFilenameColumn         m_ColumnFilename;
	CFullFilenameColumn     m_ColumnFullFilename;
	CFileSizeColumn         m_ColumnFileSize;
	CFileVersionColumn      m_ColumnFileVersion;
	CFileAttributesColumn   m_ColumnAttributes;
	CFileLocationColumn     m_ColumnLocation;
	CFileCreationDateColumn m_ColumnFileCreationDate;
	CFileModifyDateColumn   m_ColumnFileModifyDate;
	CFileAccessDateColumn   m_ColumnFileAccessDate;
	CFileTypeDescColumn     m_ColumnFileTypeDesc;
	CDupeSetColumn          m_ColumnDupeSet;

private:

	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	virtual int CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const;
	static  int CALLBACK CompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void        UpdateCtrls(UINT);
	bool        DoFind();
 void        SetupColumns();
	void        DoItemPopupMenu(const POINT &);
	void        DoColumnPopupMenu(int);
	void        RebuildColumns();
	void        UpdateColumnWidths(int iNewListWidth = -1, int iNewListHeight = -1);
	int         AbsoluteIndexToVisibleIndex(int AbsoluteIndex);
	int         VisibleIndexToAbsoluteIndex(int VisibleIndex);
	int         AutoSizeColumn(int);

//	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );

	// Generated message map functions
protected:

	//{{AFX_MSG(CDuplicateListCtrl)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDoubleClickItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUPLICATELISTCTRL_H__3E6FA09A_F557_41E7_865B_DB182255DF78__INCLUDED_)
