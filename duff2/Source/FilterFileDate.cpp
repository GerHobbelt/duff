// FileDateFilter.cpp: implementation of the CFileDateFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "FilterFileDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFileDateFilter::CFileDateFilter()
{
 m_pForm = &m_FileDateFilterForm;
	m_uiFormID = IDD_FILE_DATE_FILTER_FORM;
	m_sName = "Date/Time";
	m_sDescription = "Filters out files created, last modified or last accessed on certain dates";

	_tcscpy( m_FileTimeSettings[DATE_CREATED].Name  , _T("created") );
	_tcscpy( m_FileTimeSettings[DATE_MODIFIED].Name , _T("last modified") );
	_tcscpy( m_FileTimeSettings[DATE_ACCESSED].Name , _T("last accessed") );

}

CFileDateFilter::~CFileDateFilter()
{

}

int CFileDateFilter::FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & FileList)
{
	int  Count = 0;
 BOOL FilterIt;
 //int i;
	POSITION xPos;
	COleDateTime FileTime;
	CFileInfo *pFileInfo;
 CString Temp;
 int DateType;
 int Iteration = 0;

	// update status and log
 g_DupeFileFind.m_DuffStatus.Lock();
 g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = m_sName;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Max = FileList.GetCount();
	g_DupeFileFind.m_DuffStatus.Unlock();
 //

	//for (i = 0; i < FileList.GetSize(); i++)
	xPos = FileList.GetHeadPosition();
	while (xPos)
	{
  // speed hack: skip file if its already unaccessible (don't waste that precious CPU time!)
		if ( FileList.GetAt(xPos)->Unaccessible ) break;

		FilterIt = false;
		DateType = DATE_CREATED;
		pFileInfo = FileList.GetAt(xPos);


		while ( !FilterIt && DateType <= DATE_ACCESSED )
		{
   
   switch(DateType)
			{
 			case DATE_CREATED:
	  		FileTime = FileList.GetAt(xPos)->TimeCreated;
				break;
    case DATE_MODIFIED:
			  FileTime = FileList.GetAt(xPos)->TimeLastModified;
				break;
    case DATE_ACCESSED:
     FileTime = FileList.GetAt(xPos)->TimeLastAccessed;
				break;
			}
			
		if ( m_FileTimeSettings[DateType].Option != OPTION_IGNORE )
			switch ( m_FileTimeSettings[DateType].FilterType )
			{
				case FILTER_ON:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						FilterIt = (!(m_FileTimeSettings[DateType].DateTime1.GetYear()  == FileTime.GetYear()  && 
																m_FileTimeSettings[DateType].DateTime1.GetMonth() == FileTime.GetMonth() &&
																m_FileTimeSettings[DateType].DateTime1.GetDay()   == FileTime.GetDay()      ) );
					}
					else
					{
						FilterIt = (m_FileTimeSettings[DateType].DateTime1 != FileTime);
					}
					break;
				case FILTER_NOT_ON:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						FilterIt = (m_FileTimeSettings[DateType].DateTime1.GetYear()  == FileTime.GetYear()  && 
														m_FileTimeSettings[DateType].DateTime1.GetMonth() == FileTime.GetMonth() &&
														m_FileTimeSettings[DateType].DateTime1.GetDay()   == FileTime.GetDay()      );
					}
					else
					{
						FilterIt = (m_FileTimeSettings[DateType].DateTime1 == FileTime);
					}
					break;
				case FILTER_BEFORE:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						COleDateTime FileTime2(FileTime.GetYear(), FileTime.GetMonth(), FileTime.GetDay(), 0, 0, 0 );
						FilterIt = FileTime2 > m_FileTimeSettings[DateType].DateTime1 ;
					}
					else
					{
						FilterIt = ( FileTime > m_FileTimeSettings[DateType].DateTime1 );
					}
					break;
				case FILTER_AFTER:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						COleDateTime FileTime2(FileTime.GetYear(), FileTime.GetMonth(), FileTime.GetDay(), 24, 59, 59 );
						FilterIt = FileTime2 < m_FileTimeSettings[DateType].DateTime1;
					}
					else
					{
						FilterIt = ( FileTime < m_FileTimeSettings[DateType].DateTime1 );
					}
					break;
				case FILTER_BETWEEN:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						COleDateTime Time1(m_FileTimeSettings[DateType].DateTime1.GetYear(), m_FileTimeSettings[DateType].DateTime1.GetMonth(), m_FileTimeSettings[DateType].DateTime1.GetDay(), 24, 59, 59);
						COleDateTime Time2(m_FileTimeSettings[DateType].DateTime2.GetYear(), m_FileTimeSettings[DateType].DateTime2.GetMonth(), m_FileTimeSettings[DateType].DateTime2.GetDay(),  0,  0,  0);
						FilterIt = !( FileTime > Time1 && FileTime < Time2 );
					}
					else
					{
						FilterIt = !( FileTime > m_FileTimeSettings[DateType].DateTime1 && FileTime < m_FileTimeSettings[DateType].DateTime1);
					}
					break;
				case FILTER_NOT_BETWEEN:
					if (m_FileTimeSettings[DateType].IgnoreTime)
					{
						COleDateTime Time1(m_FileTimeSettings[DateType].DateTime1.GetYear(), m_FileTimeSettings[DateType].DateTime1.GetMonth(), m_FileTimeSettings[DateType].DateTime1.GetDay(), 24, 59, 59);
						COleDateTime Time2(m_FileTimeSettings[DateType].DateTime2.GetYear(), m_FileTimeSettings[DateType].DateTime2.GetMonth(), m_FileTimeSettings[DateType].DateTime2.GetDay(),  0,  0,  0);
						FilterIt = ( FileTime > Time1 && FileTime < Time2 );
					}
					else
					{
						FilterIt = ( FileTime > m_FileTimeSettings[DateType].DateTime1 && FileTime < m_FileTimeSettings[DateType].DateTime1);
					}
					break;
				default:
					break;
			}
   DateType++;
		}




		if (FilterIt)
		{
			//FileList.ElementAt(i)->Unaccessible = true;
			POSITION Pos2 = xPos;
			FileList.GetNext(Pos2);
			delete FileList.GetAt(xPos);
			FileList.RemoveAt(xPos);
			//i--;
			xPos = Pos2;
			Count++;
		}
		else
		{
			FileList.GetNext(xPos);
		}


  Iteration ++;

		// update status and log
		if (g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
		{
		 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = Iteration;
		 g_DupeFileFind.m_DuffStatus.Unlock();
		}
		//

	//	FileList.GetNext(xPos);
	}




	return Count;
}

