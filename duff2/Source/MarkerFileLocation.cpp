// FileLocationMarker.cpp: implementation of the CFileLocationMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileLocation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFileLocationMarker::CFileLocationMarker()
{
 
	m_sName = "File location";
	m_sDescription = "Mark files located in (or not in) a specified location";
	m_pForm = (CDialog*)&m_FileLocationMarkerForm;
	m_uiFormID = IDD_FILE_LOCATION_MARKER_FORM;
}

CFileLocationMarker::~CFileLocationMarker()
{

}

unsigned int CFileLocationMarker::MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > & DupeList)
{
 //int   x,y;
	POSITION xPos, yPos;
	int   Count = 0;
	bool  Found;
 
	//for (x = 0; x < DupeList.GetSize(); x++)
 xPos = DupeList.GetHeadPosition();
	while (xPos)
	{

 	Found = false;
 	
		//y = 0;
		//while (!Found && y < DupeList.ElementAt(x)->GetSize())
		yPos = DupeList.GetAt(xPos)->GetHeadPosition();
		while (!Found && yPos)
		{
   CFileInfo *pFileInfo= DupeList.GetAt(xPos)->GetAt(yPos);

			//?? need to change --- possible multiple thread problem !!!!
			// nice little hack to compare file path only
   TCHAR OldFirstChar = pFileInfo->Name[0];
   pFileInfo->Name[0] = _T('\0');
   //

   switch(m_Option)
			{
			case IDC_IN_DIR:
				if ( (m_Path.CompareNoCase(pFileInfo->FullName) == 0) || (m_SubDirs && m_Path.CompareNoCase(CString(pFileInfo->FullName).Left(m_Path.GetLength() )) == 0 ) )
    {
					Found = true;
     pFileInfo->Selected = true;
					Count++;
				}
				break;
   case IDC_NOTIN_DIR:
				if ( (m_Path.CompareNoCase( CString(pFileInfo->FullName).Left(m_Path.GetLength())) != 0) )
    {
					Found = true;
     DupeList.GetAt(xPos)->GetAt(yPos)->Selected = true;
					Count++;
				}
				break;
			default:
				// should never get here
				ASSERT(false);
				break;
			}
   
			// repair the little hack
   pFileInfo->Name[0] = OldFirstChar;
			//

	  //y++;
			DupeList.GetAt(xPos)->GetNext(yPos);
		}

		// if we never found one and we are supposed to mark at least one, then simply mark the first file in the list
		if (!Found && CFileMarker::GetMarkAtLeastOne() )
		{
   DupeList.GetAt(xPos)->GetHead()->Selected = true;
			Count++;
		}
		//
  
	
		DupeList.GetNext(xPos);
	}

	return Count;
}

bool CFileLocationMarker::UpdateData(bool /*SaveAndValidate*/)
{

 m_SubDirs = m_FileLocationMarkerForm.m_SubDirs.GetCheck() == BST_CHECKED;
	m_Option = m_FileLocationMarkerForm.GetCheckedRadioButton(IDC_IN_DIR, IDC_NOTIN_DIR); // m_DirOption;
	m_FileLocationMarkerForm.m_Path.GetWindowText(m_Path);

	// make sure there is a '\' at the end of the path name
	if ( m_Path.Right(1) != _T("\\") ) m_Path += _T("\\");
 //


 // let caller know if good data was retrieved from config dialog
	if ( (m_Option != IDC_IN_DIR && m_Option != IDC_NOTIN_DIR) || m_Path.GetLength() <= 2 )
	 return false;
	else
		return true;
}
