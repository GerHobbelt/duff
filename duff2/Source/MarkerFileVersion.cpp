// FileVersionMarker.cpp: implementation of the CFileVersionMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "defines.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFileVersionMarker::CFileVersionMarker()
{
	m_sName = "File version";
	m_sDescription = "Mark files based on their file version or product version";
	m_pForm = (CDialog*)&m_FileVersionMarkerForm;
	m_uiFormID = IDD_FILE_VERSION_MARKER_FORM;
 m_Option = IDC_FILE_VERSION_OLDEST;
}

CFileVersionMarker::~CFileVersionMarker()
{

}



unsigned int CFileVersionMarker::MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > &  DupeList)
{
	//int   x,y;
	POSITION xPos, yPos;
	int   Count = 0;
/*	union
	{
		QWORD SpecialVersion;
	 DWORD SpecialVersionParts[2];
	};
	union
	{
	 QWORD  TempVersion;
		DWORD  TempVersionParts[2];
 };
*/

	POSITION SpecialIndex;
 bool Found;
 bool AllTheSame;
 CFileInfo *pFileInfo, *pSpecialFileInfo;

	//for (x = 0; x < DupeList.GetSize(); x++)
	 xPos = DupeList.GetHeadPosition();
	 while (xPos)
	{

		Found = false;
  AllTheSame = true;
		yPos = DupeList.GetAt(xPos)->GetHeadPosition();
		SpecialIndex = yPos;

		if ( !DupeList.GetAt(xPos)->GetAt(SpecialIndex)->VersionDataIsValid)
		{
   DupeList.GetAt(xPos)->GetAt(SpecialIndex)->InitVersion();
		}
/*
		switch(m_Option)
		{
				case IDC_FILE_VERSION_OLDEST:
				case IDC_FILE_VERSION_NEWEST:
     
					SpecialVersionParts[0] = DupeList.ElementAt(x)->ElementAt(0)->VersionFileMS;
     SpecialVersionParts[1] = DupeList.ElementAt(x)->ElementAt(0)->VersionFileLS;
					break;
				case IDC_PRODUCT_VERSION_OLDEST:
				case IDC_PRODUCT_VERSION_NEWEST:
     SpecialVersionParts[0] = DupeList.ElementAt(x)->ElementAt(0)->VersionProductMS;
     SpecialVersionParts[1] = DupeList.ElementAt(x)->ElementAt(0)->VersionProductLS;
					break;
		}
		*/
		//SpedialIndex = 0;

  pSpecialFileInfo = DupeList.GetAt(xPos)->GetAt(SpecialIndex);

		//for (y = 1; y < DupeList.ElementAt(x)->GetSize(); y++ )
		while (yPos)
		{
   pFileInfo = DupeList.GetAt(xPos)->GetAt(yPos);

			if ( !pFileInfo->VersionDataIsValid)
			{
				pFileInfo->InitVersion();
			}

 		/*
			switch ( m_Option )
			{
				case IDC_FILE_VERSION_OLDEST:
	 		case IDC_FILE_VERSION_NEWEST:
			  TempVersionParts[0] = DupeList.ElementAt(x)->ElementAt(y)->VersionFileMS;
     TempVersionParts[1] = DupeList.ElementAt(x)->ElementAt(y)->VersionFileLS;
     break;
  		case IDC_PRODUCT_VERSION_OLDEST:
				case IDC_PRODUCT_VERSION_NEWEST:
	    TempVersionParts[0] = DupeList.ElementAt(x)->ElementAt(y)->VersionProductMS;
     TempVersionParts[1] = DupeList.ElementAt(x)->ElementAt(y)->VersionProductLS;
     break;
			}
   */

			switch ( m_Option )
			{
				case IDC_FILE_VERSION_OLDEST:
					if ( pFileInfo->VersionFile < pSpecialFileInfo->VersionFile )
					{
						pSpecialFileInfo = pFileInfo;
						Found = true;
						AllTheSame = false;
					}
     else if ( AllTheSame && pFileInfo->VersionFile  > pSpecialFileInfo->VersionFile )
					{
						AllTheSame = false;
					}
					break;

				case IDC_PRODUCT_VERSION_OLDEST:
					if ( pFileInfo->VersionProduct < pSpecialFileInfo->VersionProduct )
					{
						pSpecialFileInfo = pFileInfo;
						Found = true;
						AllTheSame = false;
					}
     else if ( AllTheSame && pFileInfo->VersionProduct  > pSpecialFileInfo->VersionProduct )
					{
						AllTheSame = false;
					}
					break;

				case IDC_FILE_VERSION_NEWEST:
 				if ( pFileInfo->VersionFile > pSpecialFileInfo->VersionFile )
					{
						pSpecialFileInfo = pFileInfo;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && pFileInfo->VersionFile < pSpecialFileInfo->VersionFile )
					{
						AllTheSame = false;
					}
					break;

				case IDC_PRODUCT_VERSION_NEWEST:
 				if ( pFileInfo->VersionProduct > pSpecialFileInfo->VersionProduct )
					{
						pSpecialFileInfo = pFileInfo;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && pFileInfo->VersionProduct < pSpecialFileInfo->VersionProduct )
					{
						AllTheSame = false;
					}
					break;

				default:
					return 0;
					break;
			};

			DupeList.GetAt(xPos)->GetNext(yPos);
		}
  
		if ( !AllTheSame || this->GetMarkAtLeastOne() )
		{
   DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Selected = true; 
			Count++;
		}

		DupeList.GetNext(xPos);
	}

	return Count;
}

bool CFileVersionMarker::UpdateData(bool /*SaveAndValidate*/)
{
 bool GotGoodData;

	m_Option = m_FileVersionMarkerForm.GetCheckedRadioButton(IDC_FILE_VERSION_OLDEST,IDC_PRODUCT_VERSION_NEWEST);

 switch ( m_Option )
	{
	 case IDC_FILE_VERSION_OLDEST:
	 case IDC_FILE_VERSION_NEWEST:
	 case IDC_PRODUCT_VERSION_OLDEST:
	 case IDC_PRODUCT_VERSION_NEWEST:
   GotGoodData = true;
		break;

		default:
			GotGoodData = false;
		break;
	}

	return GotGoodData;
}
