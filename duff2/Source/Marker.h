// FileSelection.h: interface for the CFileMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESELECTION_H__2D08B6E7_0FDE_4896_B58D_FB47BB6D45C6__INCLUDED_)
#define AFX_FILESELECTION_H__2D08B6E7_0FDE_4896_B58D_FB47BB6D45C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "FileInfo.h"
#include "DuffOptions.h"
#include "DuffModule.h"

class CFileMarker : public CDuffModule
{
public:
	CFileMarker();
	virtual ~CFileMarker();
	virtual unsigned int MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  ) = 0;
// virtual bool UpdateData(bool SaveAndValidate) = 0;

	// public methods
//	void SetSelected(bool b) { m_Selected = b; }
//	bool IsSelected() const { return m_Selected; }
// const UINT & GetFormID() const { return m_FormID; }
// CDialog * GetForm() { return m_pForm; }
// const CString & GetName() const { return m_Name; }
// const CString & GetDescription() const{ return m_Description; }
 

	static void SetMarkAtLeastOne( bool b ) { m_MarkAtLeastOne = b; }
	static void SetMarkMode( int b ) { m_MarkMode = b; }

 static bool GetMarkAtLeastOne()  { return m_MarkAtLeastOne; }
	static int  GetMarkMode() { return m_MarkMode; }
		

//protected:
//	CString   m_Name;
//	CString   m_Description;
// CDialog * m_pForm;
// UINT      m_FormID;
 
private:
	static bool m_MarkAtLeastOne;
	static int m_MarkMode;

//private:
// bool      m_Selected;
};


#endif // !defined(AFX_FILESELECTION_H__2D08B6E7_0FDE_4896_B58D_FB47BB6D45C6__INCLUDED_)
