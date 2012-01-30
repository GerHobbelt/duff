// FileSizeFilter.h: interface for the CFileSizeFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESIZEFILTER_H__613D00B4_98DA_437C_8F48_AE0B9F96590A__INCLUDED_)
#define AFX_FILESIZEFILTER_H__613D00B4_98DA_437C_8F48_AE0B9F96590A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"
#include "FilterFileSizeForm.h"

class CFileSizeFilter : public CFileFilter  
{
public:
	enum FilterType { FT_NOT_EQUAL = 0, FT_EQUAL = 1, FT_GREATER_THAN = 2, FT_LESS_THAN = 3, FT_BETWEEN = 4, FT_NOT_BETWEEN = 5 };
	CFileSizeFilter();
	virtual ~CFileSizeFilter();
 virtual bool UpdateData(bool SaveAndValidate);
	virtual int FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & );
 virtual CString GetSettingString() ;
 virtual CDuffModule * GetNew() { return new CFileSizeFilter; }

private:
	CFileSizeFilterForm m_FileSizeFilterForm;
 int m_FilterType;
 DWORD m_Value1;
 DWORD m_Value2;

};

#endif // !defined(AFX_FILESIZEFILTER_H__613D00B4_98DA_437C_8F48_AE0B9F96590A__INCLUDED_)
