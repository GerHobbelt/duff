// DuffPluginTypeProcessor.h: interface for the CDuffPluginTypeProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUFFPLUGINTYPEPROCESSOR_H__B537184D_70F1_4D34_AEF8_2BFBB3AD60B5__INCLUDED_)
#define AFX_DUFFPLUGINTYPEPROCESSOR_H__B537184D_70F1_4D34_AEF8_2BFBB3AD60B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DuffPluginType.h"

class CDuffPluginTypeProcessor : public CDuffPluginType  
{
public:
	CDuffPluginTypeProcessor();
	virtual ~CDuffPluginTypeProcessor();
 virtual HINSTANCE LoadPlugin(const CString &);

};

#endif // !defined(AFX_DUFFPLUGINTYPEPROCESSOR_H__B537184D_70F1_4D34_AEF8_2BFBB3AD60B5__INCLUDED_)
