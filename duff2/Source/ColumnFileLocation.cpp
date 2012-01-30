// FileLocationColumn.cpp: implementation of the CFileLocationColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFileLocation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileLocationColumn::CFileLocationColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_LOCATION);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = true;

}

CFileLocationColumn::~CFileLocationColumn()
{

}

