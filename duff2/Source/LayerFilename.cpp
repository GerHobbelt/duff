// FilenameLayer.cpp: implementation of the CFilenameLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "LayerFilename.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FMM_ALL  0
#define FMM_EXT  1
#define FMM_NONE 2

#include "DuplicateFileFind.h"
#include "util.h"

extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFilenameLayer::CFilenameLayer()
{
 m_pForm = &m_FilenameLayerForm;
	m_uiFormID = IDD_FILENAME_LAYER_FORM;
	m_sName = "Filename";
	m_sDescription = "In order for files to be considered duplicates, their filenames must be the same.\r\nYou can set whether the entire filename is included in comparison or just the extension. You can set case sensitivy.";
// m_ComparisonType = CFileComparisonLayer::CT_COMPARE |  CFileComparisonLayer::CT_PREFILTER;
 m_WordCount = 1;

}

CFilenameLayer::~CFilenameLayer()
{

}




// speed optimized and made unicode-compatible
inline bool CFilenameLayer::FilesEqual( CFileInfo & FileInfo1,  CFileInfo & FileInfo2) const
{
 
	switch (	 m_FilenameMatchMode )
 {
	case IDC_MATCH_FILENAMES:
		if ( m_CaseSensitive ) 
   return _tcscmp( FileInfo1.Name ,  FileInfo2.Name ) == 0;
		else
   return _tcsicmp( FileInfo1.Name ,  FileInfo2.Name ) == 0;

		break;
	case IDC_MATCH_EXTENSIONS:
		{
			TCHAR *pExtension1 = NULL , *pExtension2 = NULL;

			pExtension1 = _tcsrchr( FileInfo1.Name, _T('.') ) ;
			pExtension2 = _tcsrchr( FileInfo2.Name, _T('.') ) ;
  
			if ( pExtension1 == NULL || pExtension2 == NULL )
			{	
				return ( pExtension1 == pExtension2 );
			} 
			else
			{
				if ( m_CaseSensitive ) 
					return _tcscmp( pExtension1 , pExtension2 ) == 0;
				else
					return _tcsicmp( pExtension1 , pExtension2 ) == 0;
			}
		}
		break;
	case IDC_MATCH_NOT_FILENAME:
		if ( m_CaseSensitive ) 
   return _tcscmp( FileInfo1.Name ,  FileInfo2.Name ) != 0;
		else
   return _tcsicmp( FileInfo1.Name ,  FileInfo2.Name ) != 0;

		break;
	case IDC_MATCH_NOT_EXTENSIONS:
  {
			TCHAR *pExtension1 = NULL , *pExtension2 = NULL;

			pExtension1 = _tcsrchr( FileInfo1.Name, _T('.') ) ;
			pExtension2 = _tcsrchr( FileInfo2.Name, _T('.') ) ;
  
			if ( pExtension1 == NULL || pExtension2 == NULL )
			{	
				return ( pExtension1 == pExtension2 );
			} 
			else
			{
				if ( m_CaseSensitive ) 
					return _tcscmp( pExtension1 , pExtension2 ) != 0;
				else
					return _tcsicmp( pExtension1 , pExtension2 ) != 0;
			}
		}
		break;
	case IDC_MATCH_WORDS:
		{
		CArray <CString, CString&> Words1;
	 CArray <CString, CString&> Words2;
	 CArray <CString, CString> IgnoreWords;
  CString strMask;
		CString TempStr = FileInfo1.Name;
  int nPos = 0;	
		int nNextPos = 0;
		int x, y;
		
		//remove extension
		nPos = TempStr.ReverseFind(_T('.'));
		if ( nPos != -1)
			TempStr = TempStr.Left(nPos);
  //
  nPos = 0;	
		nNextPos = 0;

		// add file masks
		while (nPos < TempStr.GetLength()) 
		{
			nNextPos = TempStr.Find( _T(" ") ,nPos);
			if (nNextPos == -1) nNextPos = TempStr.GetLength();
			strMask = TempStr.Mid(nPos, nNextPos-nPos);
			strMask.TrimLeft();
			strMask.TrimRight();
			if ( !m_CaseSensitive ) strMask.MakeUpper();
			if (strMask != "") Words1.Add(strMask);
			nPos = nNextPos + 1;
		}
		//

		TempStr = FileInfo2.Name;

		//remove extension
		nPos = TempStr.ReverseFind(_T('.'));
		if ( nPos != -1)
			TempStr = TempStr.Left(nPos);
  //
  nPos = 0;	
		nNextPos = 0;

		// add file masks
		while (nPos < TempStr.GetLength()) 
		{
			nNextPos = TempStr.Find( _T(" ") ,nPos);
			if (nNextPos == -1) nNextPos = TempStr.GetLength();
			strMask = TempStr.Mid(nPos, nNextPos-nPos);
			strMask.TrimLeft();
			strMask.TrimRight();
			if ( !m_CaseSensitive ) strMask.MakeUpper();
			if (strMask != "") Words2.Add(strMask);
			nPos = nNextPos + 1;
		}
		//

		// remove duplicate words
  for (x = Words1.GetSize()-1; x > 0 ; x--)
		{
   for (y = x-1; y >= 0; y--)
	 	{
				if ( Words1.ElementAt(x) == Words1.ElementAt(y) ) 
				{
					Words1.RemoveAt(x);
				 break;
				}
			}
		}
		//

		// remove duplicate words
  for (x = Words2.GetSize()-1; x > 0 ; x--)
		{
   for (y = x-1; y >= 0; y--)
	 	{
				if ( Words2.ElementAt(x) == Words2.ElementAt(y) ) 
				{
					Words2.RemoveAt(x);
				 break;
				}
			}
		}
		//

  IgnoreWords.Add("-");
		IgnoreWords.Add("A");
		IgnoreWords.Add("THE");
		IgnoreWords.Add("I");
		IgnoreWords.Add("AT");
		IgnoreWords.Add("OF");
		IgnoreWords.Add("ON");

		bool deleted;

		// remove ignored words
		for (x = Words1.GetSize()-1; x>=0; x--)
		{
			deleted = false;
			y = 0;
			//for (y = 0; y < IgnoreWords.GetSize(); y++)
			while ( !deleted && y < IgnoreWords.GetSize() )
			{
				if ( Words1.ElementAt(x) == IgnoreWords.ElementAt(y) )
				{
					Words1.RemoveAt(x);
				 deleted = true;
				}
				y++;
			}
		}
  
		// remove ignored words
		for (x = Words2.GetSize()-1; x>=0; x--)
		{
			deleted = false;
			y = 0;
			//for (y = 0; y < IgnoreWords.GetSize(); y++)
			while ( !deleted && y < IgnoreWords.GetSize() )
			{
				if ( Words2.ElementAt(x) == IgnoreWords.ElementAt(y) )
				{
					Words2.RemoveAt(x);
				 deleted = true;
				}
				y++;
			}
		}

		UINT CommonCount = 0;
		// calculate the number of common words
		for (x = 0; x < Words1.GetSize(); x++)
		{
			for (y = 0; y < Words2.GetSize(); y++)
			{
				if ( Words1.ElementAt(x) == Words2.ElementAt(y) )
					CommonCount++;
			}
		}

		return ( CommonCount >= m_WordCount );
		}
		break;

	default:
		AfxMessageBox( _T("FMM_ERROR") );
		return true;
		break;
	}

	
/*
 // not optimized

 CString File1, File2;
	
	File1 = FileInfo1.Filename.Right( FileInfo1.Filename.GetLength() - FileInfo1.Filename.ReverseFind('\\') - 1 );
 File2 = FileInfo2.Filename.Right( FileInfo2.Filename.GetLength() - FileInfo2.Filename.ReverseFind('\\') - 1 );
	
 if ( !m_FilenameLayerForm.m_CaseSensitive )
	{
		File1.MakeUpper();
		File2.MakeUpper();
	}


	switch (	 m_FilenameMatchMode )
 {
	case IDC_MATCH_FILENAMES:
		return File1 == File2;
		break;
	case IDC_MATCH_EXTENSIONS:
		return File1.Right( File1.GetLength() - File1.ReverseFind('.') - 1 ) == File2.Right( File2.GetLength() - File2.ReverseFind('.') - 1);
		break;
 case IDC_MATCH_NOTHING:
		return true;
		break;
	case IDC_MATCH_NOT_FILENAME:
		return File1 != File2;
		break;
	case IDC_MATCH_NOT_EXTENSIONS:
		return File1.Right( File1.GetLength() - File1.ReverseFind('.') - 1 ) != File2.Right( File2.GetLength() - File2.ReverseFind('.') - 1);
		break;
	default:
		AfxMessageBox("FMM_ERROR");
		return true;
		break;
	}

*/

}

