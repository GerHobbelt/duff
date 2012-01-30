
#include "stdafx.h"

#include "FileEx.h"


#pragma once

#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O, utilizing memory mapping where available

IMPLEMENT_DYNAMIC(CFileEx, CFile);

// Constructors
CFileEx::CFileEx()
{
}

CFileEx::CFileEx(HANDLE hFile)
	: CFile(hFile)
{
}

CFileEx::CFileEx(LPCTSTR lpszFileName, UINT nOpenFlags)
	: CFile(lpszFileName, nOpenFlags)
{
}

// Attributes
CFileEx::operator HANDLE() const
{
	return CFile::operator HANDLE();
}

ULONGLONG CFileEx::GetPosition() const
{
	return CFile::GetPosition();
}

BOOL CFileEx::GetStatus(CFileStatus& rStatus) const
{
	return CFile::GetStatus(rStatus);
}

CString CFileEx::GetFileName() const
{
	return CFile::GetFileName();
}

CString CFileEx::GetFileTitle() const
{
	return CFile::GetFileTitle();
}

CString CFileEx::GetFilePath() const
{
	return CFile::GetFilePath();
}

void CFileEx::SetFilePath(LPCTSTR lpszNewName)
{
	CFile::SetFilePath(lpszNewName);
}

// Operations
BOOL CFileEx::Open(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError)
{
	return CFile::Open(lpszFileName, nOpenFlags, pError);
}

void PASCAL CFileEx::Rename(LPCTSTR lpszOldName, LPCTSTR lpszNewName)
{
	CFile::Rename(lpszOldName, lpszNewName);
}

void PASCAL CFileEx::Remove(LPCTSTR lpszFileName)
{
	CFile::Remove(lpszFileName);
}

BOOL PASCAL CFileEx::GetStatus(LPCTSTR lpszFileName, CFileStatus& rStatus)
{
	return CFile::GetStatus(lpszFileName, rStatus);
}

void PASCAL CFileEx::SetStatus(LPCTSTR lpszFileName, const CFileStatus& status)
{
	CFile::SetStatus(lpszFileName, status);
}

ULONGLONG CFileEx::SeekToEnd()
{
	return CFile::SeekToEnd();
}

void CFileEx::SeekToBegin()
{
	CFile::SeekToBegin();
}

// Overridables
CFileEx* CFileEx::Duplicate() const
{
	ASSERT_VALID(this);
	AfxThrowNotSupportedException();
}

ULONGLONG CFileEx::Seek(LONGLONG lOff, UINT nFrom)
{
	return CFile::Seek(lOff, nFrom);
}

void CFileEx::SetLength(ULONGLONG dwNewLen)
{
	CFile::SetLength(dwNewLen);
}

ULONGLONG CFileEx::GetLength() const
{
	return CFile::GetLength();
}

UINT CFileEx::Read(void* lpBuf, UINT nCount)
{
	return CFile::Read(lpBuf, nCount);
}

void CFileEx::Write(const void* lpBuf, UINT nCount)
{
	CFile::Write(lpBuf, nCount);
}


void CFileEx::LockRange(ULONGLONG dwPos, ULONGLONG dwCount)
{
	CFile::LockRange(dwPos, dwCount);
}

void CFileEx::UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount)
{
	CFile::UnlockRange(dwPos, dwCount);
}


void CFileEx::Abort()
{
	CFile::Abort();
}

void CFileEx::Flush()
{
	CFile::Flush();
}

void CFileEx::Close()
{
	CFile::Close();
}


// Implementation
CFileEx::~CFileEx()
{
}

#ifdef _DEBUG

void CFileEx::AssertValid() const
{
	CFile::AssertValid();
}

void CFileEx::Dump(CDumpContext& dc) const
{
	CFile::Dump(dc);
}

#endif

/*
And this is the one we override/re-use for memory mapping:

when memory mapping, you don't want to read(), which itself is a copying operation,
but to access the data directly at the source. This member function provides a way to
access that (mapped) source data without any copying.

We do NOT support memory mappings beyond 4GB as the OS won't support such large mappings
anyhow; for very large files you're back to copy-based file I/O.
*/
UINT CFileEx::GetBufferPtr(UINT nCommand, UINT nCount, void** ppBufStart, void** ppBufMax)
{
	return CFile::GetBufferPtr(nCommand, nCount, ppBufStart, ppBufMax);
}



