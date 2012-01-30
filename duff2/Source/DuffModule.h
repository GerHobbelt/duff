// DuffModule.h: interface for the CDuffModule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFMODULE_H__67A30205_B29D_48F9_81B5_788CEF14D622__INCLUDED_)
#define AFX_DUFFMODULE_H__67A30205_B29D_48F9_81B5_788CEF14D622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "defines.h"

class CDuffModule  
{
public:
	CDuffModule();
	virtual ~CDuffModule();

 virtual CString GetSettingString() const { return NULL_STR; }
 virtual bool UpdateData(bool bSaveAndValidate) = 0;
 virtual CDuffModule * GetNew() = 0;

	void SetSelected(bool b) { m_bSelected = b; }
	bool IsSelected() const { return m_bSelected; }
 const UINT & GetFormID() const { return m_uiFormID; }
 CDialog * GetForm() const { return m_pForm; }
 const CString & GetName() const { return m_sName; }
 const CString & GetDescription() const{ return m_sDescription; }
	bool IsComplete() const {return m_bComplete; }

	
protected:
	CString     m_sName;
	CString     m_sDescription;
 CDialog *   m_pForm;
 UINT        m_uiFormID;
	bool        m_bComplete;

private:
	bool        m_bSelected;

};

#endif // !defined(AFX_DUFFMODULE_H__67A30205_B29D_48F9_81B5_788CEF14D622__INCLUDED_)
