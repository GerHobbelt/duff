// FilenameFilter.h: interface for the CFilenameFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENAMEFILTER_H__E88E5863_D224_4D0D_B57F_29CBAB55A938__INCLUDED_)
#define AFX_FILENAMEFILTER_H__E88E5863_D224_4D0D_B57F_29CBAB55A938__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"

class CFilenameFilter : public CFileFilter  
{
public:
	CFilenameFilter();
	virtual ~CFilenameFilter();
	virtual int FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & );

};

#endif // !defined(AFX_FILENAMEFILTER_H__E88E5863_D224_4D0D_B57F_29CBAB55A938__INCLUDED_)
