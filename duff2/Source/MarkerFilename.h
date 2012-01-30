// FilenameSelection.h: interface for the CFilenameMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENAMESELECTION_H__F886116B_C965_4965_8815_9AF39006C971__INCLUDED_)
#define AFX_FILENAMESELECTION_H__F886116B_C965_4965_8815_9AF39006C971__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marker.h"
#include "MarkerFilenameForm.h"

class CFilenameMarker : public CFileMarker  
{
public:
	CFilenameMarker();
	virtual ~CFilenameMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFilenameMarker; }

private:
 int m_MarkMode;
 bool m_CaseSensitive;
	CString m_ContainText;

	CFilenameMarkerForm m_FilenameMarkerForm;
};

#endif // !defined(AFX_FILENAMESELECTION_H__F886116B_C965_4965_8815_9AF39006C971__INCLUDED_)
