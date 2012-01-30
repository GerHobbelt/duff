// DuffOptions.cpp: implementation of the CDuffOptions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>

#include "duff.h"
#include "DuffOptions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffOptions::CDuffOptions()
{
	General.AutoScrollDupeList = false;
	General.NoAccessRetry = true;
//	General.ProcessErrorNotify = true;
	General.ThreadPriority = 3;
	General.UpdateInterval = 100;

	General.UseToolTip = false;
	General.ToolTipText[0] = 0;

	for (int i = 0; i < 6; i++)
		Directory.DirAttributes[i] = BST_INDETERMINATE;
 
	Directory.IncludeSubDirs = true;

	Sound.Enabled = false;
	Sound.FoundDuplicate[0] = 0;
	Sound.ProcessComplete [0] = 0;

	Marker.MarkAtLeastOne = false;
	Marker.MarkMode = MARK_MODE_SINGLE;
 Marker.ClearMarks = true;
 
	Process.AutoPerformProcesses = false;
	Process.DupeSetProcessWarning = true;

}

CDuffOptions::~CDuffOptions()
{

}


bool CDuffOptions::SaveOptions() const
{
 ofstream inifile;
	inifile.open(AfxGetApp()->m_pszProfileName,ios::trunc  | ios::binary);
	if (inifile.is_open())
	{
		inifile.write ( (char*) this, sizeof((*this)) );
		inifile.close();
		return true; //( inifile.pcount() == sizeof((*this)) );
	}
	else
	{
		return false;
	}

/*


	CString TempStr;

 const char * pFilename = AfxGetApp()->m_pszProfileName;

	// general
	WritePrivateProfileString("General","AutoScrollDupeList", General.AutoScrollDupeList ? "1" : "0" ,pFilename);
	WritePrivateProfileString("General","NoAccessRetry", General.NoAccessRetry? "1" : "0" ,pFilename);
	WritePrivateProfileString("General","ProcessErrorNotify", General.ProcessErrorNotify? "1" : "0" ,pFilename);
	TempStr.Format("%d",General.ThreadPriority);
	WritePrivateProfileString("General","ThreadPriority", TempStr ,pFilename);
	TempStr.Format("%d",General.UpdateInterval);
	WritePrivateProfileString("General","UpdateInterval", TempStr ,pFilename);
 //


	// sounds
	WritePrivateProfileString("Sound","Enabled",         Sound.Enabled          ? "1" : "0" ,pFilename);
	WritePrivateProfileString("Sound","FoundDuplicate",  Sound.FoundDuplicate , pFilename);
	WritePrivateProfileString("Sound","ProcessComplete", Sound.ProcessComplete, pFilename);
	//

		*/
}

bool CDuffOptions::LoadOptions()
{
 ifstream inifile;
	inifile.open(AfxGetApp()->m_pszProfileName, ios::binary | ios::in);
	if (inifile.is_open())
	{
		inifile.read ( (char*) this, sizeof((*this)) );
		inifile.close();
		//TODO: validate input data
		return true;
	}
	else
	{
		// default options
		CDuffOptions();
		return false;
	}

/*	
	CString TempStr;
 const char * pFilename = AfxGetApp()->m_pszProfileName;
 char buffer[256];

	// general
	General.AutoScrollDupeList = GetPrivateProfileInt("General","AutoScrollDupeList", 0,pFilename) != 0;
 General.NoAccessRetry      = GetPrivateProfileInt("General","NoAccessRetry",      1,pFilename) != 0;
 General.ProcessErrorNotify = GetPrivateProfileInt("General","ProcessErrorNotify", 1,pFilename) != 0;
 General.ThreadPriority     = GetPrivateProfileInt("General","ThreadPriority",     3,pFilename);
 General.UpdateInterval     = GetPrivateProfileInt("General","UpdateInterval",   500,pFilename);
 //

	// sounds
	Sound.Enabled        = GetPrivateProfileInt("Sound","Enabled", 0,pFilename) != 0;
 GetPrivateProfileString("Sound","FoundDuplicate", "",buffer,sizeof(buffer),pFilename) != 0;
	Sound.FoundDuplicate = buffer;
 GetPrivateProfileString("Sound","ProcessComplete", "",buffer,sizeof(buffer),pFilename) != 0;
	Sound.ProcessComplete = buffer;
	//
*/
}
