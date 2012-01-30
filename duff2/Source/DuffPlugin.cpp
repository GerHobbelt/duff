// DuffPlugin.cpp: implementation of the CDuffPlugin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffPlugin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//extern CDuplicateFileFind g_DupeFileFind;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CDuffPlugin::CDuffPlugin()
{
	m_pDuffModule = NULL;
}

CDuffPlugin::~CDuffPlugin()
{

}

UINT CDuffPlugin::GetType() const
{
	return m_ePluginType;
}

void CDuffPlugin::SetType(PluginType type) 
{
 m_ePluginType = type;
}


HINSTANCE CDuffPlugin::GetInstance() const
{
	return m_hInstance;
}

CString CDuffPlugin::GetFilename() const
{
	return m_sFilename;
}


void CDuffPlugin::SetFilename(const CString & fn)
{
	m_sFilename = fn;
}
