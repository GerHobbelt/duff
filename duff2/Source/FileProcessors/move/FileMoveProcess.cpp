// FileMoveProcess.cpp: implementation of the CFileMoveProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "move.h"
#include "FileMoveProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "..\..\DuffStatus.h"

extern sDuffStatus * pDuffStatus;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileMoveProcess::CFileMoveProcess()
{
 m_pForm = &m_FileMoveProcessForm;
	m_sName = "Move Files";
	m_sDescription = "This process moves the marked files to a specified location.";
	m_uiFormID = IDD_FILE_MOVE_PROCESS_FORM;

}

CFileMoveProcess::~CFileMoveProcess()
{

}



void CFileMoveProcess::ProcessFiles ( CList<CFileInfo *, CFileInfo *> & FileList)
{
 CString Msg;
	SHFILEOPSTRUCT fos;
 TCHAR pDirBuffer[MAX_PATH];
 TCHAR pFilenameBuffer[MAX_PATH];
 CFileInfo * pFileInfo;
 POSITION ListPos;

	// setup to directory buffer
// pDirBuffer = new TCHAR[m_Dir.GetLength()+2];
 strcpy( pDirBuffer, (LPCSTR) m_Dir);
 pDirBuffer[m_Dir.GetLength()] = '\0';
 pDirBuffer[m_Dir.GetLength()+1] = '\0';
 //

	// setup struct
 fos.hwnd = AfxGetMainWnd()->m_hWnd;
 fos.wFunc= FO_MOVE;
	fos.pTo =  pDirBuffer;
	fos.fFlags = FOF_ALLOWUNDO | FOF_NOERRORUI;
	fos.lpszProgressTitle = "NULL";
 //
	
	// set confirmation flag
	if ( m_YesToAll ) fos.fFlags |= FOF_NOCONFIRMATION;
 //


	/*	for ( int i = 0; i < FileList.GetSize(); i++)
		{
			//if ( ((CDuffDlg*)GetParent()->GetParent())->m_DuplicatePage.m_DupeList.GetCheck(i) == BST_CHECKED )
			//{
				Temp = FileList.ElementAt(i).m_Filename;
				//TotalLength += Temp.GetLength() +1;
				FilesToDelete.Add(Temp);
			//}
		}
		*/


 // update progress information
	pDuffStatus->Lock();
	pDuffStatus->CurrentTaskStr = "Moving selected duplicate files...";
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
		if ( pFileInfo->Selected)
		{
			if ( ! (pFileInfo->Attributes & FILE_ATTRIBUTE_READONLY)  || m_MoveReadOnly )
			{

				/*				// remove read-only attribute
			 if ( FileList.ElementAt(i)->ReadOnly )
			 {
			 	DWORD FileAttributes;
			 	FileAttributes = GetFileAttributes( FileList.ElementAt(i)->Filename )
			 	FileAttributes ^= FILE_ATTRIBUTE_READONLY;
     SetFileAttributes(FileList.ElementAt(i)->Filename,FileAttributes );
			 }*/

	
			 _tcscpy(pFilenameBuffer, pFileInfo->GetFullName() );

    UINT			Length = _tcslen( pFilenameBuffer );

			//		for (int x = 0; x < FileList.ElementAt(i)->Filename.GetLength(); x++)
	//		{
		//		pFilenameBuffer[x] = FileList.ElementAt(i)->Filename.GetAt(x);
		//	}

		 	pFilenameBuffer[Length] = 0;
		 	pFilenameBuffer[Length+1] = 0;

			 fos.pFrom = pFilenameBuffer;

			 //		g_DupeFileFind.GetDuffDlg()->m_CurrentTaskInfoText.SetWindowText(FileList.ElementAt(i)->GetFullName());
	   //		g_DupeFileFind.GetDuffDlg()->m_CurrentTaskInfoText.RedrawWindow();

		 	// update progress information
		  pDuffStatus->Lock();
		  pDuffStatus->CurrentTaskInfo = pFileInfo->GetFullName();
		  pDuffStatus->SubProgress1.Pos++;
		  pDuffStatus->Unlock();
		  //

			
		 	/*	
		 	Msg.Format("Moving:\n%s\nto:\n%s",FileList.ElementAt(i)->m_Filename,fos.pTo);
		 	MessageBox(NULL,Msg,"FYI",MB_OK);
	   */

				if	( SHFileOperation(&fos) )
				{
					Msg.Format("ERROR moving file: %s to %s",pFileInfo->GetFullName(),m_Dir);
		//			g_DupeFileFind.GetDuffDlg()->Log(Msg);
				}
				else
				{
					Msg.Format("Moved file: %s to %s",pFileInfo->GetFullName(),m_Dir);
	//				g_DupeFileFind.GetDuffDlg()->Log(Msg);
				}
		//		g_DupeFileFind.GetDuffDlg()->m_ProgressEntire.StepIt();
	//			delete []pFilenameBuffer;
			}

		}

		FileList.GetNext(ListPos);
	}				
//	delete[] pDirBuffer;

}

bool CFileMoveProcess::UpdateData(bool /*SaveAndValidate*/)
{

	m_FileMoveProcessForm.m_Dir.GetWindowText(m_Dir);

	m_MoveReadOnly = (m_FileMoveProcessForm.m_MoveReadOnly.GetCheck() == BST_CHECKED);
 m_YesToAll = (m_FileMoveProcessForm.m_YesToAll.GetCheck() == BST_CHECKED);
 
	
	if (m_Dir.GetLength() <=2)
		return false;
	else
	 return true;
}


