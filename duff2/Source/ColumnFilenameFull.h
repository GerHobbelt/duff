// FullFilenameColumn.h: interface for the CFullFilenameColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FULLFILENAMECOLUMN_H__710C39F3_06FB_4728_AFD8_2D01873AE151__INCLUDED_)
#define AFX_FULLFILENAMECOLUMN_H__710C39F3_06FB_4728_AFD8_2D01873AE151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFullFilenameColumn : public CDuplicateListColumn  
{
public:
	CFullFilenameColumn();
	virtual ~CFullFilenameColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );
};

inline CString CFullFilenameColumn::GetColumnText(CFileInfo* pFileInfo)
{
 return pFileInfo->FullName;
}

inline int CFullFilenameColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{
	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	return _tcsicmp( pFileInfo1->FullName, pFileInfo2->FullName );
}

#endif // !defined(AFX_FULLFILENAMECOLUMN_H__710C39F3_06FB_4728_AFD8_2D01873AE151__INCLUDED_)
