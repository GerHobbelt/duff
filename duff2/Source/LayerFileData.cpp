// FileDataLayer.cpp: implementation of the CFileDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>

#include "duff.h"
#include "LayerFileData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "DuplicateFileFind.h"
#include "util.h"

using namespace std;


extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileDataLayer::CFileDataLayer()
{
 m_pForm = NULL; 
	m_uiFormID = 0; 
	m_sName = "Binary Data";
	m_sDescription = "In order for files to be considered duplicates, their data must be the same.";

}

CFileDataLayer::~CFileDataLayer()
{

}


CString CFileDataLayer::GetSettingString()
{
/* UpdateData(true);
	switch (m_FileMode)
	{
	case IDC_COMPARISON_MODE_BINARY:
	 return "the files must contain the same binary data";
		break;
	case IDC_COMPARISON_MODE_TEXT:
		return "the files must contain the same text data";
		break;
	default :
		return "No setting!";
	}
*/
	 return "the files must contain the same binary data";
}

//#include <float.h>

bool CFileDataLayer::UpdateData(bool /*SaveAndValidate*/)
{
	//m_FileMode = m_FileDataLayerForm.GetCheckedRadioButton(IDC_COMPARISON_MODE_BINARY,IDC_COMPARISON_MODE_TEXT);
 return true;
}


// compares file data
inline bool CFileDataLayer::FilesEqual(CFileInfo & FileInfo1, CFileInfo & FileInfo2) const
{
	// avoid comparison if files are not same size 
 if ( FileInfo1.Size != FileInfo2.Size )
		return false;

/*
	BYTE equal;

__asm
	{
		mov eax, DWORD PTR [&FileInfo1.Size]
		mov ebx, DWORD PTR [&FileInfo1.Size+4]
		
		cmp eax, ((DWORD*)&FileInfo2.Size)[0]
		jne notequal
		cmp ebx, ((DWORD*)&FileInfo2.Size)[1]
  jne notequal
equal:
		mov equal, 255
		jmp done
notequal:
		mov equal, 0
done:

	}
 if ( equal ) 
		return false;
*/

	// avoid comparison if they are both 0 bytes
	if ( FileInfo1.Size == 0 )
		return true;

 bool ok1 = false;
	bool ok2 = false;
	bool equal(true);
	const int BUFFSIZE = 4096;
	BYTE buffer1[BUFFSIZE];
	BYTE buffer2[BUFFSIZE];
	ifstream ifile1;
	ifstream ifile2;
	ULONGLONG NumRead1;
 ULONGLONG NumRead2;
 ULONGLONG TotalBytesRead = 0;

//	TRACE("Comparing %s : %s...",FileInfo1.Name, FileInfo2.Name);

	// progress bar stuff
	//g_DupeFileFind.GetDuffDlg()->m_ProgressSub2.SetRange64(0,FileInfo1.Length);


	// update status and log
 if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{
  g_DupeFileFind.m_DuffStatus.CurrentTaskInfo.Format( _T("\"%s\", \"%s\"") ,FileInfo1.FullName,FileInfo2.FullName);
  g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Max = 1000; // FileInfo1.GetLength() / ULongLong_IntRatio;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
  g_DupeFileFind.m_DuffStatus.Unlock();
 }
	//
	//TRACE("Wrote status0;");

#ifdef _DEBUG
	if ( FileInfo1.OpenedBefore == true || FileInfo2.OpenedBefore == true )
	{
		TRACE( _T("OPENGING A FILE AGAIN!\n") );
	}

	FileInfo1.OpenedBefore = true;
	FileInfo2.OpenedBefore = true;
#endif


	// attempt to open the files
	ifile1.open(FileInfo1.FullName,  ios::in | ios::binary);
	ifile2.open(FileInfo2.FullName,  ios::in | ios::binary);

 // get result of open attempts
	ok1 = ifile1.is_open() && !ifile1.fail() && !ifile1.bad();
	ok2 = ifile2.is_open() && !ifile2.fail() && !ifile2.bad();

	//TRACE("attempted open;");

 // continue if both opened OK
	if ( ok1 && ok2 )
	{
		// compare file data in loop until eof or it is determined that the files are not equal
  do
		{			
			// attempt to read chunk of data from files
		 ifile1.read((char *)buffer1,BUFFSIZE);
		 ifile2.read((char *)buffer2,BUFFSIZE);
	
			// get sizes of data read from files
			NumRead1 = ifile1.gcount();
			NumRead2 = ifile2.gcount();
   
			// increment total read count
			TotalBytesRead += NumRead1;

			// if read different number of bytes from the files, they are not equal,
			// otherwise, compare the data read
   if (NumRead1 != NumRead2)
				equal = false;
			else
    equal = (memcmp(buffer1,buffer2,NumRead1) == 0);
	
			// progress bar stuff
	 // if ( FileInfo1.Length > 200000 )g_DupeFileFind.GetDuffDlg()->m_ProgressSub2.SetPos64(count);

			// update status and log
		if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
		{
		 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = (int) (1000 *  ulonglongdivide(TotalBytesRead, FileInfo1.Size )  );  //??
		 g_DupeFileFind.m_DuffStatus.Unlock();
		}
		//



//TRACE(".");
		}
		while ( equal && !ifile1.eof()  && !ifile2.eof() );

		// be nice and close the files
		ifile1.close();
		ifile2.close();
	}
	else
	{
		// Could not open 1 or more files, so log the access error(s)

		CString Temp;
		if (!ok1) 
		{
			Temp.Format( _T("ERROR Accessing file: %s") ,FileInfo1.FullName);
			// update status and log
			g_DupeFileFind.m_DuffStatus.Lock();
			g_DupeFileFind.m_DuffStatus.LogQueue.Add(Temp);
			g_DupeFileFind.m_DuffStatus.Unlock();
			//
			
			if ( !GetAccessRetry() )
				FileInfo1.Unaccessible = true;
		}
			
		if (!ok2) 
		{
			Temp.Format( _T("ERROR Accessing file: %s") ,FileInfo2.FullName);
			// update status and log
			g_DupeFileFind.m_DuffStatus.Lock();
			g_DupeFileFind.m_DuffStatus.LogQueue.Add(Temp);
			g_DupeFileFind.m_DuffStatus.Unlock();
			//

			if ( !GetAccessRetry() )
 			FileInfo2.Unaccessible = true;
		}
					
		// could not compare, so assume they are not equal
		equal = false;
	}
	
	// progress bar stuff
	//g_DupeFileFind.GetDuffDlg()->m_ProgressSub2.SetPos(0);

		// update status and log
 g_DupeFileFind.m_DuffStatus.Lock();
 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Max = 0;
 g_DupeFileFind.m_DuffStatus.Unlock();
 //

//	TRACE("Done!\n");

 return equal; 

}