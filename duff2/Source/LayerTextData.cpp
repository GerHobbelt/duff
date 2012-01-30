// FileTextDataLayer.cpp: implementation of the CFileTextDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "duff.h"
#include "LayerTextData.h"
#include "FileEx.h"

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

CFileTextDataLayer::CFileTextDataLayer()
{
 m_pForm = &m_FileTextDataLayerForm;
	m_uiFormID = IDD_FILE_TEXT_DATA_LAYER_FORM;
	m_sName = "Text Data";
	m_sDescription = "Textual data must be equal. Compares ANSI with Unicode and optionally ignores case.";
 m_bComplete = false;
}

CFileTextDataLayer::~CFileTextDataLayer()
{

}


bool CFileTextDataLayer::UpdateData(bool /*SaveAndValidate*/)
{
	return true;
}


// compares file data
bool CFileTextDataLayer::FilesEqual(CFileInfo & FileInfo1, CFileInfo & FileInfo2) const
{

	// avoid comparison if they are both 0 bytes
	if ( FileInfo1.Size == 0 && FileInfo2.Size == 0)
		return true;

 bool ok1 = false;
	bool ok2 = false;
	bool equal(true);
	const int BUFFSIZE = 4096;
	BYTE buffer1[BUFFSIZE];
	BYTE buffer2[BUFFSIZE];
	CFileEx ifile1;
	CFileEx ifile2;
	UINT NumRead1;
	UINT NumRead2;
 ULONGLONG TotalBytesRead = 0;

	TRACE2("Comparing %s : %s...",FileInfo1.GetName(), FileInfo2.GetName());

	// progress bar stuff
	//g_DupeFileFind.GetDuffDlg()->m_ProgressSub2.SetRange64(0,FileInfo1.Length);


	// update status and log
 if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{
  g_DupeFileFind.m_DuffStatus.CurrentTaskInfo.Format( _T("\"%s\", \"%s\"") ,FileInfo1.GetFullName(),FileInfo2.GetFullName());
  g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Max = 1000; // FileInfo1.GetLength() / ULongLong_IntRatio;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
  g_DupeFileFind.m_DuffStatus.Unlock();
 }
	//
	TRACE0("Wrote status0;");


	// attempt to open the files
	ok1 = ifile1.Open(FileInfo1.GetFullName(),  CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary | CFile::osSequentialScan);
	ok2 = ifile2.Open(FileInfo2.GetFullName(),  CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary | CFile::osSequentialScan);

	TRACE0("attempted open;");

 // continue if both opened OK
	if ( ok1 && ok2 )
	{
		// compare file data in loop until eof or it is determined that the files are not equal
		  do
		{
			// attempt to header from files
			NumRead1 = ifile1.Read((char *)buffer1,BUFFSIZE);
			NumRead2 = ifile2.Read((char *)buffer2,BUFFSIZE);
			//

			// increment total read count
			TotalBytesRead += NumRead1;

#if 0
			int FileType1;
			int FileType2;

			// determine text file types
			FileType1 = CharEncSchemes::GetType(buffer1);
			if (FileType1 == -1) FileType1 = 0;
			FileType2 = CharEncSchemes::GetType(buffer1);
			if (FileType2 == -1) FileType2 = 0;
			//

			// seek to beginning of text
			ifile1.Seek( CharEncSchemes[FileType1].HeaderLength , CFile::begin);
			ifile2.Seek( CharEncSchemes[FileType2].HeaderLength , CFile::begin);
   //

			// reset total read count for progress display
			TotalBytesRead += CharEncSchemes[FileType1].HeaderLength;

			// Get biggest character size
			MaxCharSize = max( CharEncSchemes[FileType1].CharacterLength, CharEncSchemes[FileType2].CharacterLength );
			//

			// attempt to read chunk of data from files
			NumRead1 = ifile1.Read(buffer1,BUFFSIZE / CharEncSchemes[FileType1].CharacterLength);
			NumRead2 = ifile2.Read(buffer2,BUFFSIZE / CharEncSchemes[FileType2].CharacterLength);
	  //

			// increment total read count
			TotalBytesRead += NumRead1;

			// if the amount of data read from the files implies that the data cannot be the same, they are not equal
			// otherwise, compare the data
			if ( NumRead1 / CharEncSchemes[FileType1].CharacterLength != NumRead2 / CharEncSchemes[FileType2].CharacterLength )
			{
				equal = false;
			}
			else
			{
				// get length of smallest buffer
				SmallestRead = min(NumRead1,NumRead2);
				//

				int CharVal1 = 0;
				int CharVal2 = 0;
    BYTE *pPos1;
    BYTE *pPos2;

				int i = 0;
				while ( i < SmallestRead && equal)
				{
     pPos1 = buffer1 + ( i * CharEncSchemes[FileType1].GCharacterLength );
     pPos2 = buffer2 + ( i * CharEncSchemes[FileType2].CharacterLength );

					memcpy((BYTE*)&CharVal1, pPos1, CharEncSchemes[FileType1].CharacterLength );
					CharVal1 >>= sizeof(int) - CharEncSchemes[FileType1].CharacterLength;

					memcpy((BYTE*)&CharVal2, pPos2, CharEncSchemes[FileType2].CharacterLength );
					CharVal2 >>= sizeof(int) - CharEncSchemes[FileType2].CharacterLength;

					// convert both characters to little endian
					// not sure best way to do this
					//

					// the files are still equal only if the current characters are equal
					equal = ( CharVal1 == CharVal2 );
					//

     i++;
				}

			}
			//

#else
			break;
#endif

			// update status and log
			if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
			{
			 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = (int) (1000 *  ulonglongdivide(TotalBytesRead, FileInfo1.Size )  );  //??
			 g_DupeFileFind.m_DuffStatus.Unlock();
			}
		}
		while ( equal && NumRead1 && NumRead2);

		// be nice and close the files
		ifile1.Close();
		ifile2.Close();
	}
	else
	{
		// Could not open 1 or more files, so log the access error(s)

		CString Temp;
		if (!ok1)
		{
			Temp.Format( _T("ERROR Accessing file: %s") ,FileInfo1.GetFullName());
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
			Temp.Format( _T("ERROR Accessing file: %s") ,FileInfo2.GetFullName());
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

	TRACE0("Done!\n");

 return equal;
}


int CFileTextDataLayer::DetermineFileType(CFileInfo & )
{
 return -1;
}

