// DuplicateFileFind.cpp: implementation of the CDuplicateFileFind class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//#include "sound.h"

#include "duff.h"
#include "DuffDlg.h"
#include "util.h"
#include "DuplicateFileFind.h"
#include "Layer.h"
#include "LayerFilename.h"

CDuplicateFileFind g_DupeFileFind;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <stdio.h>

/*

// function to determine whether an item is in a list or not
template<class T1>
POSITION  Find( T1 &str , CList< T1,  T1& > & strlist)
{
	bool found = false;
 int x = 0;
	POSITION pos = strlist.GetHeadPosition();
	while (pos && !found)
	{
  if (strlist.GetAt(pos) == str) found = true;
		strlist.GetNext(pos);
	}
 return found ? POSITION : NULL;
}


*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuplicateFileFind::CDuplicateFileFind()
{

 m_LayerLogic = LOGIC_OR;

 m_FileFilters.Add(&m_FileAttributesFilter);
 m_FileFilters.Add(&m_FileSizeFilter);
 m_FileFilters.Add(&m_FileSateFilter);
 m_FileFilters.Add(&m_FileContentsFilter);

	m_FileComparisonLayers.Add(&m_FilenameLayer);
 m_FileComparisonLayers.Add(&m_FileDataLayer);
 m_FileComparisonLayers.Add(&m_FileTextDataLayer);
 m_FileComparisonLayers.Add(&m_MP3FileDataLayer);

	m_FileMarkers.Add(&m_FilenameMarker);
	m_FileMarkers.Add(&m_FileDateMarker);
 m_FileMarkers.Add(&m_FileLocationMarker);
 m_FileMarkers.Add(&m_FileSizeMarker);
 m_FileMarkers.Add(&m_FileVersionMarker);

//	m_FileProcesses.Add(&m_FileDeleteProcess);
// m_FileProcesses.Add(&m_FileMoveProcess);
// m_FileProcesses.Add(&m_FileSaveListProcess);
// m_FileProcesses.Add(&m_FileNullProcess);

	m_IncludeHiddenDirs     = BST_INDETERMINATE;
	m_IncludeSystemDirs     = BST_INDETERMINATE;
	m_IncludeReadOnlyDirs   = BST_INDETERMINATE;
	m_IncludeArchivedDirs   = BST_INDETERMINATE;
	m_IncludeCompressedDirs = BST_INDETERMINATE;

}

CDuplicateFileFind::~CDuplicateFileFind()
{
	CleanUp();
	RemoveAllSearchPaths();
}


void CDuplicateFileFind::CleanUp()
{
	while (!m_FileInfos.IsEmpty())
	{
		CFileInfo *elem = m_FileInfos.RemoveTail();
		ASSERT_VALID(elem);
		delete elem;
	}

	//m_IncludeDirectories.RemoveAll();
	m_FileInfos.RemoveAll();

	while (!m_DuplicateFiles.IsEmpty())
	{
		CList<CFileInfo *,CFileInfo *> *elem = m_DuplicateFiles.RemoveTail();
		ASSERT_VALID(elem);
		delete elem;
	}

	m_DuplicateFiles.RemoveAll();
}

unsigned int CDuplicateFileFind::BuildFileList()
{
	CString TempStr;
	CList<CDirectoryInfo,CDirectoryInfo &> Directories;
	int i;
	unsigned int FileCount = 0;
	POSITION Position;
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	CString SearchPath;
	bool Good;
	CFileInfo *pFileInfo;

	// update status and log
	m_DuffStatus.Lock();
	m_DuffStatus.CurrentTaskStr  = StringFromResource(IDS_STATUS_CREATING_DIR_LIST);
	m_DuffStatus.CurrentTaskInfo = NULL_STR;
	m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_FILE_LIST_GENERATION_STARTED) );
	m_DuffStatus.Unlock();
	//

	// Empty file list
	CleanUp();
 //


	// build directory list
	for( i = 0; i < m_UserIncludeDirectories.GetSize(); i++)
	{
		Directories.AddTail( m_UserIncludeDirectories.ElementAt(i) );
		if ( m_UserIncludeDirectories.ElementAt(i).SubDirs )
		{
			AddSubDirsToList( Directories, m_UserIncludeDirectories.ElementAt(i) );
		}
	}
	//

	// update status and log
	m_DuffStatus.Lock();
	m_DuffStatus.SubProgress2.Min = 0;
	m_DuffStatus.SubProgress2.Max = Directories.GetCount();
	m_DuffStatus.SubProgress2.Pos = 0;
	m_DuffStatus.CurrentTaskStr = StringFromResource(IDS_STATUS_SEARCHING_FOR_FILES);
	m_DuffStatus.Unlock();
	//


	// build file list
	Position = Directories.GetHeadPosition();
	while (Position)
	{
		// update status and log
		if (m_DuffStatus.LockIfUnlocked())
		{
		 m_DuffStatus.CurrentTaskInfo = Directories.GetAt(Position).FullPathName;
	  m_DuffStatus.SubProgress2.Pos ++;
		 m_DuffStatus.Unlock();
		}
		//

  for (i = 0; i < m_FileMasks.GetSize(); i++)
		{
 		if ( Directories.GetAt(Position).FullPathName[ _tcslen(Directories.GetAt(Position).FullPathName) -1]  == '\\' )
				SearchPath.Format( _T("%s%s"), Directories.GetAt(Position).FullPathName ,m_FileMasks.ElementAt(i) );
			else
	 		SearchPath.Format( _T("%s\\%s"), Directories.GetAt(Position).FullPathName ,m_FileMasks.ElementAt(i) );

			hFind = FindFirstFile(SearchPath, &FindFileData);

			if (hFind != INVALID_HANDLE_VALUE)
			{
				Good = true;
				while (Good)
				{
					if ( ! (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
					{
						pFileInfo = new CFileInfo(Directories.GetAt(Position).FullPathName, FindFileData);
						m_FileInfos.AddTail(pFileInfo);
						FileCount++;
					}
					Good = FindNextFile(hFind,&FindFileData) != 0;
				}
			}
			FindClose(hFind);
		}
		Directories.GetNext(Position);
	}
	//

	// update status and log
	m_DuffStatus.Lock();
 TempStr.Format( StringFromResource(IDS_LOGTEXT_FILE_LIST_GENERATION_FINISHED) ,m_FileInfos.GetCount());
	m_DuffStatus.LogQueue.Add(TempStr);
 m_DuffStatus.CurrentTaskStr  = NULL_STR;
 m_DuffStatus.CurrentTaskInfo = NULL_STR;
 m_DuffStatus.Unlock();
 //

 return FileCount;
}



// Adds a directory and all its subdirectories to a list of directories
void CDuplicateFileFind::AddSubDirsToList(CList<CDirectoryInfo,CDirectoryInfo &> & Directories, const CDirectoryInfo & Dir)
{
 HANDLE hFind;
	CDirectoryInfo DirEntry;
 CString SearchPath;
 WIN32_FIND_DATA FindFileData;
	bool Good;
 bool bDirValid;

	// ignore blank directory name
	if (!Dir.FullPathName[0])
		return;
 //

 // format search path string
	if ( Dir.FullPathName[ _tcsclen(Dir.FullPathName) -1] == _T('\\') )
		 SearchPath.Format( _T("%s%s") ,Dir.FullPathName, _T("*.*") );
	 else
		 SearchPath.Format( _T("%s\\%s") ,Dir.FullPathName, _T("*.*") );
 //


	// find first file
	hFind = FindFirstFile(SearchPath, &FindFileData);
	//

	// if we found a file, continue
	if (hFind != INVALID_HANDLE_VALUE)
	{
		Good = true;

		// continue to look for files
		while (Good)
		{
   if ( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) && _tcscmp(FindFileData.cFileName, _T(".") ) && _tcscmp(FindFileData.cFileName, _T("..") ) )
			{

				bDirValid =
					( (m_IncludeReadOnlyDirs   == BST_INDETERMINATE) || ( (m_IncludeReadOnlyDirs   == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY   )!=0) ) ) &&
					( (m_IncludeHiddenDirs     == BST_INDETERMINATE) || ( (m_IncludeHiddenDirs     == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN     )!=0) ) ) &&
					( (m_IncludeSystemDirs     == BST_INDETERMINATE) || ( (m_IncludeSystemDirs     == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM     )!=0) ) ) &&
					( (m_IncludeCompressedDirs == BST_INDETERMINATE) || ( (m_IncludeCompressedDirs == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED )!=0) ) ) &&
					( (m_IncludeArchivedDirs   == BST_INDETERMINATE) || ( (m_IncludeArchivedDirs   == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE    )!=0) ) ) &&
					( (m_IncludeEncryptedDirs  == BST_INDETERMINATE) || ( (m_IncludeEncryptedDirs  == BST_CHECKED) == ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED  )!=0) ) );


				TRACE2("%s %s hidden\n",FindFileData.cFileName, (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? _T("is") : _T("is not"));

				if ( bDirValid )
				{
					// add the found directory to the list of directories
					DirEntry.Init(FindFileData.cFileName, (TCHAR*)Dir.FullPathName, Dir.SubDirs);
					Directories.AddTail( DirEntry );

					// only when subdirs are requested, do we recurse:
					if (Dir.SubDirs)
					{
						AddSubDirsToList(Directories, DirEntry);
					}
					//
				}

				// update status and log
				if (m_DuffStatus.LockIfUnlocked())
				{
				 m_DuffStatus.CurrentTaskInfo = Dir.FullPathName;
				 m_DuffStatus.Unlock();
				}
				//
			}
			// find next file
			Good = FindNextFile(hFind,&FindFileData) != 0;
			//
		}
	}
	// close the find tool
	FindClose(hFind);
	//

	return;
}


// Starts the duplicate file search engine
int CDuplicateFileFind::StartSearch()
{
 CString TempStr;
 int DupeCount;
 int i;
 unsigned int uiTotalFiltered = 0;
	unsigned int uiFiltered = 0;
 bool Filter = false;

	// make sure we are not already running
 if ( m_DuffStatus.Status != DUFFSTATUS_STOPPED )
		return -1;
 //

	// we are running now
 m_DuffStatus.Status = DUFFSTATUS_RUNNING;
	//

 // delete existing duplicate list sets and empty the array
	CleanUp();
 //

 // generate file list
	BuildFileList();
	//

	i = 0;
	while ( !Filter && i < m_FileFilters.GetSize() )
	{
		if ( m_FileFilters.ElementAt(i)->IsSelected() )
		{
			Filter = true;
		}
		i++;
	}
	if (Filter)
	{
		// update status and log
		m_DuffStatus.Lock();
		m_DuffStatus.CurrentTaskStr  = StringFromResource(IDS_STATUS_FILTERING);
		m_DuffStatus.CurrentTaskInfo = NULL_STR;
		m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_FILTER_STARTED) );
		m_DuffStatus.Unlock();
		//

		// prefilter file list
		for ( i = 0; i < m_FileFilters.GetSize(); i ++)
		{
			if ( m_FileFilters.ElementAt(i)->IsSelected() )
			{
				// update status and log
				m_DuffStatus.Lock();
				TempStr.Format( StringFromResource(IDS_STATUS_FILTERING_WITH_FILTER) ,m_FileFilters.ElementAt(i)->GetName());
				m_DuffStatus.CurrentTaskStr = TempStr;
				m_DuffStatus.Unlock();
				//
				uiFiltered = m_FileFilters.ElementAt(i)->FilterDuplicateList(m_FileInfos);
				// update status and log
				m_DuffStatus.Lock();
				TempStr.Format( StringFromResource(IDS_LOGTEXT_FILTERED_OUT) ,m_FileFilters.ElementAt(i)->GetName(), uiFiltered);
				m_DuffStatus.LogQueue.Add(TempStr);
				m_DuffStatus.Unlock();
				//
				uiTotalFiltered += uiFiltered;
			}
		}
		//

		// free unused memory in the array
	//	m_FileInfos.FreeExtra();
		//

		// update status and log
		m_DuffStatus.Lock();
		TempStr.Format( StringFromResource(IDS_LOGTEXT_FILTER_FINISHED) ,uiTotalFiltered);
		m_DuffStatus.LogQueue.Add(TempStr);
		m_DuffStatus.CurrentTaskStr  = NULL_STR;
		m_DuffStatus.CurrentTaskInfo = NULL_STR;
		m_DuffStatus.Unlock();
		//
	}

	// build duplicate list
	DupeCount = BuildDuplicateList();
 //

	// update status and log
	TempStr.Format( StringFromResource(IDS_LOGTEXT_DUPESEARCH_COMPLETE) ,DupeCount, GetNumDuplicates(), m_DuplicateFiles.GetCount() );
	m_DuffStatus.Lock();
	m_DuffStatus.MainProgress.Pos = 0;
	m_DuffStatus.SubProgress1.Pos = 0;
	m_DuffStatus.SubProgress2.Pos = 0;
	m_DuffStatus.LogQueue.Add(TempStr);
	m_DuffStatus.CurrentTaskStr  = StringFromResource(IDS_STATUS_IDLE);
	m_DuffStatus.CurrentTaskInfo = NULL_STR;
	m_DuffStatus.Unlock();
	//

 // we are finished
	m_DuffStatus.Status = DUFFSTATUS_STOPPED;
 //

	return DupeCount;
}

int CDuplicateFileFind::StopSearch()
{
	m_DuffStatus.Status = DUFFSTATUS_STOPPED;
	return 0;
}

int CDuplicateFileFind::PauseSearch()
{
	m_DuffStatus.Status = DUFFSTATUS_PAUSED;
	return 0;
}

int CDuplicateFileFind::ResumeSearch()
{
	if (m_DuffStatus.Status == DUFFSTATUS_PAUSED)
		m_DuffStatus.Status = DUFFSTATUS_RUNNING;

	return 0;
}




UINT CDuplicateFileFind::BuildDuplicateList()
{
	int x,y,z;
	int NumFileInfos = 0;
	UINT DupeCount = 0;
	static int DupeSetCount = 0;
	CList<CFileInfo *, CFileInfo *> * pDupeList;
	bool bDuplicate;
	CString Msg;
	CFileInfo *File1 = NULL, *File2 = NULL;
	CString Temp;
	POSITION xPos, yPos;

	ULONGLONG ullProgressBarPos = 0;
	ULONGLONG ullProgressBarMax = 0;


	// get number of file infos to proess
	NumFileInfos = m_FileInfos.GetCount();
	//

	// calculate the number of comparisons that will take place
	ullProgressBarMax = ( (ULONGLONG)NumFileInfos * ((ULONGLONG)NumFileInfos + 1) ) / 2;
 //

	// update progress info
	if ( m_DuffStatus.LockIfUnlocked() )
	{
		m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_DUPELIST_BUILD_FINISHED) );
		m_DuffStatus.CurrentTaskStr  = StringFromResource(IDS_STATUS_BUILDING_DUPELIST);
		m_DuffStatus.CurrentTaskInfo = NULL_STR;
		m_DuffStatus.SubProgress1.Min = 0;
		m_DuffStatus.SubProgress1.Max = 1000;
		m_DuffStatus.SubProgress1.Pos = 0;
		m_DuffStatus.Unlock();
	}
	//




	xPos = m_FileInfos.GetHeadPosition();
	//while (x < NumFileInfos && m_DuffStatus.Status != DUFFSTATUS_STOPPED)
	x =0;
	while ( xPos && m_DuffStatus.Status != DUFFSTATUS_STOPPED)
	{
		THREAD_CHECK_FOR_PAUSE
		File1 = m_FileInfos.GetAt(xPos);

		// update status and log
		if ( m_DuffStatus.LockIfUnlocked() )
		{
		 Msg.Format( _T("\"%s\"") ,File1->GetFullName() );
		 m_DuffStatus.CurrentTaskInfo = Msg;
		 m_DuffStatus.Unlock();
		}
		//
		TRACE1( "Working with: %s...\n" ,File1->GetName());

		pDupeList = NULL;

		yPos = xPos;
		m_FileInfos.GetNext(yPos);
		y = x+1;
		if ( File1->Duplicate || File1->Unaccessible )
		{
			ullProgressBarPos += (m_FileInfos.GetCount() - y - 1);
		}
		else
		{
			m_FileInfos.GetHeadPosition();
			//while ( y < NumFileInfos && m_DuffStatus.Status != DUFFSTATUS_STOPPED )
			while ( yPos && !File1->Unaccessible && m_DuffStatus.Status != DUFFSTATUS_STOPPED )
			{
				File2 = m_FileInfos.GetAt(yPos);
			//TRACE("Working against: %s...\n",File2->Name);
 					ullProgressBarPos ++;

				if ( !File2->Duplicate && !File2->Unaccessible  )
				{
					if ( m_LayerLogic == LOGIC_AND )
					{
						bDuplicate = true;
						z = 0;
						while ( bDuplicate && !File1->Unaccessible && z < m_FileComparisonLayers.GetSize() )
						{
							if ( m_FileComparisonLayers.ElementAt(z)->IsSelected() ) //
							{

								bDuplicate =  m_FileComparisonLayers.ElementAt(z)->FilesEqual((*File1),(*File2));

							}

							z++;
						}

						// update status and log
						if ( m_DuffStatus.LockIfUnlocked() )
						{
							m_DuffStatus.SubProgress1.Pos = (int) (1000 * ulonglongdivide(ullProgressBarPos,ullProgressBarMax));
							m_DuffStatus.Unlock();
						}
						//

					}
					else // LOGIC_OR
					{
						bDuplicate = false;
						z = 0;
						while ( !bDuplicate && !File1->Unaccessible && z < m_FileComparisonLayers.GetSize() )
						{

							if ( m_FileComparisonLayers.ElementAt(z)->IsSelected() ) //
							{

								// speed hack!
        //if ( z != 2 || File1->Size == File2->Size )
								 bDuplicate =  m_FileComparisonLayers.ElementAt(z)->FilesEqual((*File1),(*File2));
								//else
								//	bDuplicate = false;
							}

							z++;
						}

						// update status and log
						if ( m_DuffStatus.LockIfUnlocked() )
						{
							m_DuffStatus.SubProgress1.Pos = (int) (1000 * ulonglongdivide(ullProgressBarPos,ullProgressBarMax));
							m_DuffStatus.Unlock();
						}
						//


					}


					if ( bDuplicate )
					{
						if ( !pDupeList )
						{
							DupeCount++;
							DupeSetCount++;
							pDupeList = new CList<CFileInfo *, CFileInfo *>;
							File1->Duplicate = true;
							File1->FirstFile = true;
							File1->SetID = DupeSetCount;
							pDupeList->AddTail(File1);

							// add duplicate to list view
							m_DuffStatus.Lock();
							ASSERT(File1);
							m_DuffStatus.DupeQueue.Add(File1);
							m_DuffStatus.Unlock();
							//

						}
						File2->Duplicate = true;
						File2->SetID = DupeSetCount;
						pDupeList->AddTail(File2);
						DupeCount++;

				//		progressbar_range -= (m_FileInfos.GetSize() - (x-1) - 2);    //??

						// update status and log
						m_DuffStatus.Lock();
						ASSERT(File2);
						m_DuffStatus.DupeQueue.Add(File2);
						m_DuffStatus.SubProgress1.Pos = (int) (1000 * ulonglongdivide(ullProgressBarPos,ullProgressBarMax));
					//	m_DuffStatus.SubProgress1.Max = progressbar_range;
						m_DuffStatus.Unlock();
						//

					}

				}
				y++;
				m_FileInfos.GetNext(yPos);
			}
		}
		// add the duplicate set to the array of duplicate sets
		if ( pDupeList )
		{
			m_DuplicateFiles.AddTail(pDupeList);
		}
		x++;
		m_FileInfos.GetNext(xPos);
	}


	// update status and log
 m_DuffStatus.Lock();
 m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_DUPELIST_BUILD_FINISHED) );
	m_DuffStatus.CurrentTaskStr  = "Idle";
 m_DuffStatus.CurrentTaskInfo = "";
	m_DuffStatus.SubProgress1.Min = 0;
	m_DuffStatus.SubProgress1.Max = 0;
 m_DuffStatus.SubProgress1.Pos = 0;
	m_DuffStatus.Unlock();
 //

 return DupeCount;
}



UINT CDuplicateFileFind::GetNumDuplicates()
{
 UINT Count = 0;
 POSITION Pos;

	Pos = m_DuplicateFiles.GetHeadPosition();
	while (Pos)
	{
  Count += m_DuplicateFiles.GetAt(Pos)->GetCount() - 1;
		m_DuplicateFiles.GetNext(Pos);
	}

	/*
	for (register int i = 0; i < m_DuplicateFiles.GetCount(); i++)
	{
		Count += m_DuplicateFiles.ElementAt(i)->GetSize() -1;
	}
*/
	return Count;
}


