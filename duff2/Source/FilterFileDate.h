// FileDateFilter.h: interface for the CFileDateFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATEFILTER_H__D052D738_5954_42FB_AB30_8395A6664DD3__INCLUDED_)
#define AFX_FILEDATEFILTER_H__D052D738_5954_42FB_AB30_8395A6664DD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"
#include "FilterFileDateForm.h"


#define OPTION_IS     0
#define OPTION_IGNORE 1

#define FILTER_ON          0
#define FILTER_NOT_ON      1
#define FILTER_BEFORE      2
#define FILTER_AFTER       3
#define FILTER_BETWEEN     4
#define FILTER_NOT_BETWEEN 5

const   TCHAR   FilterTypeNames[6][20] = { _T("on"), _T("not on"), _T("before"), _T("after"), _T("between"), _T("not between") };

#define DATE_CREATED  0
#define DATE_MODIFIED 1
#define DATE_ACCESSED 2

struct sFileDateFilterSetting
{
	int   Option;
	int   FilterType;
	COleDateTime DateTime1;
	COleDateTime DateTime2;
 bool  IgnoreTime;
 TCHAR Name[20];
};

class CFileDateFilter : public CFileFilter  
{
public:
	CFileDateFilter();
	virtual ~CFileDateFilter();
 virtual bool UpdateData(bool SaveAndValidate);
	virtual int FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & );
 virtual CString GetSettingString() ;
	virtual CDuffModule * GetNew() { return new CFileDateFilter; }

private:
	CFileDateFilterForm m_FileDateFilterForm;
	sFileDateFilterSetting m_FileTimeSettings[3];
};

#endif // !defined(AFX_FILEDATEFILTER_H__D052D738_5954_42FB_AB30_8395A6664DD3__INCLUDED_)
