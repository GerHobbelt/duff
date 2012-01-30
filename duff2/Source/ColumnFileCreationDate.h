// FileCreationDateColumn.h: interface for the CFileCreationDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECREATIONDATECOLUMN_H__9CAE0A33_6A10_4109_AFDB_95D1B67EC2A8__INCLUDED_)
#define AFX_FILECREATIONDATECOLUMN_H__9CAE0A33_6A10_4109_AFDB_95D1B67EC2A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileCreationDateColumn : public CDuplicateListColumn  
{
public:
	CFileCreationDateColumn();
	virtual ~CFileCreationDateColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileCreationDateColumn::GetColumnText(CFileInfo* pFileInfo)
{
	return pFileInfo->TimeCreated.Format( _T("%Y %m %d %H:%M:%S") );
}

inline int CFileCreationDateColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->TimeCreated == pFileInfo2->TimeCreated )
 	return 0;
 else 
	 if ( pFileInfo1->TimeCreated > pFileInfo2->TimeCreated )
   return -1;
	 else 
		 return 1;

}
#endif // !defined(AFX_FILECREATIONDATECOLUMN_H__9CAE0A33_6A10_4109_AFDB_95D1B67EC2A8__INCLUDED_)
