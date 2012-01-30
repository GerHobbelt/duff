// FileAttributesColumn.cpp: implementation of the CFileAttributesColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileAttributes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileAttributesColumn::CFileAttributesColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_ATTRIBUTES);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = false;

}

CFileAttributesColumn::~CFileAttributesColumn()
{

}
