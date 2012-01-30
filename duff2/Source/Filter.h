// FileFilter.h: interface for the CFileFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEFILTER_H__D938CA12_CF26_4675_8D2F_6C758833775A__INCLUDED_)
#define AFX_FILEFILTER_H__D938CA12_CF26_4675_8D2F_6C758833775A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "FileInfo.h"
#include "DuffModule.h"

class CFileFilter : public CDuffModule
{
public:
	CFileFilter();
	virtual ~CFileFilter();

 //virtual CString GetSettingString() { return "No Settings"; }
 //virtual bool UpdateData(bool SaveAndValidate) = 0;
	virtual int FilterDuplicateList( CList<CFileInfo *,CFileInfo *> & ) = 0;

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

// bool      m_Selected;

};

#endif // !defined(AFX_FILEFILTER_H__D938CA12_CF26_4675_8D2F_6C758833775A__INCLUDED_)
