// DuplicateListColumn.h: interface for the CDuplicateListColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUPLICATELISTCOLUMN_H__EDE8408B_9FD8_42E4_8A4F_171EEA4539A8__INCLUDED_)
#define AFX_DUPLICATELISTCOLUMN_H__EDE8408B_9FD8_42E4_8A4F_171EEA4539A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileInfo.h"

class CDuplicateListColumn  
{
public:
	enum ViewModes { VM_FIXED, VM_VARIABLE, VM_AUTO };
	CDuplicateListColumn();
	virtual ~CDuplicateListColumn();
 virtual CString GetColumnText(CFileInfo*) = 0;
 virtual int CompareItems( CFileInfo*, CFileInfo* ) = 0;
 
	void InitSortColumn();
 static bool IsSortAcending() { return m_bSortAcending; }

	void    SetMode(ViewModes);
	ViewModes     GetMode() const;

 const CString & GetName() const;
 const int &     GetFormat() const;

 void            SetVisible(bool);
	bool            IsVisible() const;
 void            SwitchVisible();
 double          GetPercentWidth() const;
	void            SetPercentWidth(double);

protected:
 static bool m_bSortAcending;
 static CDuplicateListColumn *m_pSortColumn;

protected:
	ViewModes m_Mode;
	CString   m_Name;
	int       m_Format;
	bool      m_Visible;
	double    m_PercentWidth;
};


inline double CDuplicateListColumn::GetPercentWidth() const
{
	return m_PercentWidth;
}

inline	void CDuplicateListColumn::SetPercentWidth(double D)
{
	m_PercentWidth = D;
}


inline void CDuplicateListColumn::InitSortColumn()
{
	if ( this == m_pSortColumn )
	{
		m_bSortAcending = !m_bSortAcending; 
	}

 m_pSortColumn = this;

}

inline void CDuplicateListColumn::SwitchVisible()
{
	m_Visible = !m_Visible;
}

inline void CDuplicateListColumn::SetVisible(bool B)
{
	m_Visible = B;
}

inline bool CDuplicateListColumn::IsVisible() const
{
	return m_Visible;
}

inline const int & CDuplicateListColumn::GetFormat() const
{
	return m_Format;
}

inline void CDuplicateListColumn::SetMode(ViewModes M)
{
 m_Mode = M;
}

inline CDuplicateListColumn::ViewModes CDuplicateListColumn::GetMode() const
{
	return m_Mode;
}

inline const CString & CDuplicateListColumn::GetName() const
{
	return m_Name;
}


#endif // !defined(AFX_DUPLICATELISTCOLUMN_H__EDE8408B_9FD8_42E4_8A4F_171EEA4539A8__INCLUDED_)
