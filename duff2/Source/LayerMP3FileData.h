// MP3FileDataLayer.h: interface for the CMP3FileDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3FILEDATALAYER_H__EE254BCA_25C6_4160_99BB_C9DD760C3879__INCLUDED_)
#define AFX_MP3FILEDATALAYER_H__EE254BCA_25C6_4160_99BB_C9DD760C3879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"
#include "LayerMP3DataForm.h"

class CMP3FileDataLayer : public CFileComparisonLayer  
{
public:
	CMP3FileDataLayer();
	virtual ~CMP3FileDataLayer();
 virtual bool UpdateData(bool SaveAndValidate);
 virtual bool FilesEqual(CFileInfo &, CFileInfo &) const;
	virtual CDuffModule * GetNew() { return new CMP3FileDataLayer; }

	
private:
	long m_MaxFileSizeDifference;
	CFileMP3DataLayerForm m_FileMP3DataLayerForm;

};

#endif // !defined(AFX_MP3FILEDATALAYER_H__EE254BCA_25C6_4160_99BB_C9DD760C3879__INCLUDED_)
