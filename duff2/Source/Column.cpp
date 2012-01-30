// DuplicateListColumn.cpp: implementation of the CDuplicateListColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "Column.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



// init static members

bool CDuplicateListColumn::m_bSortAcending = true;
CDuplicateListColumn * CDuplicateListColumn::m_pSortColumn = NULL;

//

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuplicateListColumn::CDuplicateListColumn()
{
 m_Mode = VM_FIXED;
	m_Visible = false;
	m_PercentWidth = -1;
}

CDuplicateListColumn::~CDuplicateListColumn()
{

}

