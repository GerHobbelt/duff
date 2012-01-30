// DuffPlugin.h: interface for the CDuffPlugin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFPLUGIN_H__6412949A_D55A_4046_A6A1_7768968FBE5C__INCLUDED_)
#define AFX_DUFFPLUGIN_H__6412949A_D55A_4046_A6A1_7768968FBE5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DuffModule.h"
#include "DuffStatus.h"




class CDuffPlugin  
{
public:
	enum PluginType { PLUGIN_INVALID, PLUGIN_COMPARISONLAYER, PLUGIN_FILTER, PLUGIN_MARKER, PLUGIN_PROCESSOR, PLUGIN_TOOL };
	CDuffPlugin();
	virtual ~CDuffPlugin();

	UINT GetType() const;
	void SetType(PluginType);
		
	HINSTANCE GetInstance() const;
 void SetInstance(HINSTANCE inst) { m_hInstance = inst; }


	CString GetFilename() const;
 void SetFilename(const CString &);
	void SetPrimaryModule(CDuffModule* pMod) { m_pDuffModule = pMod; }
	CDuffModule * GetPrimaryModule() const { return m_pDuffModule; }

	sDuffStatus * m_pDuffStatus;

private:
 CString        m_sFilename;
	HINSTANCE      m_hInstance;
	PluginType     m_ePluginType;
	CDuffModule  * m_pDuffModule;

};

typedef void (*FuncPtr)(CDuffPlugin *);
#define PLUGIN_INIT_FUNCTION_NAME "DuffPluginInitialize"

#endif // !defined(AFX_DUFFPLUGIN_H__6412949A_D55A_4046_A6A1_7768968FBE5C__INCLUDED_)
