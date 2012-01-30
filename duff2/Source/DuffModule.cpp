// DuffModule.cpp: implementation of the CDuffModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffModule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffModule::CDuffModule()
{
 m_bSelected = false;
	m_bComplete = true;
	m_pForm = NULL;
	m_uiFormID = 0;
}

CDuffModule::~CDuffModule()
{

}
