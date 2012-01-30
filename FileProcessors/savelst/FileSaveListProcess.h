// FileSaveListProcess.h: interface for the CFileSaveListProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESAVELISTPROCESS_H__C0745174_B7E1_4BA3_BBDA_17A3909D3466__INCLUDED_)
#define AFX_FILESAVELISTPROCESS_H__C0745174_B7E1_4BA3_BBDA_17A3909D3466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\FileProcessor.h"
#include "FileSaveListProcessForm.h"

class CFileSaveListProcess : public CFileProcessor  
{
public:
	CFileSaveListProcess();
	virtual ~CFileSaveListProcess();

	virtual void ProcessFiles ( CList<CFileInfo *, CFileInfo *> & );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileSaveListProcess; }

private:
	CString m_Filename;
	CString m_LineFormat;
	bool    m_AllFiles;
	bool    m_NewLine;
	CFileSaveListProcessForm m_FileSaveListProcessForm;
};

#endif // !defined(AFX_FILESAVELISTPROCESS_H__C0745174_B7E1_4BA3_BBDA_17A3909D3466__INCLUDED_)
