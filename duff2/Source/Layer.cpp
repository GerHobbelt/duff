// FileComparisonLayer.cpp: implementation of the CFileComparisonLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "Layer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



 CFileComparisonLayer::CFileComparisonLayer()
{
//	m_ObjectArray.Add(this); 
}

	bool CFileComparisonLayer::m_bAccessRetry = false;
//CArray< CFileComparisonLayer*, CFileComparisonLayer* > CFileComparisonLayer::m_ObjectArray;