bool CFileDateFilter::UpdateData(bool /*SaveAndValidate*/)
{
	// read settings from dialog

	// creation time
 m_FileTimeSettings[DATE_CREATED].Option = m_FileDateFilterForm.m_OptionCreated.GetCurSel();
 m_FileTimeSettings[DATE_CREATED].FilterType = m_FileDateFilterForm.m_FilterTypeCreated.GetCurSel();
	m_FileTimeSettings[DATE_CREATED].IgnoreTime = m_FileDateFilterForm.m_IgnoreTimeCreated.GetCheck() == BST_CHECKED;
	m_FileDateFilterForm.m_DateTimeCreated1.GetTime(m_FileTimeSettings[DATE_CREATED].DateTime1);
	m_FileDateFilterForm.m_DateTimeCreated2.GetTime(m_FileTimeSettings[DATE_CREATED].DateTime2);
 //

	// last modified time
 m_FileTimeSettings[DATE_MODIFIED].Option = m_FileDateFilterForm.m_OptionModified.GetCurSel();
 m_FileTimeSettings[DATE_MODIFIED].FilterType = m_FileDateFilterForm.m_FilterTypeModified.GetCurSel();
	m_FileTimeSettings[DATE_MODIFIED].IgnoreTime = m_FileDateFilterForm.m_IgnoreTimeModified.GetCheck() == BST_CHECKED;
	m_FileDateFilterForm.m_DateTimeModified1.GetTime(m_FileTimeSettings[DATE_MODIFIED].DateTime1);
	m_FileDateFilterForm.m_DateTimeModified2.GetTime(m_FileTimeSettings[DATE_MODIFIED].DateTime2);
 //

	// last accessed time
 m_FileTimeSettings[DATE_ACCESSED].Option = m_FileDateFilterForm.m_OptionAccessed.GetCurSel();
 m_FileTimeSettings[DATE_ACCESSED].FilterType = m_FileDateFilterForm.m_FilterTypeAccessed.GetCurSel();
	m_FileTimeSettings[DATE_ACCESSED].IgnoreTime = m_FileDateFilterForm.m_IgnoreTimeAccessed.GetCheck() == BST_CHECKED;
	m_FileDateFilterForm.m_DateTimeAccessed1.GetTime(m_FileTimeSettings[DATE_ACCESSED].DateTime1);
	m_FileDateFilterForm.m_DateTimeAccessed2.GetTime(m_FileTimeSettings[DATE_ACCESSED].DateTime2);
 //

	return true;
}


