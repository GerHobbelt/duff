// FileTypeDescColumn.h: interface for the CFileTypeDescColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETYPEDESCCOLUMN_H__1A5F38EF_E766_433D_8941_35C02BF5F5C0__INCLUDED_)
#define AFX_FILETYPEDESCCOLUMN_H__1A5F38EF_E766_433D_8941_35C02BF5F5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileTypeDescColumn : public CDuplicateListColumn  
{
public:
	CFileTypeDescColumn();
	virtual ~CFileTypeDescColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileTypeDescColumn::GetColumnText(CFileInfo* pFileInfo)
{
 if (!pFileInfo->ShellVerbsValid)
	{
		pFileInfo->InitShellVerbs();
	}

 return pFileInfo->TypeString;
}

inline int CFileTypeDescColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{
	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}
 
	if (!pFileInfo1->ShellVerbsValid)
	{
		pFileInfo1->InitShellVerbs();
	}
	if (!pFileInfo2->ShellVerbsValid)
	{
		pFileInfo2->InitShellVerbs();
	}


	return _tcsicmp( pFileInfo1->TypeString, pFileInfo2->TypeString );
}

#endif // !defined(AFX_FILETYPEDESCCOLUMN_H__1A5F38EF_E766_433D_8941_35C02BF5F5C0__INCLUDED_)
