// FileDataLayer.h: interface for the CFileDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATALAYER_H__B36891D8_E509_4A30_B693_6DC6ECFFA0E4__INCLUDED_)
#define AFX_FILEDATALAYER_H__B36891D8_E509_4A30_B693_6DC6ECFFA0E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"
//#include "FileDataLayerForm.h"



class CFileDataLayer : public CFileComparisonLayer  
{
public:
	CFileDataLayer();
	virtual ~CFileDataLayer();
	virtual CString GetSettingString()  ;
 virtual bool UpdateData(bool SaveAndValidate);
 virtual bool FilesEqual(CFileInfo &, CFileInfo &) const;
	virtual CDuffModule * GetNew() { return new CFileDataLayer; }

	
private:
	//int m_FileMode;
// CFileDataLayerForm m_FileDataLayerForm;
};

#endif // !defined(AFX_FILEDATALAYER_H__B36891D8_E509_4A30_B693_6DC6ECFFA0E4__INCLUDED_)
