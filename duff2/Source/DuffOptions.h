// DuffOptions.h: interface for the CDuffOptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFOPTIONS_H__ECBC8BE3_266B_487D_806F_547652A5BC5D__INCLUDED_)
#define AFX_DUFFOPTIONS_H__ECBC8BE3_266B_487D_806F_547652A5BC5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MARK_MODE_SINGLE   0
#define MARK_MODE_MULTIPLE 1


class CDuffOptions  
{
public:
	CDuffOptions();
	virtual ~CDuffOptions();

	bool SaveOptions() const;
	bool LoadOptions();

private:

	struct DirectoryOptions
	{
		bool IncludeSubDirs;
		BYTE DirAttributes[6];
	};

	struct GeneralOptions
	{
		UINT  UpdateInterval;
		int   ThreadPriority;
		bool  AutoScrollDupeList;
		bool  NoAccessRetry;
		bool  UseToolTip;
		TCHAR ToolTipText[MAX_PATH];
		//bool ProcessErrorNotify;
	};


	struct SoundOptions
	{
		bool Enabled;
		TCHAR FoundDuplicate[MAX_PATH];
		TCHAR ProcessComplete[MAX_PATH];
	};

	struct MarkerOptions
	{
		bool MarkAtLeastOne;
		int  MarkMode;
		bool ClearMarks;
	};

	struct ProcessOptions
	{
		bool AutoPerformProcesses;
		bool DupeSetProcessWarning;
	};

	public:
		DirectoryOptions Directory;
	 GeneralOptions   General;
  SoundOptions     Sound;
  MarkerOptions    Marker;
		ProcessOptions   Process;

};



#endif // !defined(AFX_DUFFOPTIONS_H__ECBC8BE3_266B_487D_806F_547652A5BC5D__INCLUDED_)
