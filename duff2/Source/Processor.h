// FileProcess.h: interface for the CFileProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPROCESS_H__C93D5756_8CF1_4C2D_9252_D72989298D82__INCLUDED_)
#define AFX_FILEPROCESS_H__C93D5756_8CF1_4C2D_9252_D72989298D82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "FileInfo.h"
#include "DuffModule.h"

class CFileProcessor : public CDuffModule
{
public:
	CFileProcessor();
	virtual ~CFileProcessor();

	virtual void ProcessFiles ( CList<CFileInfo *, CFileInfo * > & ) = 0;
 //virtual bool UpdateData(bool SaveAndValidate) = 0;

	// public methods
	//void SetSelected(bool b) { m_Selected = b; }
	//bool IsSelected() const { return m_Selected; }
 //const UINT & GetFormID() const { return m_FormID; }
 //CDialog * GetForm() { return m_pForm; }
 //const CString & GetName() const { return m_Name; }
 //const CString & GetDescription() const{ return m_Description; }

//protected:
//	CString   m_Name;
//	CString   m_Description;
// CDialog * m_pForm;
// UINT      m_FormID;

//private:
//	bool      m_Selected;

};

#endif // !defined(AFX_FILEPROCESS_H__C93D5756_8CF1_4C2D_9252_D72989298D82__INCLUDED_)