bool CDuplicateFileFind::CheckForFullSetMarks()
{
	bool All = false;
//	int x = 0;

 UINT Count = 0;
 POSITION xPos, yPos;

	xPos = m_DuplicateFiles.GetHeadPosition();
	while (xPos)
	{
		All = true;

		yPos = m_DuplicateFiles.GetAt(xPos)->GetHeadPosition();
		while (All && yPos)
		{
   if ( ! m_DuplicateFiles.GetAt(xPos)->GetAt(yPos)->Selected ) All = false;
   m_DuplicateFiles.GetAt(xPos)->GetNext(yPos);
		}
  Count += m_DuplicateFiles.GetAt(xPos)->GetCount() - 1;
		m_DuplicateFiles.GetNext(xPos);
	}

/*
	while ( !All && x < m_DuplicateFiles.GetCount() )
	{
  All = true;
		int y = 0;
		while (All && y < m_DuplicateFiles.ElementAt(x)->GetSize() )
		{
   if ( ! m_DuplicateFiles.ElementAt(x)->ElementAt(y++)->Selected ) All = false;
		}
  x++;
	}
*/
 return All;
}

UINT CDuplicateFileFind::ExecuteMarkers()
{
 int SelectionIndex;
	CString Msg;
 int MarkerCount = 0;

	// deselect all files
	if ( 1 ) // ((CDuffDlg*)GetParent()->GetParent())->m_OptionsPage.m_DuffOptions.Marker.ClearMarks  )
	{
		DeselectAllFiles();
	}
 //

	for (SelectionIndex = 0; SelectionIndex < m_FileMarkers.GetSize(); SelectionIndex++)
	{
		if ( m_FileMarkers.ElementAt(SelectionIndex)->IsSelected() )
		{
			MarkerCount ++;
		 m_FileMarkers.ElementAt(SelectionIndex)->UpdateData(true);
		}
	}

	// update status and log
 m_DuffStatus.Lock();
 m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_MARKING_STARTED) );
	m_DuffStatus.CurrentTaskStr  = NULL_STR;
 m_DuffStatus.CurrentTaskInfo = NULL_STR;
	m_DuffStatus.SubProgress1.Min = 0;
	m_DuffStatus.SubProgress1.Max = MarkerCount;
 m_DuffStatus.SubProgress1.Pos = 0;
	m_DuffStatus.Unlock();
 //



	// Selection file list
	for (SelectionIndex = 0; SelectionIndex < m_FileMarkers.GetSize(); SelectionIndex++)
	{
		if ( m_FileMarkers.ElementAt(SelectionIndex)->IsSelected() )
		{
			//Msg.Format("Making selection: %s",m_FileMarkers.ElementAt(SelectionIndex)->IsSelected()->GetName() );
   //((CDuffDlg*)GetParent()->GetParent())->Log(Msg);

			// update status and log
			if ( m_DuffStatus.LockIfUnlocked() )
			{
				m_DuffStatus.SubProgress1.Pos = SelectionIndex;
				m_DuffStatus.Unlock();
			}
			//

			m_FileMarkers.ElementAt(SelectionIndex)->MakeSelections( m_DuplicateFiles );

		}
	}
	//

	// update status and log
 m_DuffStatus.Lock();
 m_DuffStatus.LogQueue.Add( StringFromResource(IDS_LOGTEXT_MARKING_FINISHED) );
	m_DuffStatus.CurrentTaskStr  = NULL_STR;
 m_DuffStatus.CurrentTaskInfo = NULL_STR;
	m_DuffStatus.SubProgress1.Min = 0;
	m_DuffStatus.SubProgress1.Max = 0;
 m_DuffStatus.SubProgress1.Pos = 0;
	m_DuffStatus.Unlock();
 //

 // we are finished
	m_DuffStatus.Status = DUFFSTATUS_STOPPED;
 //

 return 0;
}

UINT CDuplicateFileFind::ExecuteProcesses()
{
	int  ProcessIndex;
	UINT Count = 0;
 CFileProcessor * pProcessor;

	for ( ProcessIndex = 0; ProcessIndex < m_FileProcesses.GetSize(); ProcessIndex++ )
	{
	 pProcessor = m_FileProcesses.ElementAt(ProcessIndex);
		if ( pProcessor->IsSelected() )
		{
			pProcessor->UpdateData(true);
			pProcessor->ProcessFiles( m_FileInfos );
			Count++;
		}

	}

 // we are finished
	m_DuffStatus.Status = DUFFSTATUS_STOPPED;
 //

 return Count;
}
