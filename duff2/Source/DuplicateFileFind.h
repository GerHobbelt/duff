// DuplicateFileFind.h: interface for the CDuplicateFileFind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUPLICATEFILEFIND_H__4FDCEC5D_B0E7_47D5_89A4_8B98291E1A5D__INCLUDED_)
#define AFX_DUPLICATEFILEFIND_H__4FDCEC5D_B0E7_47D5_89A4_8B98291E1A5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// misc
#include <afxmt.h>
#include <afxtempl.h>
#include <windows.h>
#include "FileInfo.h"
#include "DirectoryInfo.h"
#include "DuffStatus.h"

// file comparison layers
#include "LayerFilename.h"
#include "LayerFileData.h"
#include "LayerMP3FileData.h"
#include "LayerTextData.h"

// file processors (now in plugins)
#include "Processor.h"

// file markers
#include "MarkerFilename.h"
#include "MarkerFileDate.h"
#include "MarkerFileLocation.h"
#include "MarkerFileSize.h"
#include "MarkerFileVersion.h"

// file filters
#include "FilterFileAttributes.h"
#include "FilterFileContents.h"
#include "FilterFileDate.h"
#include "FilterFileSize.h"


#define THREAD_CHECK_FOR_PAUSE if( m_DuffStatus.Status == DUFFSTATUS_PAUSED ) \
 while ( ::WaitForSingleObject(m_DuffStatus.Event, 1000) == WAIT_TIMEOUT);

#define LOGIC_AND 0
#define LOGIC_OR  1

class CDuplicateFileFind  
{

 // public methods
public:
	             CDuplicateFileFind();
	virtual      ~CDuplicateFileFind();
	int          StartSearh();
	int          StopSearch();
	int          PauseSearch();
	int          ResumeSearch();
	void         AddSearchPath(const CString & DirectoryName, const bool SearchSubDirectories );

	const CArray<CFileFilter *, CFileFilter *> * GetFileFilterArray() const;
	const CArray<CFileComparisonLayer *, CFileComparisonLayer * > * GetFileComparisonLayerArray() const;
	const CArray<CFileProcessor *, CFileProcessor * > * GetFileProcessArray() const;
	const CArray<CFileMarker *, CFileMarker * > * GetFileSelectionArray() const;

	void IncludeHiddenDirs(int);
	void IncludeSystemDirs(int);
	void IncludeReadOnlyDirs(int);
	void IncludeCompressedDirs(int);
	void IncludeArchivedDirs(int);
	void IncludeEncryptedDirs(int);


	void DeselectAllFiles();
	void RemoveAllSearchPaths();
	UINT MakeSelections(UINT SelectionIndex);

	void AddFileMask(const CString &);
	void RemoveAllFileMasks();

	bool SelectFilter(UINT, bool);
	bool SelectFileComparisonLayer(UINT, bool);

	bool SetLayerLogic(int);
	int  GetLayerLogic() const;
	
	bool AddFileComparisonLayer( CFileComparisonLayer * );
	bool RemoveAllFileComparisonLayers();

	bool AddFileFilter( CFileFilter * );
	bool RemoveAllFileFilters();

	bool AddFileSelector( CFileMarker * );
	bool RemoveAllFileSelectors();

	bool AddFileProcessor( CFileProcessor * );
	bool RemoveAllFileProcessors();

	bool CheckForFullSetMarks();

	UINT ExecuteProcesses();
	UINT ExecuteMarkers();

	void CleanUp();

	// public data
public:
	
	sDuffStatus m_DuffStatus;

 // private methods
private:

	UINT GetNumDuplicates();
	UINT BuildDuplicateList();
	void AddSubDirsToList(CList<CDirectoryInfo,CDirectoryInfo &> & Directories, const CDirectoryInfo & Dir);

	unsigned int BuildFileList();

// private data
private: 

	int                         m_LayerLogic;
	int                         m_IncludeHiddenDirs;
	int                         m_IncludeSystemDirs;
	int                         m_IncludeReadOnlyDirs;
	int                         m_IncludeCompressedDirs;
	int                         m_IncludeArchivedDirs;
	int                         m_IncludeEncryptedDirs;

