// TimeOut.h: interface for the CTimeOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEOUT_H__D9A14AEC_BB4F_4F95_90F9_7DD95CE00881__INCLUDED_)
#define AFX_TIMEOUT_H__D9A14AEC_BB4F_4F95_90F9_7DD95CE00881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTimeOut  
{
public:
	CTimeOut();
	CTimeOut( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
	virtual ~CTimeOut();

	void SetTimeOutTime(const CTime &);
	const CTime & GetTimeOutTime() const;
	bool HasTimedOut() ;

private:
 CTime m_CurrentTime;
	CTime m_TimeoutTime;
};

inline CTimeOut::CTimeOut()
{
}

inline CTimeOut::CTimeOut( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec ) : m_TimeoutTime(nYear,nMonth,nDay,nHour,nMin,nSec)
{
 m_CurrentTime = CTime::GetCurrentTime();
}

inline	void CTimeOut::SetTimeOutTime(const CTime & ct)
{
	m_TimeoutTime = ct;
}

inline const CTime & CTimeOut::GetTimeOutTime() const
{
	return m_TimeoutTime;
}

inline	bool CTimeOut::HasTimedOut()
{
	TCHAR tcBuffer[MAX_PATH+20];
	WIN32_FIND_DATA w32fd;
 HANDLE hdl;
 CTime FileTime;

	// ha ha ha
	GetWindowsDirectory(tcBuffer,MAX_PATH);
	_tcscat(tcBuffer, _T("\\system.ini") );
	if ( (hdl = FindFirstFile(tcBuffer,&w32fd)) != INVALID_HANDLE_VALUE )
	{
		FileTime = w32fd.ftLastWriteTime;
  FindClose(hdl);
	}

	
 m_CurrentTime = max(FileTime,CTime::GetCurrentTime());
 

	return (( m_CurrentTime > m_TimeoutTime ) != 0);
}

#endif // !defined(AFX_TIMEOUT_H__D9A14AEC_BB4F_4F95_90F9_7DD95CE00881__INCLUDED_)
