// FileDeleteProcess.cpp: implementation of the CFileDeleteProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "delete.h"
#include "FileDeleteProcess.h"

//#include "..\..\DuplicateFileFind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//extern CDuplicateFileFind g_DupeFileFind;
#include "..\..\DuffStatus.h"
extern sDuffStatus * pDuffStatus;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileDeleteProcess::CFileDeleteProcess()
{
	m_pForm = &m_FileDeleteProcessForm;
	m_sName = "Delete Files";
	m_sDescription = "This process deletes the marked files, optionally to the recycle bin.";
	m_uiFormID = IDD_FILE_DELETE_PROCESS_FORM;

}

CFileDeleteProcess::~CFileDeleteProcess()
{

}

void CFileDeleteProcess::ProcessFiles ( CList<CFileInfo *, CFileInfo *> & FileList)
{
	SHFILEOPSTRUCT fos;
 CString Msg;
	TCHAR *buffer;
 POSITION ListPos;
 CFileInfo * pFileInfo;

 // update progress information
	pDuffStatus->Lock();
	pDuffStatus->CurrentTaskStr = "Deleting selected duplicate files...";
	pDuffStatus->CurrentTaskInfo = "";
	pDuffStatus->SubProgress1.Min = 0;
	pDuffStatus->SubProgress1.Pos = 0;
	pDuffStatus->SubProgress1.Max = FileList.GetCount();
	pDuffStatus->Unlock();
	//


	ListPos = FileList.GetHeadPosition();
	
	while (ListPos)
	{
		pFileInfo = FileList.GetAt(ListPos);
  
		// process only the selected files
		if (pFileInfo->Selected)
		{
			if ( m_Recycle )
			{

			// pre-setup struct
			fos.hwnd = AfxGetMainWnd()->m_hWnd;
			fos.wFunc=   FO_DELETE;
			fos.pTo =    NULL;
			fos.fFlags = NULL; //FOF_NOERRORUI;
			fos.lpszProgressTitle = "NULL";
			//

			// set delete to recycle bin flag
			if ( m_Recycle ) fos.fFlags |= FOF_ALLOWUNDO;
			//

			// set confirmation flag
			if ( m_YesToAll ) fos.fFlags |= FOF_NOCONFIRMATION;
			//

		UINT TotalLength = _tcslen (pFileInfo->FullName ) ;
			// create filename buffer and fill with filename

			buffer = new TCHAR[ TotalLength + sizeof(TCHAR) * 4];
		//	for (int x = 0; x < FileList.ElementAt(i)->cFileName.GetLength(); x++)
		//	{
	//			buffer[x] = FileList.ElementAt(i)->Filename.GetAt(x);
	//		}

			_tcscpy(buffer, pFileInfo->FullName);

			buffer[TotalLength] = 0;
			buffer[TotalLength+1] = 0;
			//

			// set filename in struct
			fos.pFrom = buffer;
			//

			// update progress information
			pDuffStatus->Lock();
			pDuffStatus->CurrentTaskInfo = pFileInfo->FullName;
			pDuffStatus->SubProgress1.Pos ++;
			pDuffStatus->Unlock();
			//
				
			/*
			Msg.Format("Performing:\n%s (%s)\n on file:\n%s",m_Name, m_Recycle ? "to recycle bin" : "direct", FileList.ElementAt(i)->Filename);
			MessageBox(NULL,Msg,"FYI",MB_OK);
			*/

			if	( SHFileOperation(&fos) )
			{
				Msg.Format("ERROR %s file: %s",m_Recycle ? "recycling" : "deleting", pFileInfo->FullName);
				//g_DupeFileFind.GetDuffDlg()->Log(Msg);

				
				// update status and log
				pDuffStatus->Lock();			
				pDuffStatus->LogQueue.Add(Msg);
				pDuffStatus->Unlock();
				//

			}
			else
			{
				Msg.Format("%s file: %s",m_Recycle ? "Recycled" : "Deleted", pFileInfo->FullName);
			//g_DupeFileFind.GetDuffDlg()->Log(Msg);

				
				// update status and log
				pDuffStatus->Lock();
				pDuffStatus->LogQueue.Add(Msg);
				pDuffStatus->Unlock();
				//

			}
					

			// update progress info
	//		g_DupeFileFind.GetDuffDlg()->m_ProgressEntire.StepIt();
			//

			// free filename buffer 
			delete []buffer;
			//
			}

			
			else
			{
				Msg.Format("%s file: %s", DeleteFile(pFileInfo->FullName) ? "Deleted" : "ERROR deleting", pFileInfo->FullName);
				
				
				// update status and log
				pDuffStatus->Lock(); 
				pDuffStatus->CurrentTaskInfo = pFileInfo->FullName;
				pDuffStatus->LogQueue.Add(Msg);
				pDuffStatus->Unlock();
				//

			}
			
  }

  FileList.GetNext(ListPos);
	} // while

}

bool CFileDeleteProcess::UpdateData(bool /*SaveAndValidate*/)
{

	m_DeleteReadOnly = (m_FileDeleteProcessForm.m_DeleteReadOnly.GetCheck() == BST_CHECKED);
 m_Recycle = ( m_FileDeleteProcessForm.GetCheckedRadioButton(IDC_RECYCLE,IDC_DELETE) == IDC_RECYCLE) ;
 m_YesToAll = (m_FileDeleteProcessForm.m_YesToAll.GetCheck() == BST_CHECKED);

#if 0
 if ( m_Recycle != IDC_RECYCLE && m_Recycle != IDC_DELETE )
		return false;
	else
#endif
		return true;
}


