// FilenameLayer.h: interface for the CFilenameLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENAMELAYER_H__F2B211C2_C840_4ADB_945D_CFF438232E0F__INCLUDED_)
#define AFX_FILENAMELAYER_H__F2B211C2_C840_4ADB_945D_CFF438232E0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "layers.h"
#include "Layer.h"
#include "LayerFilenameForm.h"

class CFilenameLayer : public CFileComparisonLayer  
{
public:
	virtual CString GetSettingString()  ;
 virtual bool UpdateData(bool SaveAndValidate);
	virtual bool FilesEqual( CFileInfo &,  CFileInfo &) const;
	virtual CDuffModule * GetNew() { return new CFilenameLayer; }

	CFilenameLayer();
	virtual ~CFilenameLayer();

private:
	CFilenameLayerForm m_FilenameLayerForm;
 bool m_CaseSensitive;
	UINT m_FilenameMatchMode;
	UINT m_WordCount;
};

#endif // !defined(AFX_FILENAMELAYER_H__F2B211C2_C840_4ADB_945D_CFF438232E0F__INCLUDED_)

