// FilenameColumn.h: interface for the CFilenameColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENAMECOLUMN_H__AF17F835_683C_443E_8ECB_5AB449699307__INCLUDED_)
#define AFX_FILENAMECOLUMN_H__AF17F835_683C_443E_8ECB_5AB449699307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFilenameColumn : public CDuplicateListColumn  
{
public:
	CFilenameColumn();
	virtual ~CFilenameColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFilenameColumn::GetColumnText(CFileInfo* pFileInfo)
{
 return pFileInfo->Name;
}

inline int CFilenameColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{
	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	return _tcsicmp( pFileInfo1->Name, pFileInfo2->Name );
}


#endif // !defined(AFX_FILENAMECOLUMN_H__AF17F835_683C_443E_8ECB_5AB449699307__INCLUDED_)
