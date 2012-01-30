// FilenameSelection.cpp: implementation of the CFilenameMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "MarkerFilename.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilenameMarker::CFilenameMarker()
{
	m_sName = "Filename";
	m_sDescription = "Mark files based on the filenames, including things like filename length, etc.";
	m_pForm = (CDialog*)&m_FilenameMarkerForm;
	m_uiFormID = IDD_FILENAME_SELECTION_FORM;

}

CFilenameMarker::~CFilenameMarker()
{

}

/*
int Select( CArray<CFileInfo,CFileInfo> * List )
{
 switch(m_MarkMode)
	{
	case IDC_LONGEST:
	case IDC_SHORTEST:
	case IDC_CONTAIN:
	case IDC_DONTCONTAIN:
	case IDC_LOWERCASE:   SelectLowercase(
	case IDC_UPPERCASE:   SelectUppercase(List); break;
 default:              ASSERT(false);         break;
}
*/

#define JUST_FILENAME(PATH) PATH.Right( PATH.GetLength() - PATH.ReverseFind('\\') -1 )

unsigned int CFilenameMarker::MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  DupeList)
{
 int count = 0;
 //int x,y;
	POSITION xPos, yPos, yPosOld;
	POSITION SpecialIndex;
	POSITION yHead;
	DWORD NewLen;
 bool found;
 bool UniqueLength;
	switch( m_MarkMode )
	{
	case IDC_LONGEST:
	case IDC_SHORTEST:

		// algorithm needs work!
	//for (x = 0; x < DupeList.GetSize(); x++)
	xPos = DupeList.GetHeadPosition();
	while (xPos)
	{
  found = false;
  NewLen = _tcslen ( DupeList.GetAt(xPos)->GetHead()->Name ); //DupeList.ElementAt(x)->ElementAt(0).Filename.Right( DupeList.ElementAt(x)->ElementAt(0).Filename.GetLength() - DupeList.ElementAt(x)->ElementAt(0).Filename.ReverseFind('\\') -1 ).GetLength();


  //for (y = 0; y < DupeList.ElementAt(x)->GetSize(); y++)
		yPosOld = 0;
		yHead = yPos = DupeList.GetAt(xPos)->GetHeadPosition();
  SpecialIndex  = yPos;
		UniqueLength = true;
		while (yPos)
		{
 //  CString ModifiedFilename ;
	//		ModifiedFilename = DupeList.ElementAt(x)->ElementAt(y).Filename.Right( DupeList.ElementAt(x)->ElementAt(y).Filename.GetLength() - DupeList.ElementAt(x)->ElementAt(y).Filename.ReverseFind('\\') -1 );
   UINT CurrentLength = _tcslen(DupeList.GetAt(xPos)->GetAt(yPos)->Name);
   if (
				(m_MarkMode == IDC_LONGEST ) && CurrentLength > NewLen ||
				(m_MarkMode == IDC_SHORTEST) && CurrentLength < NewLen 
				)
			{
			 UniqueLength = true;
				NewLen = CurrentLength; //ModifiedFilename.GetLength();
				SpecialIndex  = yPos;
			//	found = true;
			}
			else
				if ( yPos != yHead && CurrentLength == NewLen )
				{
 			 UniqueLength = false;
				}
					//			if ( y && JUST_FILENAME(DupeList.ElementAt(x)->ElementAt(y-1).Filename).GetLength() != JUST_FILENAME(DupeList.ElementAt(x)->ElementAt(y).Filename).GetLength() ) found = true;
	if ( yPosOld && _tcslen( DupeList.GetAt(xPos)->GetAt(yPosOld)->Name ) != _tcslen(DupeList.GetAt(xPos)->GetAt(yPos)->Name) ) found = true;
   
	  yPosOld = yPos;
	  DupeList.GetAt(xPos)->GetNext(yPos);
		}
		
		if (found && UniqueLength || CFileMarker::GetMarkAtLeastOne() )
		{
   DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Selected = true;
		}
 
		DupeList.GetNext(xPos); 
	}
	break;
	case IDC_CONTAIN:
	case IDC_DONTCONTAIN:
 
		{
			CString FindText = m_ContainText;

			//for (x = 0; x < DupeList.GetSize(); x++)
			xPos = DupeList.GetHeadPosition();
			while (xPos)
			{
				SpecialIndex  = 0;
				found = false;

				//y = 0;
				//while (!found && y < DupeList.ElementAt(x)->GetSize() )
				yPos = DupeList.GetAt(xPos)->GetHeadPosition();
				while ( yPos && !found )
				{
					CString ModifiedFilename;

					ModifiedFilename = DupeList.GetAt(xPos)->GetAt(yPos)->Name; //.Right( DupeList.ElementAt(x)->ElementAt(y).Filename.GetLength() - DupeList.ElementAt(x)->ElementAt(y).Filename.ReverseFind('\\') -1 );
  
					if ( !m_CaseSensitive )
					{
						ModifiedFilename.MakeLower();
						FindText.MakeLower();
					}

					if (
						(m_MarkMode == IDC_CONTAIN    ) && (ModifiedFilename.Find(FindText) != -1) ||
						(m_MarkMode == IDC_DONTCONTAIN) && (ModifiedFilename.Find(FindText) == -1) 
						)
					{
						SpecialIndex  = yPos;
						found = true;
					}
					//y++;
					DupeList.GetAt(xPos)->GetNext(yPos);
				}

				if (found || CFileMarker::GetMarkAtLeastOne() )
				{
					DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Selected = true;
				}

    DupeList.GetNext(xPos);
			}

		}
	break;
	case IDC_LOWERCASE:
	case IDC_UPPERCASE:
	
		//for (x = 0; x < DupeList.GetSize(); x++)
	xPos = DupeList.GetHeadPosition();

	while (xPos)
	{
  found = false;

		//y = 0;
  //while (!found && y < DupeList.ElementAt(x)->GetSize() )
		yPos = DupeList.GetAt(xPos)->GetHeadPosition();
  SpecialIndex = yPos;
		while (yPos && !found)
		{
   CString ModifiedFilename ;
			ModifiedFilename = DupeList.GetAt(xPos)->GetAt(yPos)->Name; //JUST_FILENAME(DupeList.ElementAt(x)->ElementAt(y).Filename);
   if (m_MarkMode == IDC_LOWERCASE)
				ModifiedFilename.MakeLower();
			else
	 		ModifiedFilename.MakeUpper();
	
   if (	ModifiedFilename	== DupeList.GetAt(xPos)->GetAt(yPos)->Name )
			{
				SpecialIndex  = yPos;
				found = true;
			}
					//y++;
					DupeList.GetAt(xPos)->GetNext(yPos);
		}

		if (found || CFileMarker::GetMarkAtLeastOne() )
		{
   DupeList.GetAt(xPos)->GetAt(SpecialIndex )->Selected = true;
		}

  DupeList.GetNext(xPos);
	}

	break;
	default:
		ASSERT(false);
 	break;
	}


	
	return count;
}

bool CFilenameMarker::UpdateData(bool /*SaveAndValidate*/)
{
	
	m_MarkMode =   m_FilenameMarkerForm.GetCheckedRadioButton(IDC_LONGEST,IDC_UPPERCASE);
 m_FilenameMarkerForm.GetDlgItem(IDC_CONTAINTEXT)->GetWindowText(m_ContainText);
	m_CaseSensitive = m_FilenameMarkerForm.m_CaseSensitive.GetCheck() == BST_CHECKED;
 
	if ( (m_MarkMode != IDC_LONGEST && m_MarkMode != IDC_SHORTEST && m_MarkMode != IDC_CONTAIN && m_MarkMode != IDC_DONTCONTAIN && m_MarkMode != IDC_LOWERCASE && m_MarkMode != IDC_UPPERCASE) ||
						(m_ContainText.GetLength() == 0) 
					)
	 return false;
	else
	 return true;
}


