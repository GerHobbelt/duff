// FileModifyDateColumn.h: interface for the CFileModifyDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMODIFYDATECOLUMN_H__40038D98_8C6E_4214_8CAE_167C0399F5E9__INCLUDED_)
#define AFX_FILEMODIFYDATECOLUMN_H__40038D98_8C6E_4214_8CAE_167C0399F5E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileModifyDateColumn : public CDuplicateListColumn  
{
public:
	CFileModifyDateColumn();
	virtual ~CFileModifyDateColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileModifyDateColumn::GetColumnText(CFileInfo* pFileInfo)
{
	return pFileInfo->TimeLastModified.Format( _T("%Y %m %d %H:%M:%S") );
}

inline int CFileModifyDateColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->TimeLastModified == pFileInfo2->TimeLastModified )
 	return 0;
 else 
	 if ( pFileInfo1->TimeLastModified > pFileInfo2->TimeLastModified )
   return -1;
	 else 
		 return 1;

}

#endif // !defined(AFX_FILEMODIFYDATECOLUMN_H__40038D98_8C6E_4214_8CAE_167C0399F5E9__INCLUDED_)
