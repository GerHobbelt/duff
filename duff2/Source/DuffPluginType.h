// DuffPluginType.h: interface for the CDuffPluginType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFPLUGINTYPE_H__22CA3319_6908_4B37_933D_5511A03A134E__INCLUDED_)
#define AFX_DUFFPLUGINTYPE_H__22CA3319_6908_4B37_933D_5511A03A134E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "Processor.h"

class CDuffPluginType  
{
public:
	CDuffPluginType();
	enum PluginType { PLUGIN_FCL, PLUGIN_FLT, PLUGIN_MRK, PLUGIN_PRO, PLUGIN_TOL };
	virtual ~CDuffPluginType();
 virtual HINSTANCE LoadPlugin(const CString &) = 0;
private:
	CString m_PluginTypeString;
 CString m_EntryPointString;
//	static CArray<CDuffPluginType*,CDuffPluginType*> m_AllTypes;
};

#endif // !defined(AFX_DUFFPLUGINTYPE_H__22CA3319_6908_4B37_933D_5511A03A134E__INCLUDED_)
