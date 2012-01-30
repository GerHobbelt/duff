// FileSizeMarker.h: interface for the CFileSizeMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESIZEMARKER_H__2C83F2DA_E641_463A_8C84_2D1D388E06BE__INCLUDED_)
#define AFX_FILESIZEMARKER_H__2C83F2DA_E641_463A_8C84_2D1D388E06BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marker.h"
#include "MarkerFileSizeForm.h"

class CFileSizeMarker : public CFileMarker  
{
public:
	CFileSizeMarker();
	virtual ~CFileSizeMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileSizeMarker; }

private:
	int m_Option;
	CFileSizeMarkerForm m_FileSizeMarkerForm;
};

#endif // !defined(AFX_FILESIZEMARKER_H__2C83F2DA_E641_463A_8C84_2D1D388E06BE__INCLUDED_)
