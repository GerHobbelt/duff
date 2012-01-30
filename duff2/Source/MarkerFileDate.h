// FileDateMarker.h: interface for the CFileDateMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATEMARKER_H__E8BA11D0_AD06_412F_851E_8439AC0DBBA1__INCLUDED_)
#define AFX_FILEDATEMARKER_H__E8BA11D0_AD06_412F_851E_8439AC0DBBA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marker.h"
#include "MarkerFileDateForm.h"



class CFileDateMarker : public CFileMarker  
{
public:
	CFileDateMarker();
	virtual ~CFileDateMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileDateMarker; }

private:
	CFileDateMarkerForm m_FileDateMarkerForm;
	int m_Option;
};

#endif // !defined(AFX_FILEDATEMARKER_H__E8BA11D0_AD06_412F_851E_8439AC0DBBA1__INCLUDED_)
