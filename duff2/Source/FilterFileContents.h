// FileContentsFilter.h: interface for the CFileContentsFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECONTENTSFILTER_H__8E029D2E_F5EE_42E1_89B0_E74ADBD3D5B5__INCLUDED_)
#define AFX_FILECONTENTSFILTER_H__8E029D2E_F5EE_42E1_89B0_E74ADBD3D5B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"
#include "FilterFileContentsForm.h"

class CFileContentsFilter : public CFileFilter  
{
public:
	CFileContentsFilter();
	virtual ~CFileContentsFilter();
	virtual int FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & );
 virtual bool UpdateData(bool SaveAndValidate);
 virtual CString GetSettingString();
	virtual CDuffModule * GetNew() { return new CFileContentsFilter; }

private:
	CString                 m_ContentString;
	CFileContentsFilterForm m_FileContentsFilterForm;
	bool                    m_CaseSensitive;
	int                     m_ContentsOption;
};

#endif // !defined(AFX_FILECONTENTSFILTER_H__8E029D2E_F5EE_42E1_89B0_E74ADBD3D5B5__INCLUDED_)
