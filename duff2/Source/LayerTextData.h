// FileTextDataLayer.h: interface for the CFileTextDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETEXTDATALAYER_H__256FE8F0_2B41_41FE_A217_474BE6857D94__INCLUDED_)
#define AFX_FILETEXTDATALAYER_H__256FE8F0_2B41_41FE_A217_474BE6857D94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"
#include "LayerTextDataForm.h"

class CFileTextDataLayer : public CFileComparisonLayer  
{
public:
	CFileTextDataLayer();
	virtual ~CFileTextDataLayer();
 virtual bool UpdateData(bool SaveAndValidate);
 virtual bool FilesEqual(CFileInfo &, CFileInfo &) const;
	virtual CDuffModule * GetNew() { return new CFileTextDataLayer; }

 int DetermineFileType(CFileInfo &);

 CFileTextDataLayerForm m_FileTextDataLayerForm;
};

#endif // !defined(AFX_FILETEXTDATALAYER_H__256FE8F0_2B41_41FE_A217_474BE6857D94__INCLUDED_)