	bool m_bProgressPositive;
	CList< CList<CFileInfo *,CFileInfo *> *, CList<CFileInfo *,CFileInfo *> * > m_DuplicateFiles;
	CList<CFileInfo *,CFileInfo *> m_FileInfos;
	CString                     m_IncludeFilter;
	CString                     m_ExcludeFilter;
	CArray<CDirectoryInfo, CDirectoryInfo&> m_UserIncludeDirectories;
	CArray<CDirectoryInfo, CDirectoryInfo&> m_IncludeDirectories;

	CArray<CString, CString&> m_FileMasks;

	// file filters
	CFileAttributesFilter m_FileAttributesFilter;
	CFileSizeFilter       m_FileSizeFilter;
	CFileDateFilter       m_FileSateFilter;
	CFileContentsFilter   m_FileContentsFilter;
	CArray<CFileFilter *, CFileFilter *> m_FileFilters;
	//

	// Filename comparison layers
	CFilenameLayer     m_FilenameLayer;
	CFileDataLayer     m_FileDataLayer;
	CFileTextDataLayer m_FileTextDataLayer;
	CMP3FileDataLayer  m_MP3FileDataLayer;
	CArray<CFileComparisonLayer *, CFileComparisonLayer * > m_FileComparisonLayers;
	//

	// file selections
	CFilenameMarker m_FilenameMarker;
	CFileDateMarker m_FileDateMarker;
	CFileLocationMarker m_FileLocationMarker;
	CFileSizeMarker m_FileSizeMarker;
	CFileVersionMarker m_FileVersionMarker;
	CArray < CFileMarker *, CFileMarker * > m_FileMarkers;
	//

	// File processes
	//	CFileDeleteProcess   m_FileDeleteProcess;
	//CFileMoveProcess     m_FileMoveProcess;
	//	CFileSaveListProcess m_FileSaveListProcess;
	//	CFileNullProcess     m_FileNullProcess;
	CArray<CFileProcessor *, CFileProcessor * > m_FileProcesses;
	//

};

// inline methods

inline bool CDuplicateFileFind::AddFileComparisonLayer( CFileComparisonLayer * pFCL)
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
		m_FileComparisonLayers.Add( pFCL );
	 return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::RemoveAllFileComparisonLayers()
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileComparisonLayers.RemoveAll();
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::AddFileFilter( CFileFilter * pFF)
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileFilters.Add( pFF );
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::RemoveAllFileFilters()
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileFilters.RemoveAll();
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::AddFileSelector( CFileMarker * pFS)
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileMarkers.Add( pFS );
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::RemoveAllFileSelectors()
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileMarkers.RemoveAll();
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::AddFileProcessor( CFileProcessor * pFP)
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileProcesses.Add(pFP);
		return true;
	}
	else
	{
		return false;
	}
}

inline bool CDuplicateFileFind::RemoveAllFileProcessors()
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
 	m_FileProcesses.RemoveAll();
		return true;
	}
	else
	{
		return false;
	}
}

inline	bool CDuplicateFileFind::SetLayerLogic(int L)
{
	if ( m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
		switch (L)
		{
		case LOGIC_OR:
		case LOGIC_AND:
			m_LayerLogic = L;
			return true;
			break;
		default:
			m_LayerLogic = LOGIC_OR;
			return false;
			break;
		}
	}
 else
	{
		return false;
	}
}

inline	int CDuplicateFileFind::GetLayerLogic() const
{
	return m_LayerLogic;
}

inline bool CDuplicateFileFind::SelectFileComparisonLayer(UINT index, bool selected)
{
 if (index < (UINT)m_FileComparisonLayers.GetSize() )
	{
		m_FileComparisonLayers.ElementAt(index)->SetSelected(selected);
		return true;
	}
	return false;
}

