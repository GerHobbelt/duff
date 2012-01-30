// FileSelection.cpp: implementation of the CFileMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "Marker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


bool CFileMarker::m_MarkAtLeastOne = false;
int CFileMarker::m_MarkMode = MARK_MODE_SINGLE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileMarker::CFileMarker()
{
 //m_Selected = false;
	//m_FormID   = 0;
	//m_pForm    = NULL;
}

CFileMarker::~CFileMarker()
{

}
