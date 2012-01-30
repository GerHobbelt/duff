// FileDateMarker.cpp: implementation of the CFileDateMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileDateMarker::CFileDateMarker()
{
	m_sName = "File date";
	m_sDescription = "Mark files based on their creation date, last modified date, or last accessed date";
	m_pForm = (CDialog*)&m_FileDateMarkerForm;
	m_uiFormID = IDD_FILE_DATE_MARKER_FORM;

}

CFileDateMarker::~CFileDateMarker()
{

}


unsigned int CFileDateMarker::MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  DupeList)
{
	//int   x,y;
	POSITION xPos, yPos;
	int   Count = 0;
	COleDateTime SpecialTime;
 POSITION   SpecialIndex;
 bool  Found;
 bool AllTheSame;
 CList<CFileInfo *,CFileInfo *> *pFileInfoList;
 CFileInfo *pFileInfo;

	//for (x = 0; x < DupeList.GetSize(); x++)
	xPos = DupeList.GetHeadPosition();
	while (xPos)
	{

		Found = false;
  AllTheSame = true;
		pFileInfoList = DupeList.GetAt(xPos);
		
		yPos = pFileInfoList->GetHeadPosition();
  SpecialIndex = yPos;
		
		if (yPos)
		switch(m_Option)
		{
				case IDC_MOST_RECENTLY_CREATED:
				case IDC_LEAST_RECENTLY_CREATED:
     SpecialTime = DupeList.GetAt(xPos)->GetAt(yPos)->TimeCreated;
					break;
				case IDC_MOST_RECENTLY_MODIFIED:
				case IDC_LEAST_RECENTLY_MODIFIED:
					SpecialTime = DupeList.GetAt(xPos)->GetAt(yPos)->TimeLastModified;
					break;

				case IDC_MOST_RECENTLY_ACCESSED:
				case IDC_LEAST_RECENTLY_ACCESSED:
					SpecialTime = DupeList.GetAt(xPos)->GetAt(yPos)->TimeLastAccessed;
					break;		
		}
		

		//for (y = 1; y < pFileInfoArray->GetSize(); y++ )
		while (yPos)
		{
   
			pFileInfo = pFileInfoList->GetAt(yPos);

			switch ( m_Option )
			{
				case IDC_MOST_RECENTLY_CREATED:
					if ( SpecialTime < pFileInfo->TimeCreated )
					{
						SpecialTime = pFileInfo->TimeCreated;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
     else if ( AllTheSame && SpecialTime > pFileInfo->TimeCreated )
					{
						AllTheSame = false;
					}
					break;

				case IDC_LEAST_RECENTLY_CREATED:
					if ( SpecialTime > pFileInfo->TimeCreated )
					{
						SpecialTime = pFileInfo->TimeCreated;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && SpecialTime < pFileInfo->TimeCreated )
					{
						AllTheSame = false;
					}
					break;

				case IDC_MOST_RECENTLY_MODIFIED:
					if ( SpecialTime < pFileInfo->TimeLastModified )
					{
						SpecialTime = pFileInfo->TimeLastModified;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
     else if ( AllTheSame && SpecialTime > pFileInfo->TimeLastModified )
					{
						AllTheSame = false;
					}
					break;

				case IDC_LEAST_RECENTLY_MODIFIED:
					if ( SpecialTime > pFileInfo->TimeLastModified )
					{
						SpecialTime = pFileInfo->TimeLastModified;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && SpecialTime < pFileInfo->TimeLastModified )
					{
						AllTheSame = false;
					}
					break;

				case IDC_MOST_RECENTLY_ACCESSED:
					if ( SpecialTime < pFileInfo->TimeLastAccessed )
					{
						SpecialTime = pFileInfo->TimeLastAccessed;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && SpecialTime > pFileInfo->TimeLastAccessed )
					{
						AllTheSame = false;
					}

					break;
				case IDC_LEAST_RECENTLY_ACCESSED:
					if ( SpecialTime > pFileInfo->TimeLastAccessed )
					{
						SpecialTime = pFileInfo->TimeLastAccessed;
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && SpecialTime > pFileInfo->TimeLastAccessed )
					{
						AllTheSame = false;
					}
					break;		

				default:
					return 0;
					break;
			};


			pFileInfoList->GetNext(yPos);
		}
  
		if ( !AllTheSame || this->GetMarkAtLeastOne() )
		{
   pFileInfoList->GetAt(SpecialIndex)->Selected = true; 
			Count++;
		}


		DupeList.GetNext(xPos);
	}


	return Count;
}

bool CFileDateMarker::UpdateData(bool /*SaveAndValidate*/)
{
 bool GoodData;

 m_Option = m_FileDateMarkerForm.GetCheckedRadioButton(IDC_MOST_RECENTLY_CREATED, IDC_LEAST_RECENTLY_ACCESSED);
 
	switch ( m_Option )
	{
	 case IDC_MOST_RECENTLY_CREATED:
		case IDC_LEAST_RECENTLY_CREATED:
		case IDC_MOST_RECENTLY_MODIFIED:
		case IDC_LEAST_RECENTLY_MODIFIED:
		case IDC_MOST_RECENTLY_ACCESSED:
		case IDC_LEAST_RECENTLY_ACCESSED:
   GoodData = true;
		break;

		default:
			GoodData = false;
		break;
	}

	return GoodData;
}
