// DuplicateFileFindConfigurer.h: interface for the CDuplicateFileFindConfigurer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUPLICATEFILEFINDCONFIGURER_H__5DB40F7B_320C_4A72_B7DB_365F70811A9F__INCLUDED_)
#define AFX_DUPLICATEFILEFINDCONFIGURER_H__5DB40F7B_320C_4A72_B7DB_365F70811A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DuplicateFileFind.h"

class CDuplicateFileFindConfigurer  
{
public:
	CDuplicateFileFindConfigurer();
	virtual ~CDuplicateFileFindConfigurer();
 virtual int InitDupeFileFind(CDuplicateFileFind & ) = 0;

 const CArray<CDuplicateFileFindConfigurer *,CDuplicateFileFindConfigurer *> * GetList() { return &m_List; }

private:
	static CArray<CDuplicateFileFindConfigurer *,CDuplicateFileFindConfigurer *> m_List;
};

#endif // !defined(AFX_DUPLICATEFILEFINDCONFIGURER_H__5DB40F7B_320C_4A72_B7DB_365F70811A9F__INCLUDED_)
