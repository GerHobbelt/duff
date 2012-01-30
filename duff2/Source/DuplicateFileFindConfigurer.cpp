// DuplicateFileFindConfigurer.cpp: implementation of the CDuplicateFileFindConfigurer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuplicateFileFindConfigurer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CArray<CDuplicateFileFindConfigurer *,CDuplicateFileFindConfigurer *> CDuplicateFileFindConfigurer::m_List;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuplicateFileFindConfigurer::CDuplicateFileFindConfigurer()
{
 m_List.Add(this);
}

CDuplicateFileFindConfigurer::~CDuplicateFileFindConfigurer()
{

}
