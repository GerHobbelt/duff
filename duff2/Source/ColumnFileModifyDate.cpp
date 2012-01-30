// FileModifyDateColumn.cpp: implementation of the CFileModifyDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileModifyDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileModifyDateColumn::CFileModifyDateColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_DATE_LAST_MODIFIED);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = false;

}

CFileModifyDateColumn::~CFileModifyDateColumn()
{

}
