// DuffObject.cpp: implementation of the CDuffObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <afxtempl.h>

CArray< CDuffObject *, CDuffObject * > g_DuffObjects;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffObject::CDuffObject()
{
	g_DuffObjects.Add(this);
}

CDuffObject::~CDuffObject()
{
}
