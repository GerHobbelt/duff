// FileDeleteProcess.h: interface for the CFileDeleteProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDELETEPROCESS_H__5A987D73_3784_4E3D_96CA_FA186300129B__INCLUDED_)
#define AFX_FILEDELETEPROCESS_H__5A987D73_3784_4E3D_96CA_FA186300129B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Processor.h"
#include "FileDeleteProcessForm.h"

class CFileDeleteProcess : public CFileProcessor  
{
public:
	CFileDeleteProcess();
	virtual ~CFileDeleteProcess();

	virtual void ProcessFiles ( CList<CFileInfo *, CFileInfo *> & );
 virtual bool UpdateData(bool SaveAndValidate);
	virtual CDuffModule * GetNew() { return new CFileDeleteProcess; }


private:
	bool m_Recycle;
	bool m_DeleteReadOnly;
	bool m_YesToAll;
	CFileDeleteProcessForm m_FileDeleteProcessForm;
};

#endif // !defined(AFX_FILEDELETEPROCESS_H__5A987D73_3784_4E3D_96CA_FA186300129B__INCLUDED_)
