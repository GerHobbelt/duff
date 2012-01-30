// DuffPluginType.cpp: implementation of the CDuffPluginType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffPluginType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CArray<CDuffPluginType*,CDuffPluginType*> CDuffPluginType::m_AllTypes;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffPluginType::CDuffPluginType()
{
 m_AllTypes.Add(this);
}

CDuffPluginType::~CDuffPluginType()
{

}
