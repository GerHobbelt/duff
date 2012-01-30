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
