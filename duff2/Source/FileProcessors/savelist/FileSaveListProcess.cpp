// FileSaveListProcess.cpp: implementation of the CFileSaveListProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <fstream>

#include "savelist.h"
#include "FileSaveListProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSaveListProcess::CFileSaveListProcess()
{
 m_pForm = &m_FileSaveListProcessForm;
	m_sName = "Save File List";
	m_sDescription = "This process save filenames of the marked files to a text file.";
	m_uiFormID = IDD_FILE_SAVELIST_PROCESS_FORM;

}

CFileSaveListProcess::~CFileSaveListProcess()
{

}


void CFileSaveListProcess::ProcessFiles ( CList<CFileInfo *, CFileInfo *> & FileList)
{
 CString Line;
	ofstream outfile;
	POSITION ListPos;
	CFileInfo *pFileInfo;

	outfile.open(m_Filename,  ios::out);
 if ( outfile.is_open() )
	{
		ListPos = FileList.GetHeadPosition();

  while (ListPos)
		{
			pFileInfo = FileList.GetAt(ListPos);
			//Line = m_LineFormat;
			//Line.Replace("%1", FileList.ElementAt(i).PathName
			if (pFileInfo->Selected)
			{
		  outfile.write( pFileInfo->FullName, _tcslen(pFileInfo->FullName ) );
			 outfile.write("\n",1);
			}

		 FileList.GetNext(ListPos);
		}
  outfile.close();
	}
	else
	{

	}
}

bool CFileSaveListProcess::UpdateData(bool /*SaveAndValidate*/)
{
	//m_FileSaveListProcessForm.UpdateData(true);

	m_FileSaveListProcessForm.m_Filename.GetWindowText(m_Filename);
	m_FileSaveListProcessForm.m_LineFormat.GetWindowText(m_LineFormat);
 m_AllFiles = m_FileSaveListProcessForm.GetCheckedRadioButton (IDC_WHATFILES_OPTION1,IDC_WHATFILES_OPTION2) == IDC_WHATFILES_OPTION2;
 m_NewLine = m_FileSaveListProcessForm.m_NewLine.GetCheck() == BST_CHECKED;
 
	return true;
}
