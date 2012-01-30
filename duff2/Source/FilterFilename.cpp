// FilenameFilter.cpp: implementation of the CFilenameFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "FilterFilename.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilenameFilter::CFilenameFilter()
{

}

CFilenameFilter::~CFilenameFilter()
{

}


int CFilenameFilter::FilterDuplicateList(  CList<CFileInfo*,CFileInfo*> &  /*FileList*/ )
{
	//	remove any files that don't match the include filter and files to do match the exclude filter
 //m_FilenameLayerForm.m_ExcludeFilters
	//m_FilenameLayerForm.m_IncludeFilters
 return 0;
}
