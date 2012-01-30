// DuffPluginTypeProcessor.cpp: implementation of the CDuffPluginTypeProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffPluginTypeProcessor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffPluginTypeProcessor::CDuffPluginTypeProcessor()
{
	m_PluginTypeString = "Processor";
 m_EntryPointString = "GetProcessorPtr";
}

CDuffPluginTypeProcessor::~CDuffPluginTypeProcessor()
{

}

HINSTANCE CDuffPluginTypeProcessor::LoadPlugin(const CString & sFilename)
{
	HINSTANCE hInstance = LoadLibrary(sFilename);
 FuncPtr MyFunc;
	if (hInstance)
	{
		MyFunc = (FuncPtr) GetProcAddress(hInstance, m_EntryPointString);
  if (MyFunc)
			return hInstance;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

}