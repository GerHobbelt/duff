// FileVersionMarker.h: interface for the CFileVersionMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVERSIONMARKER_H__83C6221B_7CC1_4C85_86B9_F2273EE2C34A__INCLUDED_)
#define AFX_FILEVERSIONMARKER_H__83C6221B_7CC1_4C85_86B9_F2273EE2C34A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marker.h"
#include "MarkerFileVersionForm.h"

class CFileVersionMarker : public CFileMarker  
{
public:
	CFileVersionMarker();
	virtual ~CFileVersionMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileVersionMarker; }

private:
	int m_Option;
	CFileVersionMarkerForm m_FileVersionMarkerForm;
};

#endif // !defined(AFX_FILEVERSIONMARKER_H__83C6221B_7CC1_4C85_86B9_F2273EE2C34A__INCLUDED_)
