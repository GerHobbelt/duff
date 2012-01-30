// FileLocationColumn.h: interface for the CFileLocationColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELOCATIONCOLUMN_H__3E5E4B94_D0A3_4388_81CE_103AAAC64F23__INCLUDED_)
#define AFX_FILELOCATIONCOLUMN_H__3E5E4B94_D0A3_4388_81CE_103AAAC64F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileLocationColumn : public CDuplicateListColumn  
{
public:
	CFileLocationColumn();
	virtual ~CFileLocationColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileLocationColumn::GetColumnText(CFileInfo* pFileInfo)
{
	CString sLocation;
	sLocation = pFileInfo->FullName;
 sLocation = sLocation.Left( sLocation.ReverseFind('\\')+1);
 return sLocation;
}

inline int CFileLocationColumn::CompareItems( CFileInfo *pFileInfo1, CFileInfo *pFileInfo2 )
{
	//int iCount;

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}
 
 // C:\directory\file.txt
/*
	if ( pFileInfo1->Name - pFileInfo1->FullName > pFileInfo2->Name - pFileInfo2->FullName )
	{
		iCount = ( (pFileInfo1->Name - pFileInfo1->FullName) / sizeof(TCHAR) ) - 1;
	}
	else
	{
		iCount = ( (pFileInfo2->Name - pFileInfo2->FullName) / sizeof(TCHAR) ) - 1;
	}
*/
	CString Dir1;
	CString Dir2;

	Dir1 = pFileInfo1->FullName;
 Dir1 = Dir1.Left( Dir1.ReverseFind('\\') );

	Dir2 = pFileInfo2->FullName;
 Dir2 = Dir2.Left( Dir2.ReverseFind('\\') );

	return Dir1.Compare(Dir2);

//	return _tcsnicmp( pFileInfo1->FullName , pFileInfo2->FullName  , iCount );
}

#endif // !defined(AFX_FILELOCATIONCOLUMN_H__3E5E4B94_D0A3_4388_81CE_103AAAC64F23__INCLUDED_)
