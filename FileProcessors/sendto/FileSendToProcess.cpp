// FileSendToProcess.cpp: implementation of the CFileSendToProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sendto.h"
#include "FileSendToProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSendToProcess::CFileSendToProcess() 
{
 m_pForm = &m_FileSendToProcessForm;
	m_sName = "Send to Program";
	m_sDescription = "This process executes a program with the marked files as parameters";
	m_uiFormID = IDD_FILE_SENDTO_PROCESS_FORM;
 //AfxMessageBox("1");

	//m_FileSendToProcessForm.Create(IDD_FILE_SENDTO_PROCESS_FORM, NULL);
// AfxMessageBox("2");
}

CFileSendToProcess::~CFileSendToProcess()
{

}

void CFileSendToProcess::ProcessFiles ( CList<CFileInfo *, CFileInfo *> & Files)
{
	CString sParams;
 CString sFilenames;
	POSITION ListPos;

 if ( Files.GetCount() )
	if ( m_Option == IDC_OPTION_SEPERATE )
	{
		
		ListPos = Files.GetHeadPosition();
		while (ListPos)
		{
			sParams = m_Parameters;
			sFilenames.Format("\"%s\"",Files.GetAt(ListPos)->FullName);
			sParams.Replace("%s",sFilenames);
			ShellExecute(NULL, "open", m_ProgramName, sParams, "", SW_NORMAL);
		
		 Files.GetNext(ListPos);
		}
	}
	else
	{
		ListPos = Files.GetHeadPosition();
		while (ListPos)
		{
			if (ListPos == Files.GetHeadPosition() ) sFilenames += " ";
			sFilenames += '\"';
			sFilenames += Files.GetAt(ListPos)->FullName;
			sFilenames += '\"';

			Files.GetNext(ListPos);
		}
		m_Parameters.Replace("%s",sFilenames);
		ShellExecute(NULL, "open", m_ProgramName, m_Parameters, "", SW_NORMAL);

	}
}

bool CFileSendToProcess::UpdateData(bool SaveAndValidate)
{
	m_FileSendToProcessForm.m_ProgramCtrl.GetWindowText(m_ProgramName );
	m_FileSendToProcessForm.m_ParametersCtrl.GetWindowText(m_Parameters);
 m_Option = m_FileSendToProcessForm.GetCheckedRadioButton(IDC_OPTION_SEPERATE,IDC_OPTION_COMBINED);
 
	return true;
}
