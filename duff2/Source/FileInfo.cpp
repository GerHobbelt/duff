// FileInfo.cpp: implementation of the CFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "FileInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CFileInfo, CObject);


#ifdef _DEBUG
UINT CFileInfo::Count = 0;
#endif

	//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFileInfo::~CFileInfo()
{
	#ifdef _DEBUG
	Count--;
	#endif
}




#if defined(_DEBUG) || defined(_AFXDLL)

// Diagnostic Support
void CFileInfo::AssertValid() const
{
	CObject::AssertValid();
}

void CFileInfo::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif

