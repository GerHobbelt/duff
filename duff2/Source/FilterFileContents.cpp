// FileContentsFilter.cpp: implementation of the CFileContentsFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "duff.h"
#include "FilterFileContents.h"
#include "FileEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "DuplicateFileFind.h"

using namespace std;


extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileContentsFilter::CFileContentsFilter()
{
 m_pForm = &m_FileContentsFilterForm;
	m_uiFormID = IDD_FILE_CONTENTS_FILTER_FORM;
	m_sName = "Contents";
	m_sDescription = "Process only files that contain certain data";
 m_CaseSensitive = false;
	m_ContentsOption = 0;
}

CFileContentsFilter::~CFileContentsFilter()
{

}


int CFileContentsFilter::FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & FileList)
{
	const unsigned int BUFFSIZE = 4096;
	BYTE buffer[BUFFSIZE];
	int i;
	POSITION xPos;
	bool ok;
 bool bDataFound;
 ULONGLONG TotalBytesRead;
 ULONGLONG NumRead;
 UINT Count = 0;
 CFileEx ifile;
 CFileException file_ex;
 int ArrayIndex = 0;

	// update status and log
 if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{
  g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = "data filter";
  g_DupeFileFind.m_DuffStatus.SubProgress1.Min = 0;
  g_DupeFileFind.m_DuffStatus.SubProgress1.Max = FileList.GetCount(); // FileInfo1.GetLength() / ULongLong_IntRatio;
  g_DupeFileFind.m_DuffStatus.SubProgress1.Pos = 0;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
  g_DupeFileFind.m_DuffStatus.Unlock();
 }
	//

	xPos = FileList.GetHeadPosition();
	//for (int ArrayIndex = 0; ArrayIndex < FileList.GetSize(); ArrayIndex++)
	while (xPos)
	{
				// update status and log
		if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
		{
			g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = FileList.GetAt(xPos)->FullName;
			g_DupeFileFind.m_DuffStatus.SubProgress2.Max = FileList.GetAt(xPos)->Size;
	  g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
			g_DupeFileFind.m_DuffStatus.Unlock();
		}
		//

		ok = ifile.Open( FileList.GetAt(xPos)->FullName ,  CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary | CFile::osSequentialScan, &file_ex);
		if (ok)
		{
			//ifile.seekg(0);
			bDataFound = false;
			TotalBytesRead = 0;
			do
			{
				NumRead = ifile.Read(buffer, BUFFSIZE);
				TotalBytesRead +=NumRead;
				i=0;
				while(i + 1 < NumRead && !bDataFound)
				{
					if (m_CaseSensitive)
					 bDataFound =  memcmp( buffer, (BYTE*)(LPTSTR)(LPCTSTR)m_ContentString, m_ContentString.GetLength() * sizeof(TCHAR) ) == 0;
					else
					 bDataFound = _memicmp( buffer, (BYTE*)(LPTSTR)(LPCTSTR)m_ContentString, m_ContentString.GetLength() * sizeof(TCHAR) ) == 0;

					i++;
				}
				if (!bDataFound)
				{
					ifile.Seek(-1 * ( m_ContentString.GetLength() * (sizeof(TCHAR)+1) ), CFile::current);
				}

						// update status and log
				if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
				{
					g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = TotalBytesRead;
					g_DupeFileFind.m_DuffStatus.Unlock();
				}
				//
			}
			while (!bDataFound && NumRead /* && !ifile.eof() */ );

			if ( (!bDataFound && (m_ContentsOption == 0)) || (bDataFound && (m_ContentsOption == 1)))
			{
				//FileList.ElementAt(i)->Unaccessible = true;
				POSITION Pos2 = xPos;
				FileList.GetNext(Pos2);
				delete FileList.GetAt(xPos);
				FileList.RemoveAt(xPos);
				//i--;
	 			xPos = Pos2;
				Count++;
				ArrayIndex--;
			}
			else
			{
				FileList.GetNext(xPos);
			}

			ArrayIndex ++;
	//	 FileList.GetNext(xPos);
		}
		ifile.Close();
		// update status and log
		if ( ArrayIndex >=0 && g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
		{
			g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = FileList.GetAt(xPos)->FullName;
			g_DupeFileFind.m_DuffStatus.SubProgress1.Pos = ArrayIndex;
			g_DupeFileFind.m_DuffStatus.Unlock();
		}
		//
	}
	return Count;
}

bool CFileContentsFilter::UpdateData(bool /*SaveAndValidate*/)
{
 bool GoodData = true;
	//if ( ! m_FileContentsFilterForm.UpdateData(true) )
	//	return false;

	m_FileContentsFilterForm.m_ContentString.GetWindowText(m_ContentString);

	m_CaseSensitive = m_FileContentsFilterForm.m_CaseSensitive.GetCheck() == BST_CHECKED;

	m_ContentsOption = m_FileContentsFilterForm.GetCheckedRadioButton(IDC_CONTAINS_DATA, IDC_DOES_NOT_CONTAIN_DATA);

	switch( m_ContentsOption )
	{
	 case IDC_DOES_NOT_CONTAIN_DATA:
 	case IDC_CONTAINS_DATA:
		 GoodData = true;
		break;

 	default:
   GoodData = false;
		break;

	}


 return GoodData;
}

CString CFileContentsFilter::GetSettingString()
{
	CString Temp;
	Temp.Format( _T("must contain %s") ,m_ContentString);
	return Temp;
}