/*
int CFilenameLayer::CreateDuplicateList( CArray<CFileInfo,CFileInfo> & FileList, CArray< CArray<CFileInfo,CFileInfo> *,CArray<CFileInfo,CFileInfo> * > & DupeList)
{
//
}

int CFilenameLayer::RefineDuplicateList( CArray< CArray<CFileInfo,CFileInfo> *,CArray<CFileInfo,CFileInfo> * > & DupeList)
{
 int x,y,z;

	for (x = 0; x < DupeList.GetSize(); x++)
	{
		for (y = 0; y < DupeList.ElementAt(x)->GetSize(); y++)
		{
   


					for (z = y+1; z < DupeList.ElementAt(x)->GetSize(); z++)
		{
			if ( CouldBeDuplicates( DupeList.ElementAt(x)->ElementAt(y), DupeList.ElementAt(x)->ElementAt(z) ) )
			{
    // keep
			}
			else
			{
				// remove
			}
		}

		}

	}


	return 0;
}
*/

CString CFilenameLayer::GetSettingString()
{
	UpdateData(true);
 CString Desc;

	switch (	 m_FilenameMatchMode )
 {
	case IDC_MATCH_FILENAMES:
		Desc = "the filenames must be the same";
		if (m_CaseSensitive) 
			Desc += " (case sensitive)";
		else
			Desc += " (case insensitive)";
		break;
	case IDC_MATCH_EXTENSIONS:
		Desc = "the filename extensions must be the same";
		if (m_CaseSensitive) 
			Desc += " (case sensitive)";
		else
			Desc += " (case insensitive)";
		break;
	case IDC_MATCH_WORDS:
		Desc = "NULL";
		break;
	case IDC_MATCH_NOT_FILENAME:		
		Desc = "the filenames must NOT be the same";
		if (m_CaseSensitive) 
			Desc += " (case sensitive)";
		else
			Desc += " (case insensitive)";
		break;
	case IDC_MATCH_NOT_EXTENSIONS:
		Desc = "the filename extensions must NOT be the same";
		if (m_CaseSensitive) 
			Desc += " (case sensitive)";
		else
			Desc += " (case insensitive)";
		break;
	}

	return Desc;
}





bool CFilenameLayer::UpdateData(bool /*SaveAndValidate*/) 
{
 bool GoodData = true;
	CString sTemp;

	// get data from dialog
	m_CaseSensitive = m_FilenameLayerForm.m_CaseSensitive.GetCheck() == BST_CHECKED;
 m_FilenameMatchMode = m_FilenameLayerForm.GetCheckedRadioButton(IDC_MATCH_FILENAMES,IDC_MATCH_WORDS) ;	
	m_FilenameLayerForm.m_WordCountCtrl.GetWindowText(sTemp);
	m_WordCount = _ttoi(sTemp);
	//

	// validate data
	switch ( m_FilenameMatchMode )
	{
	 case IDC_MATCH_FILENAMES:
		case IDC_MATCH_NOT_FILENAME:
		case IDC_MATCH_EXTENSIONS:
		case IDC_MATCH_NOT_EXTENSIONS:
		case IDC_MATCH_WORDS:
		 GoodData = true;
		break;

		default:
			GoodData = false;
		break;
	}

	if ( m_WordCount < 1 || m_WordCount > MAX_PATH )
		GoodData = false;

 if ( ! isinteger(sTemp) )
		GoodData = false;
 //

	// return result
	return GoodData;
 //
}


