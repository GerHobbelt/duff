// FileAccessDateColumn.h: interface for the CFileAccessDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEACCESSDATECOLUMN_H__004F4225_505C_4937_87FB_64D1B4E4827B__INCLUDED_)
#define AFX_FILEACCESSDATECOLUMN_H__004F4225_505C_4937_87FB_64D1B4E4827B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileAccessDateColumn : public CDuplicateListColumn  
{
public:
	CFileAccessDateColumn();
	virtual ~CFileAccessDateColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileAccessDateColumn::GetColumnText(CFileInfo* pFileInfo)
{
	return pFileInfo->TimeLastAccessed.Format( _T("%Y %m %d %H:%M:%S") );
}

inline int CFileAccessDateColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->TimeLastAccessed == pFileInfo2->TimeLastAccessed )
 	return 0;
 else 
	 if ( pFileInfo1->TimeLastAccessed > pFileInfo2->TimeLastAccessed )
   return -1;
	 else 
		 return 1;

}


#endif // !defined(AFX_FILEACCESSDATECOLUMN_H__004F4225_505C_4937_87FB_64D1B4E4827B__INCLUDED_)