inline bool CDuplicateFileFind::SelectFilter(UINT index, bool selected)
{
 if (index < (UINT)m_FileFilters.GetSize() )
	{
		m_FileFilters.ElementAt(index)->SetSelected(selected);
		return true;
	}
	return false;
}

inline void CDuplicateFileFind::RemoveAllFileMasks()
{
	m_FileMasks.RemoveAll();
}

inline void CDuplicateFileFind::AddFileMask(const CString & str)
{
	m_FileMasks.Add((CString&)str);
}

inline	void CDuplicateFileFind::IncludeHiddenDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeHiddenDirs = opt;
		 break;
  default:
		 m_IncludeHiddenDirs = BST_INDETERMINATE;
			break;
	}
}

inline	void CDuplicateFileFind::IncludeSystemDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeSystemDirs = opt;
		 break;
  default:
		 m_IncludeSystemDirs = BST_INDETERMINATE;
			break;
	}
}

inline	void CDuplicateFileFind::IncludeReadOnlyDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeReadOnlyDirs = opt;
		 break;
  default:
		 m_IncludeReadOnlyDirs = BST_INDETERMINATE;
			break;
	}
}

inline	void CDuplicateFileFind::IncludeCompressedDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeCompressedDirs = opt;
		 break;
  default:
		 m_IncludeCompressedDirs = BST_INDETERMINATE;
			break;
	}
}

inline	void CDuplicateFileFind::IncludeArchivedDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeArchivedDirs = opt;
		 break;
  default:
		 m_IncludeArchivedDirs = BST_INDETERMINATE;
			break;
	}
}

inline	void CDuplicateFileFind::IncludeEncryptedDirs(int opt)
{
	switch(opt)
	{
	 case BST_CHECKED:
  case BST_UNCHECKED:
	 case BST_INDETERMINATE:
		 m_IncludeEncryptedDirs = opt;
		 break;
  default:
		 m_IncludeEncryptedDirs = BST_INDETERMINATE;
			break;
	}
}


inline	const CArray<CFileFilter *, CFileFilter *> * CDuplicateFileFind::GetFileFilterArray() const
{
	return &m_FileFilters;
}

inline  const CArray<CFileComparisonLayer *, CFileComparisonLayer * > * CDuplicateFileFind::GetFileComparisonLayerArray() const
{
	return &m_FileComparisonLayers;
}

inline const CArray<CFileProcessor *, CFileProcessor * > * CDuplicateFileFind::GetFileProcessArray() const
{
	return &m_FileProcesses;
}

inline  const CArray<CFileMarker *, CFileMarker * > * CDuplicateFileFind::GetFileSelectionArray() const
{
	return &m_FileMarkers;
}

inline void CDuplicateFileFind::DeselectAllFiles()
{
 POSITION Pos;

	Pos = m_FileInfos.GetHeadPosition();
	while (Pos)
	{
  m_FileInfos.GetAt(Pos)->Selected = false;
		m_FileInfos.GetNext(Pos);
	}
/*
	for (int i = 0; i < m_FileInfos.GetCount(); i++)
	{
		m_FileInfos.ElementAt(i)->Selected = false;
	}
	*/
}

inline UINT CDuplicateFileFind::MakeSelections(UINT SelectionIndex)
{
	m_FileMarkers.ElementAt(SelectionIndex)->UpdateData(true);
	return m_FileMarkers.ElementAt(SelectionIndex)->MakeSelections( m_DuplicateFiles );
}

inline void CDuplicateFileFind::AddSearchPath(const CString & DirectoryName, const bool SearchSubDirs )
{
 CDirectoryInfo D(DirectoryName, SearchSubDirs);
 m_UserIncludeDirectories.Add(D);
}

inline void CDuplicateFileFind::RemoveAllSearchPaths()
{
	m_UserIncludeDirectories.RemoveAll();
	m_IncludeDirectories.RemoveAll();
}

#endif // !defined(AFX_DUPLICATEFILEFIND_H__4FDCEC5D_B0E7_47D5_89A4_8B98291E1A5D__INCLUDED_)
