// FileAccessDateColumn.cpp: implementation of the CFileAccessDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileAccessDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileAccessDateColumn::CFileAccessDateColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_DATE_LAST_ACCESSED);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = false;

}

CFileAccessDateColumn::~CFileAccessDateColumn()
{

}
