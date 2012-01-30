// FileLocationMarker.h: interface for the CFileLocationMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELOCATIONMARKER_H__3946455B_98EE_48F6_85DD_45559EB5E6A1__INCLUDED_)
#define AFX_FILELOCATIONMARKER_H__3946455B_98EE_48F6_85DD_45559EB5E6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marker.h"
#include "MarkerFileLocationForm.h"

class CFileLocationMarker : public CFileMarker  
{
public:
	CFileLocationMarker();
	virtual ~CFileLocationMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileLocationMarker; }

private:
	CFileLocationMarkerForm m_FileLocationMarkerForm;
	CString m_Path;
	bool    m_SubDirs;
	int     m_Option;
};

#endif // !defined(AFX_FILELOCATIONMARKER_H__3946455B_98EE_48F6_85DD_45559EB5E6A1__INCLUDED_)
