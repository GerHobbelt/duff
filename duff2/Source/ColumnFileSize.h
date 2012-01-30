// FileSizeColumn.h: interface for the CFileSizeColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESIZECOLUMN_H__97882D92_8357_49A4_A5A9_D56395B89B99__INCLUDED_)
#define AFX_FILESIZECOLUMN_H__97882D92_8357_49A4_A5A9_D56395B89B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"
#include "util.h"


class CFileSizeColumn : public CDuplicateListColumn  
{
public:
	CFileSizeColumn();
	virtual ~CFileSizeColumn();
 virtual CString GetColumnText(CFileInfo* pFileInfo);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileSizeColumn::GetColumnText(CFileInfo* pFileInfo)
{
	TCHAR buffer[50];

	ulonglong2str(buffer,pFileInfo->Size);
 return buffer;
}

inline int CFileSizeColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{
	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->Size == pFileInfo2->Size )
 	return 0;
 else 
	 if ( pFileInfo1->Size > pFileInfo2->Size )
   return -1;
	 else 
		 return 1;
}

#endif // !defined(AFX_FILESIZECOLUMN_H__97882D92_8357_49A4_A5A9_D56395B89B99__INCLUDED_)
