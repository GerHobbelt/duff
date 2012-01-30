
#pragma once

#include <limits.h>

/////////////////////////////////////////////////////////////////////////////
// CProgressCtrl64

class CProgressCtrl64 : public CProgressCtrl 
{
	DECLARE_DYNAMIC(CProgressCtrl64)

protected:
	LONGLONG m_min, m_max;
	double m_mult;

// Constructors
public:
	CProgressCtrl64()
	{
		m_mult = 1;
		m_min = m_max = 0;
	}

// Attributes

	// Sets range of values for the control. (16-bit limit)
	void SetRange(_In_ short nLower, _In_ short nUpper)
	{
		m_mult = 1.0;
		m_min = nLower;
		m_max = nUpper;
		CProgressCtrl::SetRange(nLower, nUpper);
	}

	// Sets range of values for the control. (32-bit limit)
	void SetRange32(_In_ int nLower, _In_ int nUpper)
	{
		m_mult = 1.0;
		m_min = nLower;
		m_max = nUpper;
		CProgressCtrl::SetRange32(nLower, nUpper);
	}

	// Sets range of values for the control. (64-bit limit)
	void SetRange64(_In_ LONGLONG nLower, _In_ LONGLONG nUpper)
	{
		m_mult = (double)SHRT_MAX / (double)(nUpper - nLower);
		m_min = nLower;
		m_max = nUpper;
		CProgressCtrl::SetRange32(int(nLower * m_mult), int(nUpper * m_mult));
	}

	// Retrieves range of values for the control. (32-bit limit)
	void GetRange(_Out_ int& nLower, _Out_ int& nUpper) const
	{
		nLower = int(m_min * m_mult);
		nUpper = int(m_max * m_mult);
	}

	// Retrieves range of values for the control. (64-bit limit)
	void GetRange64(_Out_ LONGLONG& nLower, _Out_ LONGLONG& nUpper) const
	{
		nLower = m_min;
		nUpper = m_max;
	}

	// Gets the current position within the set range of the control.
	int GetPos() const
	{
		int pos = CProgressCtrl::GetPos();
		return pos;
	}

	// Gets the current position within the set range of the control.
	LONGLONG GetPos64() const
	{
		int pos = CProgressCtrl::GetPos();
		return LONGLONG(pos / m_mult);
	}

	// Sets the current position within the set range of the control.
	int SetPos(_In_ int nPos)
	{
		int pos = CProgressCtrl::SetPos(nPos);
		return pos;
	}

	// Sets the current position within the set range of the control.
	LONGLONG SetPos64(_In_ LONGLONG nPos)
	{
		int pos = CProgressCtrl::SetPos(int(nPos * m_mult));
		return LONGLONG(pos / m_mult);
	}

	// Displaces the current position within the set range of the
	// control by the passed value.
	int OffsetPos(_In_ int nPos)
	{
		int pos = CProgressCtrl::SetPos(nPos);
		return pos;
	}

	// Displaces the current position within the set range of the
	// control by the passed value.
	LONGLONG OffsetPos64(_In_ LONGLONG nPos)
	{
		int pos = CProgressCtrl::SetPos(int(nPos * m_mult));
		return LONGLONG(pos / m_mult);
	}

// Implementation
public:
	virtual ~CProgressCtrl64()
	{
	}
};
