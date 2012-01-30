// DupeSetColumn.h: interface for the CDupeSetColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUPESETCOLUMN_H__B29A3B68_A3CD_4CF1_8D13_F5E64CC93D89__INCLUDED_)
#define AFX_DUPESETCOLUMN_H__B29A3B68_A3CD_4CF1_8D13_F5E64CC93D89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CDupeSetColumn : public CDuplicateListColumn  
{
public:
	CDupeSetColumn();
	virtual ~CDupeSetColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CDupeSetColumn::GetColumnText(CFileInfo* pFileInfo)
{
	CString sTemp;
	sTemp.Format( _T("%d"), pFileInfo->SetID );
	return sTemp;
}

inline int CDupeSetColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}
	

	if ( pFileInfo1->SetID == pFileInfo2->SetID )
 	return 0;
 else 
	 if ( pFileInfo1->SetID > pFileInfo2->SetID )
   return -1;
	 else 
		 return 1;

}

#endif // !defined(AFX_DUPESETCOLUMN_H__B29A3B68_A3CD_4CF1_8D13_F5E64CC93D89__INCLUDED_)
