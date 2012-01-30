// FileTypeDescColumn.cpp: implementation of the CFileTypeDescColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileTypeDesc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileTypeDescColumn::CFileTypeDescColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_TYPE);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = false;

}

CFileTypeDescColumn::~CFileTypeDescColumn()
{

}
