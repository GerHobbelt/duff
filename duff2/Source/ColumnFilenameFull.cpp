// FullFilenameColumn.cpp: implementation of the CFullFilenameColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFilenameFull.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFullFilenameColumn::CFullFilenameColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_FULL_FILENAME);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = false;

}

CFullFilenameColumn::~CFullFilenameColumn()
{

}
