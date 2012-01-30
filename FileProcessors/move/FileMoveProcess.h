// FileMoveProcess.h: interface for the CFileMoveProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMOVEPROCESS_H__9DE6C6E9_5354_489F_BAA2_40B324EB431E__INCLUDED_)
#define AFX_FILEMOVEPROCESS_H__9DE6C6E9_5354_489F_BAA2_40B324EB431E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\FileProcessor.h"
#include "FileMoveProcessForm.h"

class CFileMoveProcess : public CFileProcessor  
{
public:
	CFileMoveProcess();
	virtual ~CFileMoveProcess();

	virtual void ProcessFiles ( CList<CFileInfo *, CFileInfo *> & );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileMoveProcess; }

private:
	CFileMoveProcessForm m_FileMoveProcessForm;
	bool    m_MoveReadOnly;
	bool    m_YesToAll;
	CString m_Dir;
};

#endif // !defined(AFX_FILEMOVEPROCESS_H__9DE6C6E9_5354_489F_BAA2_40B324EB431E__INCLUDED_)
