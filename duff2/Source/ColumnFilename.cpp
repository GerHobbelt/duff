// FilenameColumn.cpp: implementation of the CFilenameColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "ColumnFilename.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilenameColumn::CFilenameColumn()
{
 m_Name = StringFromResource(IDS_COLUMN_FILENAME);
	m_Format = LVCFMT_LEFT;
 m_Mode = VM_FIXED;
	m_Visible = true;
}

CFilenameColumn::~CFilenameColumn()
{

}
