// FileAttributesFilter.h: interface for the CFileAttributesFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEATTRIBUTESFILTER_H__86E11BA5_8CBF_4B64_A591_15F91682B2C8__INCLUDED_)
#define AFX_FILEATTRIBUTESFILTER_H__86E11BA5_8CBF_4B64_A591_15F91682B2C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"
#include "FilterFileAttributesForm.h"

class CFileAttributesFilter : public CFileFilter  
{
public:
	CFileAttributesFilter();
	virtual ~CFileAttributesFilter();
	virtual int FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & );
 virtual bool UpdateData(bool SaveAndValidate);
 virtual CString GetSettingString();
 virtual CDuffModule * GetNew() { return new CFileAttributesFilter; }

private:
	int m_IncludeReadOnly;
	int m_IncludeHidden;
	int m_IncludeSystem;
	int m_IncludeCompressed;
	int m_IncludeArchived;
	int m_IncludeEncrypted;
	int m_IncludeTemporary;
	CFileAttributesFilterForm m_FileAttributesFilterForm;
};

#endif // !defined(AFX_FILEATTRIBUTESFILTER_H__86E11BA5_8CBF_4B64_A591_15F91682B2C8__INCLUDED_)
