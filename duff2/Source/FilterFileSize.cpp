// FileSizeFilter.cpp: implementation of the CFileSizeFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "FilterFileSize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "DuplicateFileFind.h"
#include "util.h"

extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSizeFilter::CFileSizeFilter()
{
 m_pForm = &m_FileSizeFilterForm;
	m_uiFormID = IDD_FILE_SIZE_FILTER_FORM;
	m_sName = "File Size";
	m_sDescription = "Process only files with file size restrictions";

}

CFileSizeFilter::~CFileSizeFilter()
{

}



bool CFileSizeFilter::UpdateData(bool /*SaveAndValidate*/)
{
	CString Temp;

 m_FilterType = m_FileSizeFilterForm.m_FilterTypeControl.GetCurSel();
	m_FileSizeFilterForm.m_Value1Control.GetWindowText(Temp);
 if ( !isinteger(Temp) )
		return false;

	m_Value1 = _ttol(Temp);
 
	m_FileSizeFilterForm.m_Value2Control.GetWindowText(Temp);
 if ( !isinteger(Temp) )
		return false;

 m_Value2 = _ttol(Temp);

	return true;
}


 

int CFileSizeFilter::FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & FileList)
{
 int Count = 0;
 bool FilterIt = false;
 int Iteration = 0;
 POSITION xPos;

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
		switch(m_FilterType)
		{
		case FT_NOT_EQUAL: // not equal
   FilterIt = ( FileList.GetAt(xPos)->Size == m_Value1 );
			break;
		case FT_EQUAL: // equal
   FilterIt = ( FileList.GetAt(xPos)->Size != m_Value1 );
			break;
		case FT_GREATER_THAN: // greater
   FilterIt = ( FileList.GetAt(xPos)->Size <= m_Value1 );
			break;
		case FT_LESS_THAN: // less
   FilterIt = ( FileList.GetAt(xPos)->Size >= m_Value1 );
			break;
		case FT_BETWEEN: // between
   FilterIt = ( FileList.GetAt(xPos)->Size < m_Value1 || FileList.GetAt(xPos)->Size > m_Value2 );
			break;
		case FT_NOT_BETWEEN: // not between
   FilterIt = ( FileList.GetAt(xPos)->Size >= m_Value1 && FileList.GetAt(xPos)->Size <= m_Value2	);
			break;
		default:
			return 0;
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
		if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
		{
		 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = Iteration;
		 g_DupeFileFind.m_DuffStatus.Unlock();
		}
		//

	}

 return Count;
}


CString CFileSizeFilter::GetSettingString() 
{
 
	CString Temp;



	switch(m_FilterType)
	{
	case 0: // not equal
  Temp.Format( _T("do not have a file size of %d bytes") ,m_Value1);
		break;
	case 1: // equal
  Temp.Format( _T("have a file size of %d bytes") ,m_Value1);
		break;
	case 2: // greater
  Temp.Format( _T("have a file size greater than %d bytes") ,m_Value1);
		break;
	case 3: // less
  Temp.Format( _T("have a file size less than %d bytes") ,m_Value1);
		break;
	case 4: // between
  Temp.Format( _T("have a file size between %d and %d bytes") ,m_Value1, m_Value2);
		break;
	case 5: // not between
  Temp.Format( _T("do no have a file size between %d and %d bytes") ,m_Value1, m_Value2);
		break;
	}
	
return Temp;
}
