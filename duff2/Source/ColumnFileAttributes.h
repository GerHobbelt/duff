// FileAttributesColumn.h: interface for the CFileAttributesColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEATTRIBUTESCOLUMN_H__769180D9_527D_45F6_817C_7CEC1676294D__INCLUDED_)
#define AFX_FILEATTRIBUTESCOLUMN_H__769180D9_527D_45F6_817C_7CEC1676294D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Column.h"

class CFileAttributesColumn : public CDuplicateListColumn  
{
public:
	CFileAttributesColumn();
	virtual ~CFileAttributesColumn();
 virtual CString GetColumnText(CFileInfo*);
 virtual int CompareItems( CFileInfo*, CFileInfo* );

};

inline CString CFileAttributesColumn::GetColumnText(CFileInfo* pFileInfo)
{
 TCHAR buffer[50];

	struct AttribStruct
	{
		TCHAR Char;
		DWORD Flag;
	};
	UINT NumAttribs = 7;
 AttribStruct Attribs[7] = { 
		{_T('R'), FILE_ATTRIBUTE_READONLY},
		{_T('H'), FILE_ATTRIBUTE_HIDDEN},
		{_T('S'), FILE_ATTRIBUTE_SYSTEM},
		{_T('A'), FILE_ATTRIBUTE_ARCHIVE},
		{_T('C'), FILE_ATTRIBUTE_COMPRESSED},
		{_T('E'), FILE_ATTRIBUTE_ENCRYPTED},
		{_T('T'), FILE_ATTRIBUTE_TEMPORARY}
	};
	//RHSACET
 buffer[7] = 0;
 for(UINT i = 0; i < NumAttribs; i++)
	{
		if ( pFileInfo->Attributes & Attribs[i].Flag )
			buffer[i] = Attribs[i].Char;
		else
			buffer[i] = _T('_');

	}
 return buffer;
}

inline int CFileAttributesColumn::CompareItems( CFileInfo *pFileInfo1 , CFileInfo *pFileInfo2 )
{

	if ( !m_bSortAcending )
	{
		CFileInfo *pFileInfoTemp = pFileInfo1;
		pFileInfo1 = pFileInfo2;
		pFileInfo2 = pFileInfoTemp;
	}

	if ( pFileInfo1->Attributes == pFileInfo2->Attributes )
 	return 0;
 else 
	 if ( pFileInfo1->Attributes > pFileInfo2->Attributes )
   return -1;
	 else 
		 return 1;

}

#endif // !defined(AFX_FILEATTRIBUTESCOLUMN_H__769180D9_527D_45F6_817C_7CEC1676294D__INCLUDED_)
