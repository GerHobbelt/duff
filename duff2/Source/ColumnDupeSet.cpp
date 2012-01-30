// DupeSetColumn.cpp: implementation of the CDupeSetColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnDupeSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDupeSetColumn::CDupeSetColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_SET);
	m_Format = LVCFMT_RIGHT;
 m_Mode = VM_FIXED;
	m_Visible = true;

}

CDupeSetColumn::~CDupeSetColumn()
{

}
