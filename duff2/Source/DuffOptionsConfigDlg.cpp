// DuffOptionsConfigDlg.cpp: implementation of the CDuffOptionsConfigDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "DuffOptionsConfigDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


extern CDuffApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuffOptionsConfigDlg::CDuffOptionsConfigDlg()
{
 m_pDuffOptions = &theApp.m_DuffOptions;
}

CDuffOptionsConfigDlg::~CDuffOptionsConfigDlg()
{

}