CString CFileDateFilter::GetSettingString() 
{
 CString Desc, Temp;
 int DateType, i;
 bool OtherText;

	UpdateData(true);
 DateType = DATE_CREATED;

	while ( DateType <= DATE_ACCESSED )
	{
   
		if ( m_FileTimeSettings[DateType].Option != OPTION_IGNORE )
		{
   OtherText = false;
			i = 0;
			while ( !OtherText && i < DateType )
			{
				if ( m_FileTimeSettings[i].Option != OPTION_IGNORE ) OtherText = true;
				i++;
			}
			if ( OtherText ) Desc += " and ";


				switch ( m_FileTimeSettings[DateType].FilterType )
				{
					case FILTER_ON:
					case FILTER_NOT_ON:
					case FILTER_BEFORE:
					case FILTER_AFTER:
						{
						 Temp.Format(
								           m_FileTimeSettings[DateType].IgnoreTime  ? _T("%s %s %s %%B %%d, %%Y" : _T("%s %s %s %%B %%d, %%Y at %%H:%%M:%%S") ), 
								           (m_FileTimeSettings[DateType].FilterType == FILTER_ON) ? _T("were") : _T("were not"),
									          m_FileTimeSettings[DateType].Name,
									          FilterTypeNames[m_FileTimeSettings[DateType].FilterType] 
																		);

							Desc += m_FileTimeSettings[DateType].DateTime1.Format( Temp );
						}
						break;
					case FILTER_BETWEEN:
					case FILTER_NOT_BETWEEN:
						{
							CString TimeStr1, TimeStr2;
							TimeStr1 = m_FileTimeSettings[DateType].DateTime1.Format( m_FileTimeSettings[DateType].IgnoreTime  ? _T("%B %d, %Y") : _T("%H:%M:%S on %B %d, %Y")) ;
							TimeStr2 = m_FileTimeSettings[DateType].DateTime2.Format( m_FileTimeSettings[DateType].IgnoreTime  ? _T("%B %d, %Y") : _T("%H:%M:%S on %B %d, %Y")) ;
							Temp.Format(
								           _T("were %s sometime %s %s and %s (exclusively)") ,
								           m_FileTimeSettings[DateType].Name, 
																			FilterTypeNames[m_FileTimeSettings[DateType].FilterType],
																			TimeStr1,
																			TimeStr2
																		);
							Desc += Temp;
						}
						break;
				}

		}
	DateType++;
	}

	
	return Desc;
}
