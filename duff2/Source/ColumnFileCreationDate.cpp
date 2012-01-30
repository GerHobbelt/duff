// FileCreationDateColumn.cpp: implementation of the CFileCreationDateColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileCreationDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCreationDateColumn::CFileCreationDateColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_DATE_CREATED);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = true;

}

CFileCreationDateColumn::~CFileCreationDateColumn()
{

}
