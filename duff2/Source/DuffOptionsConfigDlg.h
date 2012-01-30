// DuffOptionsConfigDlg.h: interface for the CDuffOptionsConfigDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFOPTIONSCONFIGDLG_H__953C9E81_0EA7_41A8_904A_449F756353CF__INCLUDED_)
#define AFX_DUFFOPTIONSCONFIGDLG_H__953C9E81_0EA7_41A8_904A_449F756353CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DuffOptions.h"

class CDuffOptionsConfigDlg  
{
public:

	CDuffOptionsConfigDlg();
	virtual ~CDuffOptionsConfigDlg();

	const CString & GetName() { return m_Name; }

	virtual bool LoadOptions() = 0;
	virtual bool SaveOptions() = 0;

protected:
 CDuffOptions *m_pDuffOptions;
	CString m_Name;
};

#endif // !defined(AFX_DUFFOPTIONSCONFIGDLG_H__953C9E81_0EA7_41A8_904A_449F756353CF__INCLUDED_)
