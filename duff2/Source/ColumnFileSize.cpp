// FileSizeColumn.cpp: implementation of the CFileSizeColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileSize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileSizeColumn::CFileSizeColumn()
{
 m_Name    = StringFromResource(IDS_COLUMN_FILE_SIZE);
	m_Format  = LVCFMT_RIGHT;
 m_Mode    = VM_FIXED;
	m_Visible = true;

}

CFileSizeColumn::~CFileSizeColumn()
{

}
