#ifndef DUFFSTATUS_H_2495EBTYHEBTY356356747834NRTU47n467n4RTYJRTY
#define DUFFSTATUS_H_2495EBTYHEBTY356356747834NRTU47n467n4RTYJRTY


#include <afxtempl.h>
#include <afxmt.h>
#include "FileInfo.h"

#define DUFFSTATUS_STOPPED 0
#define DUFFSTATUS_PAUSED  1
#define DUFFSTATUS_RUNNING 2

struct sProgressBarInfo
{
 sProgressBarInfo();
	LONGLONG Min;
	LONGLONG Max;
	LONGLONG Pos;
};

inline sProgressBarInfo::sProgressBarInfo()
{
	Min = 0;
	Max = 0;
	Pos = 0;
}

struct sDuffStatus
{
	sDuffStatus();
//	void WaitUntilUnlocked() const { while (Locked) Sleep(1); }

public:
	bool Lock();
	bool Unlock();
 bool IsLocked();
 bool LockIfUnlocked();
	CEvent Event; 

	int              Status;
 //volatile mutable bool             Locked;
	CString          CurrentTaskStr;
	CString          CurrentTaskInfo;
	sProgressBarInfo MainProgress;
	sProgressBarInfo SubProgress1;
	sProgressBarInfo SubProgress2;
	CArray<CString,CString>        LogQueue;
	CArray<CFileInfo*, CFileInfo*> DupeQueue;


private:
	//volatile bool Locked;
 CSemaphore  MagLock;

};

inline sDuffStatus::sDuffStatus()
{
	//Locked = false;
	Status = DUFFSTATUS_STOPPED;
}

inline bool sDuffStatus::Lock()
{
	CSingleLock SLock(&MagLock);
 return SLock.Lock(INFINITE) != 0;
}

inline bool sDuffStatus::Unlock() 
{
	CSingleLock SLock(&MagLock);
 return SLock.Unlock(1) != 0;
}

inline bool sDuffStatus::IsLocked()
{
	CSingleLock SLock(&MagLock);
 return SLock.IsLocked() != 0;
}

inline bool sDuffStatus::LockIfUnlocked() 
{ 
	CSingleLock SLock(&MagLock);
 return SLock.Lock(0) != 0;
}



#endif
