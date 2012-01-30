// DuffObject.h: interface for the CDuffObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFOBJECT_H__28748986_DDD3_484B_8BDD_A0D4A2AF1D72__INCLUDED_)
#define AFX_DUFFOBJECT_H__28748986_DDD3_484B_8BDD_A0D4A2AF1D72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDuffObject  
{
public:
	CDuffObject();
	virtual ~CDuffObject();

	virtual void LoadSettings() = 0;
	virtual void SaveSettings() = 0;

 CString m_DuffObjectName;
};

#endif // !defined(AFX_DUFFOBJECT_H__28748986_DDD3_484B_8BDD_A0D4A2AF1D72__INCLUDED_)

