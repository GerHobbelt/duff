// DuffPluginManager.h: interface for the CDuffPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFPLUGINMANAGER_H__85BB5C09_78AA_4EA9_A458_DAFC2144B6DB__INCLUDED_)
#define AFX_DUFFPLUGINMANAGER_H__85BB5C09_78AA_4EA9_A458_DAFC2144B6DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <afxtempl.h>
#include "DuffPlugin.h"

class CDuffPluginManager  
{
public:
	CDuffPluginManager();
	virtual ~CDuffPluginManager();
 UINT LoadPlugins();
// const CList<CDuffPlugin, CDuffPlugin &> * GetPluginList() const { return &m_Plugins; }

//private:
	CList<CDuffPlugin, CDuffPlugin &> m_Plugins;
};

#endif // !defined(AFX_DUFFPLUGINMANAGER_H__85BB5C09_78AA_4EA9_A458_DAFC2144B6DB__INCLUDED_)
