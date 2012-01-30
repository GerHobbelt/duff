// FileComparisonLayer.h: interface for the CFileComparisonLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOMPARISONLAYER_H__AF67F071_E51C_44C7_A47F_CD51B1C99136__INCLUDED_)
#define AFX_FILECOMPARISONLAYER_H__AF67F071_E51C_44C7_A47F_CD51B1C99136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "FileInfo.h"
#include "DuffModule.h"

class CFileComparisonLayer : public CDuffModule  
{
public:

 CFileComparisonLayer();


	// methods children should implement
 //virtual CString GetSettingString() const { return NULL_STR; }
 //virtual bool UpdateData(bool bSaveAndValidate) = 0;
 virtual bool FilesEqual( CFileInfo & FileInfo1,  CFileInfo & FileInfo2) const = 0  ;
 virtual ~CFileComparisonLayer() {  }

	/*
	// public methods
	void SetSelected(bool b) { m_bSelected = b; }
	bool IsSelected() const { return m_bSelected; }
 const UINT & GetFormID() const { return m_uiFormID; }
 CDialog * GetForm() const { return m_pForm; }
 const CString & GetName() const { return m_sName; }
 const CString & GetDescription() const{ return m_sDescription; }

	bool IsComplete() const {return m_bComplete; }
*/

	// static methods
	static bool GetAccessRetry() { return m_bAccessRetry; }
 static void SetAccessRetry(bool b) { m_bAccessRetry = b; }
 //static const CArray< CFileComparisonLayer*, CFileComparisonLayer* > & GetObjectArray() { return m_ObjectArray; }

	// data to share with children
//protected:

	//CString     m_sName;
	//CString     m_sDescription;
 //CDialog *   m_pForm;
 //UINT        m_uiFormID;
 //bool        m_bComplete;

	// private data
//private:
//		bool        m_bSelected;
	// static data
private:
 static bool m_bAccessRetry;
	//static CArray< CFileComparisonLayer*, CFileComparisonLayer* > m_ObjectArray;

};



#endif // !defined(AFX_FILECOMPARISONLAYER_H__AF67F071_E51C_44C7_A47F_CD51B1C99136__INCLUDED_)

