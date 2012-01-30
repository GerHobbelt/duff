// FileVersionColumn.h: interface for the CFileVersionColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVERSIONCOLUMN_H__7DE72A3B_0283_43F3_A5D2_B43E16A62DA0__INCLUDED_)
#define AFX_FILEVERSIONCOLUMN_H__7DE72A3B_0283_43F3_A5D2_B43E16A62DA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileVersionColumn : public CDuplicateListColumn  
{
public:
	CFileVersionColumn();
	virtual ~CFileVersionColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileVersionColumn::GetColumnText(CFileInfo* pFileInfo)
{
 return pFileInfo->GetFileVersionStr();
}

inline int CFileVersionColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{
	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->VersionFile == pFileInfo2->VersionFile )
		return 0;
	else 
		if ( pFileInfo1->VersionFile > pFileInfo2->VersionFile )
   return -1;
		else 
			return 1;

}

#endif // !defined(AFX_FILEVERSIONCOLUMN_H__7DE72A3B_0283_43F3_A5D2_B43E16A62DA0__INCLUDED_)
