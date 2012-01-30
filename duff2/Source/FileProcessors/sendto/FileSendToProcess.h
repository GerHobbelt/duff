// FileSendToProcess.h: interface for the CFileSendToProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESENDTOPROCESS_H__E5FDE1C1_E8C9_4209_8412_1261A3229694__INCLUDED_)
#define AFX_FILESENDTOPROCESS_H__E5FDE1C1_E8C9_4209_8412_1261A3229694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Processor.h"
#include "FileSendToProcessForm.h"

class CFileSendToProcess : public CFileProcessor  
{
public:
	CFileSendToProcess();
	virtual ~CFileSendToProcess();

	virtual void ProcessFiles ( CList<CFileInfo *, CFileInfo *> & );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileSendToProcess; }

private:
	CString m_ProgramName;
	CString m_Parameters;
	CFileSendToProcessForm m_FileSendToProcessForm;
	int     m_Option;
};

#endif // !defined(AFX_FILESENDTOPROCESS_H__E5FDE1C1_E8C9_4209_8412_1261A3229694__INCLUDED_)
