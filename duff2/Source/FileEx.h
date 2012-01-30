
#pragma once

#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O, utilizing memory mapping where available

class CFileEx : protected CFile
{
	DECLARE_DYNAMIC(CFileEx)

public:

// Constructors
	CFileEx();
	CFileEx(HANDLE hFile);
	CFileEx(LPCTSTR lpszFileName, UINT nOpenFlags);

// Attributes
public:
	// HANDLE m_hFile;   -- made invisible from outside by 'protected' parent class
	operator HANDLE() const;

	ULONGLONG GetPosition() const;
	BOOL GetStatus(CFileStatus& rStatus) const;
	CString GetFileName() const;
	CString GetFileTitle() const;
	CString GetFilePath() const;
	void SetFilePath(LPCTSTR lpszNewName);

// Operations
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL);

	static void PASCAL Rename(LPCTSTR lpszOldName, LPCTSTR lpszNewName);
	static void PASCAL Remove(LPCTSTR lpszFileName);
	static BOOL PASCAL GetStatus(LPCTSTR lpszFileName, CFileStatus& rStatus);
	static void PASCAL SetStatus(LPCTSTR lpszFileName, const CFileStatus& status);

	virtual ULONGLONG SeekToEnd();
	virtual void SeekToBegin();

// Overridables
	virtual CFileEx* Duplicate() const;

	virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);
	virtual void SetLength(ULONGLONG dwNewLen);
	virtual ULONGLONG GetLength() const;

	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);

	virtual void LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
	virtual void UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);

	virtual void Abort();
	virtual void Flush();
	virtual void Close();

// Implementation
public:
	virtual ~CFileEx();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	/*
	And this is the one we override/re-use for memory mapping:

	when memory mapping, you don't want to read(), which itself is a copying operation,
	but to access the data directly at the source. This member function provides a way to
	access that (mapped) source data without any copying.
	*/
	UINT GetBufferPtr(UINT nCommand, UINT nCount = 0, void** ppBufStart = NULL, void** ppBufMax = NULL);

protected:
};

