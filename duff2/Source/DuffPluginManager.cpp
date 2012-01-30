// DuffPluginManager.cpp: implementation of the CDuffPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffPluginManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "DuffPlugin.h"
#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffPluginManager::CDuffPluginManager()
{

}

CDuffPluginManager::~CDuffPluginManager()
{
	while (!m_Plugins.IsEmpty())
	{
		CDuffPlugin pPlugin = m_Plugins.RemoveTail();

		delete pPlugin.GetPrimaryModule();
	}
}



UINT CDuffPluginManager::LoadPlugins()
{

 int Count = 0;
 bool Good;
 CString Msg;
 CString sFilename;
 HINSTANCE hInstance;
	CFileFind ff;
	CString SearchPath;
	int iPluginTypeIndex = 0;
 bool Loaded = false;
 FuncPtr MyFunc;

 CDuffPlugin DuffPlugin;
 CDuffPlugin *pDuffPlugin = NULL;

	SearchPath = _pgmptr;
	SearchPath = SearchPath.Left( SearchPath.ReverseFind( _T('\\') ) +1);
	SearchPath += _T("plugins\\*.dll");

	Good = ff.FindFile(SearchPath) != 0;
 while ( Good )
	{
		Good = ff.FindNextFile() != 0;
  sFilename = ff.GetFilePath();
		iPluginTypeIndex = 0;
		Loaded = false;
	 hInstance = LoadLibrary(sFilename);

  if (hInstance)
	 {
		 MyFunc = (FuncPtr) GetProcAddress(hInstance, PLUGIN_INIT_FUNCTION_NAME );
   if (MyFunc )
		 {
    DuffPlugin.SetInstance(hInstance);
				DuffPlugin.m_pDuffStatus = &g_DupeFileFind.m_DuffStatus;
				DuffPlugin.SetFilename( sFilename );
				MyFunc(&DuffPlugin);

				m_Plugins.AddTail(DuffPlugin);
    pDuffPlugin = & m_Plugins.GetTail();
			Loaded = true;

				//	pDuffModule = MyFunc();
			// if (pDuffModule)
			// {
			//		m_ProcessPage.AddProcessor(hInstance,pProcessor);
		 //  Loaded = true;
			//	}


		 }
	 }


		if ( Loaded )
		{

			CString sPluginType;
			switch(pDuffPlugin->GetType())
			{
			case CDuffPlugin::PLUGIN_INVALID:
			 	sPluginType = _T("Invalid");
				break;
			 case CDuffPlugin::PLUGIN_COMPARISONLAYER:
			 	sPluginType = _T("Comparison Layer");
				break;
			 case CDuffPlugin::PLUGIN_FILTER:
			 	sPluginType = _T("Filter");
				break;
			 case CDuffPlugin::PLUGIN_MARKER:
			 	sPluginType = _T("Marker");
				break;
			 case CDuffPlugin::PLUGIN_PROCESSOR:
			 	sPluginType = _T("Processor");
				break;
			 case CDuffPlugin::PLUGIN_TOOL:
			 	sPluginType = _T("Tool");
				break;
			}

		 Msg.Format( StringFromResource(IDS_LOADED_PLUGIN), pDuffPlugin->GetPrimaryModule()->GetName(), sPluginType ,ff.GetFileName());
			Count++;
		}
		else
		{
		 Msg.Format( StringFromResource(IDS_SKIPPING_NON_DLL), ff.GetFileName());
		}
		//Log(Msg);
		TRACE(Msg + "\n");
	}

	return Count;
		}
