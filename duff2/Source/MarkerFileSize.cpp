// FileSizeMarker.cpp: implementation of the CFileSizeMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "MarkerFileSize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSizeMarker::CFileSizeMarker()
{

	m_sName = "File size";
	m_sDescription = "Mark smallest or biggest files";
	m_pForm = (CDialog*)&m_FileSizeMarkerForm;
	m_uiFormID = IDD_FILE_SIZE_MARKER_FORM;

}

CFileSizeMarker::~CFileSizeMarker()
{

}



unsigned int CFileSizeMarker::MakeSelections( CList< CList<CFileInfo *,CFileInfo *> *,CList<CFileInfo *,CFileInfo *> * > & DupeList)
{
 //int   x,y;
	POSITION xPos, yPos;
	int   Count = 0;
	//COleDateTime SpecialTime;
 POSITION   SpecialIndex;
 bool  Found;
 bool AllTheSame;
 
	//for (x = 0; x < DupeList.GetSize(); x++)
	xPos = DupeList.GetHeadPosition();
	while (xPos)
	{

		Found = false;
  AllTheSame = true;
				
		//for (y = 1; y < DupeList.ElementAt(x)->GetSize(); y++ )
		yPos = DupeList.GetAt(xPos)->GetHeadPosition();
  SpecialIndex = yPos;
		while (yPos)
		{
   
			switch ( m_Option )
			{
				case IDC_BIGGEST:
					if ( DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Size  < DupeList.GetAt(xPos)->GetAt(yPos)->Size )
					{
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
     else if ( AllTheSame && DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Size > DupeList.GetAt(xPos)->GetAt(yPos)->Size )
					{
						AllTheSame = false;
					}
					break;

				case IDC_SMALLEST:
					if ( DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Size > DupeList.GetAt(xPos)->GetAt(yPos)->Size )
					{
						SpecialIndex = yPos;
						Found = true;
						AllTheSame = false;
					}
					else if ( AllTheSame && DupeList.GetAt(xPos)->GetAt(SpecialIndex)->Size  < DupeList.GetAt(xPos)->GetAt(yPos)->Size )
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

bool CFileSizeMarker::UpdateData(bool /*SaveAndValidate*/)
{
	bool GotGoodData;

 m_Option = m_FileSizeMarkerForm.GetCheckedRadioButton(IDC_SMALLEST, IDC_BIGGEST);

	switch ( m_Option )
	{
	 case IDC_SMALLEST:
	 case IDC_BIGGEST:
			GotGoodData = true;
		break;

		default:
			GotGoodData = false;
		break;
	}

	return GotGoodData;
}
