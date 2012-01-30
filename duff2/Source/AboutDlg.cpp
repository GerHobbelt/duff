

#include "stdafx.h"
#include "AboutDlg.h"
#include "VersionInfo.h"

#include "math.h"
#include "util.h"

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_COPYRIGHT, m_Copyright);
	DDX_Control(pDX, IDC_PLUGIN_INFORMATION, m_PluginInformation);
	DDX_Control(pDX, IDC_LICENSE_TYPE, m_LicenseType);
	DDX_Control(pDX, IDC_EMAIL, m_Email);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_COMPILED_DATE, m_CompiledDate);
	DDX_Control(pDX, URL_CHYPERLINK, m_HyperLink);
	DDX_Control(pDX, URL_VERSIONINFO, m_VersionInfo);
	DDX_Control(pDX, URL_SIZELIB, m_SizeLib);
	DDX_Control(pDX, URL_HOMEPAGE, m_HomePage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_ICONLOGO, OnIconlogo)
	ON_NOTIFY(NM_DBLCLK, IDC_PLUGIN_INFORMATION, OnDblclkPluginInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#ifdef  _DEBUG
#define BUILD_TYPE "Debug"
#else
#define BUILD_TYPE "Release"
#endif

#include "duff.h"
extern CDuffApp theApp;

#ifdef _UNICODE
#define _tpgmptr _wpgmptr 
#else
#define _tpgmptr _pgmptr
#endif

#include "util.h"

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

			m_PluginInformation.SetExtendedStyle(  LVS_REPORT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_PluginInformation.InsertColumn(0, _T("Type"),    LVCFMT_LEFT, LVSCW_AUTOSIZE , -1 );
	m_PluginInformation.InsertColumn(1, _T("Name"),    LVCFMT_LEFT, LVSCW_AUTOSIZE , -1 );
	m_PluginInformation.InsertColumn(2, _T("Version"), LVCFMT_LEFT, LVSCW_AUTOSIZE , -1 );
	m_PluginInformation.InsertColumn(3, _T("Author"),  LVCFMT_LEFT, LVSCW_AUTOSIZE , -1 );
	m_PluginInformation.InsertColumn(4, _T("File"),    LVCFMT_LEFT, LVSCW_AUTOSIZE , -1 );

	m_PluginInformation.InsertItem ( 0, _T("Processor") );
	m_PluginInformation.SetItemText( 0, 1, _T("Delete") );
 m_PluginInformation.SetItemText( 0, 2, _T("1.0.0.1") );
 m_PluginInformation.SetItemText( 0, 3, _T("Jeremy B. Smith") );
 m_PluginInformation.SetItemText( 0, 4, _T("delete.dll") );
 

	CString sTemp;
	//sTemp = theApp.m_Timeout.GetTimeOutTime().Format( StringFromResource(IDS_TIME_LIMITED_VERSION) );
	//m_LicenseType.SetWindowText(sTemp);

	m_Email.SetURL( _T("mailto:mr_helamonster@yahoo.com?subject=DUFF") );
 m_Email.ModifyLinkStyle(NULL,CHyperLink::StyleCopyMenu);

	m_HomePage.SetURL( _T("http://utdallas.edu/~jbs024000/") );
	m_HomePage.ModifyLinkStyle(NULL,CHyperLink::StyleCopyMenu);
 
	m_SizeLib.SetURL( _T("http://www.codeproject.com/property/resizableproperties.asp") );
	m_SizeLib.ModifyLinkStyle(NULL,CHyperLink::StyleCopyMenu);
																
 m_VersionInfo.SetURL( _T("http://codeguru.earthweb.com/misc/version_info_from_resource.shtml") );
	m_VersionInfo.ModifyLinkStyle(NULL,CHyperLink::StyleCopyMenu);

	m_HyperLink.SetURL( _T("http://codeguru.earthweb.com/controls/hyperlink.shtml") );
	m_HyperLink.ModifyLinkStyle(NULL,CHyperLink::StyleCopyMenu);

	CString Temp;
	Temp.Format( StringFromResource(IDS_COMPILED_ON) ,__DATE__, __TIME__);
	m_CompiledDate.SetWindowText(Temp);

	CVersionInfo vi;



	vi.GetVersionInfo(_tpgmptr, _T("040904B0"), _T("SpecialBuild") );

	// set version
	Temp.Format( StringFromResource(IDS_VERSION) ,vi.m_strFixedProductVersion,vi.m_strVersionInfo,BUILD_TYPE);
	m_Version.SetWindowText(Temp);
	
	// set copyright
	//Temp.Format( StringFromResource(IDS_VERSION) ,vi.m_strFixedProductVersion,vi.m_strVersionInfo,BUILD_TYPE);
//	m_Copyright.SetWindowText(vi. );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAboutDlg::OnIconlogo() 
{
 SHORT result1 = GetKeyState(VK_RSHIFT);
 SHORT result2 = GetKeyState(VK_LCONTROL);
 result1 >>= 1;
 result2 >>= 1;

	// scroll/caps/num locks ON + left control key + right shift key... kinda tough to do while clicking....
 if ( GetKeyState(VK_NUMLOCK) && GetKeyState(VK_SCROLL) && GetKeyState(VK_CAPITAL) && result1 && result2 )
	{
		

int i = RandomInt(0,5,true);

switch( i )
{
case -1: break;
case 0:

for ( i = 0; i < 100; i++)
{
	Beep( DWORD(sin(4.0f*i) * 10000),100);
}
break;

case 1:

for ( i = 0; i < 100; i++)
{
	Beep( DWORD(cos(2.0f*i) * 500),100);
}
break;
case 2:

for ( i = 0; i < 200; i++)
{
	Beep( DWORD(tan(2.0f*i) * 1000),1);
}
break;
case 3:

// random
RandomInt(100,5000,true);
for ( i = 0; i < 100; i++)
{
	Beep( RandomInt(100,5000,false),50);
}
break; 
case 4:
for ( i = 0; i < 1000; i++)
{
	Beep( DWORD(pow(2.0f,i)),50);

}
break;
case 5:
	 DWORD music[16][2] = 
	{ 
	 {525, 1000}, {784,   500}, {698,   167}, {659,  167},
		{587, 167 }, {1047, 1000}, {784,   500}, {698,  167},
		{659, 167 }, {587,   167}, {1047, 1000}, {784,  500},
	 {698, 167 }, {659,   167}, {698,   167}, {587, 1000}
	};
	for (int i = 0; i <16; i++)
	{
		Beep(music[i][0],music[i][1]);

	}
	break;

	}
	}
		//	if ( m_AnimateControl.Open("clock.avi") )
//	{
//		m_AnimateControl.ShowWindow(SW_SHOW); 
 // m_AnimateControl.Play(0,UINT_MAX,UINT_MAX); 	
	//}
}



void CAboutDlg::OnDblclkPluginInformation(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
 MessageBox(_T("Visit www.whatever.com"));
	*pResult = 0;
}
