// MP3FileDataLayer.cpp: implementation of the CMP3FileDataLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "duff.h"
#include "LayerMP3FileData.h"
#include "FileEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ULONGLONG_MAX 18446744073709551615
#include "DuplicateFileFind.h"
#include "util.h"

using namespace std;


extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMP3FileDataLayer::CMP3FileDataLayer()
{
 m_pForm = &m_FileMP3DataLayerForm;
	m_uiFormID = IDD_FILE_MP3DATA_LAYER_FORM;
	m_sName = "MP3 File Data";
	m_sDescription = "Does a binary compare on MP3 files, ignoring the MPEG header and ID3v1 and/or ID3v2 tags, if present\r\nIgnores non-MP3 files";
 m_MaxFileSizeDifference = 4096;
}

CMP3FileDataLayer::~CMP3FileDataLayer()
{

}



bool CMP3FileDataLayer::UpdateData(bool /*SaveAndValidate*/)
{

	m_MaxFileSizeDifference = m_FileMP3DataLayerForm.m_Slider.GetPos() * 1024;

	if (m_MaxFileSizeDifference >= 1025024) m_MaxFileSizeDifference = -1;

	 return true;
}




// compares file data
bool CMP3FileDataLayer::FilesEqual(CFileInfo & FileInfo1, CFileInfo & FileInfo2) const
{
	// constant data
	static const BYTE Mp3HeaderLength = 0x00000004;
	static const BYTE NullBytes[128]  = { 0x000000FF };
	static const int  BUFFSIZE        = 0x00001000;
	static const WORD HeaderSyncMask  = 0x0000F0FF;

	// general data
 int          i = 0;
	bool         FilesStillEqual = true;
	bool         HeaderFound = false;
 ULONGLONG    TotalBytesRead = 0;
	CString      sTemp;

	// file-specific data
 bool         FileGood1 = false;
	bool         FileGood2 = false;
	BYTE         buffer1[BUFFSIZE] = { 0x0 };
	BYTE         buffer2[BUFFSIZE] = { 0x0 };
	CFileEx     Mp3File1;
	CFileEx     Mp3File2;
	CFileException file_ex;
	UINT    NumBytesRead1 = 0;
	UINT    NumBytesRead2 = 0;
	ULONGLONG    DataStartPos1 = 0;
 ULONGLONG    DataStartPos2 = 0;
 ULONGLONG    MaxDataPos1 = 0;
 ULONGLONG    MaxDataPos2 = 0;
	ULONGLONG    Mp3DataLength1 = 0;
	ULONGLONG    Mp3DataLength2 = 0;




	// avoid comparison if file sizes are very different
	if (
		    (m_MaxFileSizeDifference > 0) &&
			   (
						 (FileInfo1.Size > FileInfo2.Size) &&  (FileInfo1.Size - FileInfo2.Size >= m_MaxFileSizeDifference) ||
						 (FileInfo2.Size > FileInfo1.Size) &&  (FileInfo2.Size - FileInfo1.Size >= m_MaxFileSizeDifference)
					 )
				)
					return false;

	// avoid comparison if they are both 0 bytes
	if ( FileInfo1.Size == 0 && FileInfo2.Size == 0)
		return true;
 //


	// update status and progress
 if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{
  g_DupeFileFind.m_DuffStatus.CurrentTaskInfo.Format( _T("\"%s\", \"%s\"") ,FileInfo1.FullName,FileInfo2.FullName);
  g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Max = 1000; // FileInfo1.GetLength() / ULongLong_IntRatio;
  g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
  g_DupeFileFind.m_DuffStatus.Unlock();
 }
	//

	// attempt to open the files
	FileGood1 = Mp3File1.Open( FileInfo1.FullName ,  CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary | CFile::osSequentialScan);
	FileGood2 = Mp3File2.Open( FileInfo2.FullName ,  CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary | CFile::osSequentialScan);
 //


 // continue if both opened OK
	if ( FileGood1 && FileGood2 )
	{

		// read until MPEG header is found or EOF
		HeaderFound = false;
		TotalBytesRead = 0;
		do
		{
			NumBytesRead1 = Mp3File1.Read(buffer1,BUFFSIZE);
			i=0;
			while(i + 1 < NumBytesRead1 && !HeaderFound)
			{
				HeaderFound = (((*(WORD*)(buffer1+i)) & HeaderSyncMask) == HeaderSyncMask);
				i++;
			}
			if (HeaderFound)
			{
				DataStartPos1 = TotalBytesRead + i - 1;
			}
			else
			{
				Mp3File1.Seek(-1,CFile::current);
				TotalBytesRead += NumBytesRead1-1;
			}
		}
		while (!HeaderFound && NumBytesRead1);
  //

  // if the header was not found, the file is not an mp3, so we can't do comparison
  if (!HeaderFound)
			return false;
		//

  // read until MPEG header is found or EOF
		HeaderFound = false;
		TotalBytesRead = 0;
		do
		{
			NumBytesRead2 = Mp3File2.Read(buffer2,BUFFSIZE);
			i=0;
			while(i + 1 < NumBytesRead2 && !HeaderFound)
			{
				HeaderFound = (((*(WORD*)(buffer2+i)) & HeaderSyncMask) == HeaderSyncMask);
				i++;
			}
			if (HeaderFound)
			{
				DataStartPos2 = TotalBytesRead + i - 1;
			}
			else
			{
				Mp3File2.Seek(-1,CFile::current);
				TotalBytesRead+= NumBytesRead2 - 1;   // BUGFIX!
			}
		}
		while (!HeaderFound && NumBytesRead2);
  //

  // if the header was not found, the file is not an mp3, so we can't do comparison
  if (!HeaderFound)
			return false;
		//

		// get the max mp3 data position in the file
  if ( FileInfo1.Size >=128)
		{
			Mp3File1.Seek(FileInfo1.Size-128, CFile::begin);
			Mp3File1.Read(buffer1,128);
			if( memcmp(buffer1,"TAG",3) == 0 || memcmp(buffer1,NullBytes,128) == 0)
			{
				MaxDataPos1 = FileInfo1.Size - 128;
			}
			else
			{
				MaxDataPos1 = FileInfo1.Size;
			}
		}
		else
		{
			MaxDataPos1 = FileInfo1.Size;
		}
		//

	 /*
		// ignore all 0xFF bytes at end of mp3 data
		buffer1[0] = 0x00;
		do
		{
		 Mp3File1.seekg(MaxDataPos1);
			Mp3File1.read(buffer1,1);
		 NumBytesRead1 = Mp3File1.gcount();
			if ( buffer1[0] == 0xFF ) MaxDataPos1--;
		}
		while ( buffer1[0] == 0xFF && NumBytesRead1 == 1);
  //
  */

		// get the max mp3 data position in the file
		if ( FileInfo2.Size >=128)
		{
			Mp3File2.Seek(FileInfo2.Size-128, CFile::begin);
			Mp3File2.Read(buffer2,128);
			if( memcmp(buffer2,"TAG",3) == 0 || memcmp(buffer2,NullBytes,128) == 0)
			{
				MaxDataPos2 = FileInfo2.Size - 128;
			}
			else
			{
				MaxDataPos2 = FileInfo2.Size;
			}
		}
		else
		{
			MaxDataPos2 = FileInfo2.Size;
		}
  //

		/*
		// ignore all 0xFF bytes at end of mp3 data
		buffer2[0] = 0x00;
		do
		{
		 Mp3File2.seekg(MaxDataPos2);
			Mp3File2.read(buffer2,1);
		 NumBytesRead2 = Mp3File2.gcount();
			if ( buffer2[0] == 0xFF ) MaxDataPos2--;
		}
		while ( buffer2[0] == 0xFF && NumBytesRead2 == 1);
  //
  */

		// modify data start positions so that the MP3 headers are NOT compared
		DataStartPos1 += Mp3HeaderLength;
		DataStartPos2 += Mp3HeaderLength;
		//

  // calculate the total MPEG data chunk lengths
		Mp3DataLength1 = MaxDataPos1 - DataStartPos1;
		Mp3DataLength2 = MaxDataPos2 - DataStartPos2;
  //

		// if mp3 data chunks are different size, the files can not be duplicate, so exit
		if ( Mp3DataLength1 != Mp3DataLength2 )
		{
			TRACE2("File1 and File2 Data chunk sizes are different (%d vs %d)!\n",(UINT)Mp3DataLength1,(UINT)Mp3DataLength2);
			return false;
		}
		//

		// seek to beginning positions
		Mp3File1.Seek(DataStartPos1, CFile::begin);
		Mp3File2.Seek(DataStartPos2, CFile::begin);
		//

		// compare file data in loop until eof or it is determined that the files are not FilesStillEqual
		do
		{
			NumBytesRead1 = Mp3File1.Read(buffer1,BUFFSIZE);
			NumBytesRead2 = Mp3File2.Read(buffer2,BUFFSIZE);

		   // adjust NumBytesRead1 and NumBytesRead2 if id3v1 tags (at end of file) were read
			if ( (TotalBytesRead + DataStartPos1 + NumBytesRead1) > MaxDataPos1 )
			{
				NumBytesRead1 = MaxDataPos1 - (TotalBytesRead + DataStartPos1);
			}
			if ( (TotalBytesRead + DataStartPos2 + NumBytesRead2) > MaxDataPos2 )
			{
				NumBytesRead2 = MaxDataPos2 - (TotalBytesRead + DataStartPos2);
			}
			//

 			// increment total bytes read counter
			TotalBytesRead += NumBytesRead1;
			//

			// if we read different number of bytes from the files, they are not FilesStillEqual,
			// otherwise, compare the data read
			FilesStillEqual = (NumBytesRead1 == NumBytesRead2) ? (memcmp(buffer1,buffer2,NumBytesRead1) == 0) : false;
   //

			// update progress
			if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
			{
				g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = (int) (1000 *  ulonglongdivide(TotalBytesRead, Mp3DataLength1 )  );
				g_DupeFileFind.m_DuffStatus.Unlock();
			}
			//

		}
		while ( FilesStillEqual &&  (TotalBytesRead < Mp3DataLength1) && (Mp3File1.GetPosition() < MaxDataPos1) && (Mp3File2.GetPosition() < MaxDataPos2) );

		// be nice and close the files
		Mp3File1.Close();
		Mp3File2.Close();
		//

	}
	else
	{
		// Could not open the file, so log the access error
		if (!FileGood1)
		{
			sTemp.Format( _T("ERROR Accessing file: %s") ,FileInfo1.FullName);

			// update log
			g_DupeFileFind.m_DuffStatus.Lock();
			g_DupeFileFind.m_DuffStatus.LogQueue.Add(sTemp);
			g_DupeFileFind.m_DuffStatus.Unlock();
			//

			// mark the file as unaccessible so we don't try to read it again
			if ( !GetAccessRetry() )
				FileInfo1.Unaccessible = true;
			//
		}
	 //

		// Could not open the file, so log the access error
		if (!FileGood2)
		{
			sTemp.Format( _T("ERROR Accessing file: %s") ,FileInfo2.FullName);

			// update log
			g_DupeFileFind.m_DuffStatus.Lock();
			g_DupeFileFind.m_DuffStatus.LogQueue.Add(sTemp);
			g_DupeFileFind.m_DuffStatus.Unlock();
			//

			// mark the file as unaccessible so we don't try to read it again
			if ( !GetAccessRetry() )
 			FileInfo2.Unaccessible = true;
			//
		}
		//

		// could not compare, so assume they are not equal
		FilesStillEqual = false;
		//
	}

	// update status, log and progress
 g_DupeFileFind.m_DuffStatus.Lock();
 g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = 0;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Max = 0;
 g_DupeFileFind.m_DuffStatus.Unlock();
 //

 // return a simple yes or no answer
	return FilesStillEqual;
	//
}