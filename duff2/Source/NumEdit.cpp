// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "NumEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// CNumEdit

CNumEdit::CNumEdit()
{
 m_SelStart = 0;
 m_SelEnd = 0;
}

CNumEdit::~CNumEdit()
{
}


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	//{{AFX_MSG_MAP(CNumEdit)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumEdit message handlers

void CNumEdit::OnUpdate() 
{
	CString Temp;

	GetWindowText(Temp);
	if ( !isinteger(Temp) )
	{
		SetWindowText(m_OldText);
		SetSel(m_SelStart,m_SelEnd);
	}
	else
	{
		m_OldText = Temp;
	}

}

void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	GetSel(m_SelStart,m_SelEnd);
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
