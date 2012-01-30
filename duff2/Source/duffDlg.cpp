// duffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "DuplicateFileFind.h"
#include "duffDlg.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <afx.h>
#include "AboutDlg.h"
#include "LayerFilenameForm.h"
#include "util.h"

#define ALL 0,UINT_MAX,UINT_MAX
#define TIMER_PROGRESS 1

//extern int g_FileComparisonLayersCount;
//extern CFileComparisonLayer g_FileComparisonLayers[];
extern CDuplicateFileFind g_DupeFileFind;
extern CDuffApp theApp;
extern CArray< CDuffObject *, CDuffObject * > g_DuffObjects;


/////////////////////////////////////////////////////////////////////////////
// CDuffDlg dialog

/*CDuffDlg::CDuffDlg()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	running = false;
	paused = false;
}*/


//CDuffDlg * pDuffDlg;

CDuffDlg::CDuffDlg(CWnd* pParent /*=NULL*/)
: CResizableDialog(CDuffDlg::IDD, pParent)

{
	//{{AFX_DATA_INIT(CDuffDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	running = false;
//	paused = false;
// pDuffDlg = this;
	m_pWorkerThread = NULL;
}

void CDuffDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDuffDlg)
	DDX_Control(pDX, IDC_RANGE_ENTIRE, m_RangeEntire);
	DDX_Control(pDX, IDC_SUBRANGE2, m_SubRange2);
	DDX_Control(pDX, IDC_SUBRANGE1, m_SubRange1);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_PROPERTYSHEET, m_PropertySheetFrame);
	DDX_Control(pDX, IDC_PROGRESS_SUB_2, m_ProgressSub2);
	DDX_Control(pDX, IDC_PROGRESS_SUB_1, m_ProgressSub1);
	DDX_Control(pDX, IDC_PAUSE, m_PauseCheckBox);
	DDX_Control(pDX, IDC_ANIMATE_CONTROL, m_AnimateControl);
	DDX_Control(pDX, IDC_STOP, m_StopButton);
	DDX_Control(pDX, IDC_TASK_INFO, m_CurrentTaskInfoText);
	DDX_Control(pDX, IDC_PROGRESS_ENTIRE, m_ProgressEntire);
	DDX_Control(pDX, IDC_CURRENT_TASK, m_CurrentTaskText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDuffDlg, CResizableDialog)
	//{{AFX_MSG_MAP(CDuffDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(IDM_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDM_FILE_EXIT, OnFileExit)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_COMMAND(IDM_SEARCH_PAUSE, OnSearchPause)
	ON_COMMAND(IDM_SEARCH_START, OnSearchStart)
	ON_COMMAND(IDM_SEARCH_STOP, OnSearchStop)
	ON_COMMAND(IDM_VIEW_DIECTORIES, OnViewDiectories)
	ON_COMMAND(IDM_VIEW_DUPLICATES, OnViewDuplicates)
	ON_COMMAND(IDM_VIEW_LAYERS, OnViewLayers)
	ON_COMMAND(IDM_VIEW_LOG, OnViewLog)
	ON_COMMAND(IDM_VIEW_PROCESSES, OnViewProcesses)
	ON_COMMAND(IDM_VIEW_SELECTIONS, OnViewSelections)
	ON_COMMAND(IDM_FILE_SAVELOG, OnFileSavelog)
	ON_COMMAND(ID_FILE_CLEAR_RESULTS, OnFileClearResults)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_WM_SIZE()
	ON_COMMAND(IDM_VIEW_OPTIONS, OnViewOptions)
	ON_WM_DESTROY()
	ON_COMMAND(IDM_VIEW_FILE_FILTERS, OnViewFileFilters)
	ON_WM_TIMER()
	ON_COMMAND(IDM_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(IDM_FILE_SAVE_GLOBAL, OnFileSaveGlobal)
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_FILE_EXPORT_CSV, OnFileExportCsv)
	ON_COMMAND(IDM_FILE_EXPORT_DUPLIC8, OnFileExportDuplic8)
	ON_COMMAND(IDM_FILE_EXPORT_FND, OnFileExportFnd)
	ON_COMMAND(IDM_FILE_IMPORT_DUPLIC8, OnFileImportDuplic8)
	ON_COMMAND(IDM_FILE_IMPORT_FND, OnFileImportFnd)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDuffDlg message handlers

BOOL CDuffDlg::OnInitDialog()
{
CResizableDialog::OnInitDialog();


	// Add "About..." menu item to system menu.
	/*
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
*/
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

 m_CurrentTaskText.SetWindowText( StringFromResource(IDS_STATUS_IDLE)  );



 m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));
 if (!m_hAccel)
	{
		AfxMessageBox(IDS_MSGBOX_ACCELERATOR_LOAD_ERROR_TEXT, MB_OK | MB_ICONEXCLAMATION);
	}

//HWND phWnd;
//GetDlgItem(IDC_PROPERTYSHEET,&phWnd);

//m_PropertySheet.Attach(phWnd);
 m_PropertySheet.EnableStackedTabs(FALSE);
	m_PropertySheet.AddPage(&m_LayerPage);
 m_PropertySheet.AddPage(&m_DirectoryPage);
	m_PropertySheet.AddPage(&m_FileFilterPage);
 m_PropertySheet.AddPage(&m_DuplicatePage);
 m_PropertySheet.AddPage(&m_SelectionPage);
 m_PropertySheet.AddPage(&m_ProcessPage);
 m_PropertySheet.AddPage(&m_StatusLogPage);
 m_PropertySheet.AddPage(&m_OptionsPage);
#ifdef _DEBUG
 m_PropertySheet.AddPage(&m_DebugPage);
#endif


		m_PropertySheet.Create(this, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE, 0);

	m_PropertySheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_PropertySheet.ModifyStyle( 0, WS_TABSTOP );

 // property sheet fix
 m_PropertySheet.SetActivePage(0);
 m_PropertySheet.SetActivePage(1);
 m_PropertySheet.SetActivePage(2);
	m_PropertySheet.SetActivePage(3);
	m_PropertySheet.SetActivePage(4);
 m_PropertySheet.SetActivePage(5);
 m_PropertySheet.SetActivePage(6);
 m_PropertySheet.SetActivePage(7);
#ifdef _DEBUG
 m_PropertySheet.SetActivePage(8);
#endif
 m_PropertySheet.SetActivePage(0);
	//

m_TabImageList.Create( IDB_TABIMAGES, 13, 1, RGB(255,0,255) );
m_PropertySheet.GetTabControl()->SetImageList(&m_TabImageList);

TC_ITEM tcItem;
	tcItem.mask = TCIF_IMAGE;
	for( int i = 0; i < 8; i++ )
	{
		tcItem.iImage = i;
		m_PropertySheet.GetTabControl()->SetItem( i, &tcItem );
	}


 // preset resize layout
	AddAnchor(IDC_EXIT, BOTTOM_RIGHT);
	AddAnchor(IDC_START, BOTTOM_RIGHT);
	AddAnchor(IDC_STOP, BOTTOM_RIGHT);
	AddAnchor(IDC_PAUSE, BOTTOM_RIGHT);
	AddAnchor(IDC_ANIMATE_CONTROL, BOTTOM_RIGHT);
	AddAnchor(IDC_STATUS, BOTTOM_RIGHT);
	AddAnchor(IDC_STATIC_CURRENT_TASK, BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_TASK_INFO, BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_SUBPREGRESS1, BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_SUBPROGRESS2, BOTTOM_LEFT);
	AddAnchor(IDC_STATIC_PROGRESS_ENTIRE, BOTTOM_LEFT);
	AddAnchor(IDC_PROPERTYSHEET, TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_TASK_INFO,  BOTTOM_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_CURRENT_TASK,  BOTTOM_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESS_ENTIRE, BOTTOM_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESS_SUB_2, BOTTOM_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESS_SUB_1, BOTTOM_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_SUBRANGE2, BOTTOM_RIGHT);
	AddAnchor(IDC_SUBRANGE1, BOTTOM_RIGHT);
	AddAnchor(IDC_RANGE_ENTIRE, BOTTOM_RIGHT);
 //



//
//this->ShowSizeGrip(FALSE);

 m_PropertySheet.Resize();

//	CRect rcSheet;
	//GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
	//ScreenToClient( &rcSheet );
//	m_PropertySheet.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );

// g_DupeFileFind.SetDuffDlg(this);

 // load plugins
	Log( StringFromResource(IDS_LOADING_PLUGINS) );
	LoadPlugins();
	Log( StringFromResource(IDS_FINISHED_LOADING_PLUGINS) );
	//

	m_bAnimateControl = m_AnimateControl.Open(StringFromResource(IDS_ANIMATION_FILENAME)) != 0;
	Log( StringFromResource(m_bAnimateControl ? IDS_ANIMATE_CONTROL_LOADED : IDS_ANIMATE_CONTROL_NOT_LOADED) );


	// not in use
	/*
	for (i = 0; i < g_DuffObjects.GetSize(); i++)
	{
		g_DuffObjects.ElementAt(i)->LoadSettings();
	}
 */



	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDuffDlg::Log(const CString desc/*, CString p1, CString p2*/)
{
 CString TimeStr;
	COleDateTime t;
	t = t.GetCurrentTime();
	TimeStr = t.Format(StringFromResource(IDS_LOG_DATETIME_FORMAT));

	m_StatusLogPage.m_StatusLog.InsertItem(m_StatusLogPage.m_StatusLog.GetItemCount(),TimeStr);
 m_StatusLogPage.m_StatusLog.SetItemText(m_StatusLogPage.m_StatusLog.GetItemCount()-1,1,desc);
//	m_StatusLogPage.m_StatusLog.SetItemText(m_StatusLogPage.m_StatusLog.GetItemCount()-1,2,p1);
//	m_StatusLogPage.m_StatusLog.SetItemText(m_StatusLogPage.m_StatusLog.GetItemCount()-1,3,p2);
}




void CDuffDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
  Help();
	}
	else
	{
		CResizableDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDuffDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CResizableDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDuffDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDuffDlg::OnHelpAbout()
{
	Help();
}



void CDuffDlg::OnFileSave()
{
SaveSettings();
}

void CDuffDlg::OnOK()
{
}

void CDuffDlg::OnCancel()
{
	if ( g_DupeFileFind.m_DuffStatus.Status != DUFFSTATUS_RUNNING || ( (g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_RUNNING) && Confirm()) )
	{
		g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_STOPPED;
	 Exit();
	}
	// TODO: Add extra cleanup here

	//CResizableDialog::OnCancel();
}

/*
void CDuffDlg::OnClearLog()
{
//m_StatusLog.DeleteAllItems();
}
*/
void CDuffDlg::OnFileExit()
{
 Exit();
}

void CDuffDlg::Exit()
{
	if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_STOPPED || ( (g_DupeFileFind.m_DuffStatus.Status != DUFFSTATUS_STOPPED) && Confirm()) )
	{
  g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_STOPPED;
 	CResizableDialog::OnOK();
	}
}



void CDuffDlg::OnExit()
{
 Exit();
}

bool CDuffDlg::Confirm()
{
 return MessageBox(StringFromResource(IDS_MSGBOX_ARE_YOU_SURE_TEXT),StringFromResource(IDS_MSGBOX_ARE_YOU_SURE_TITLE),MB_YESNO | MB_ICONINFORMATION) == IDYES;
}


void CDuffDlg::OnStop()
{
 Stop();
}




void CDuffDlg::Help()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CDuffDlg::OnSearchPause()
{
 Pause();
}

void CDuffDlg::OnSearchStart()
{
 Start();
}

void CDuffDlg::OnSearchStop()
{
 Stop();
}

void CDuffDlg::OnViewLayers()
{
 m_PropertySheet.SetActivePage(&m_LayerPage);
}
void CDuffDlg::OnViewDiectories()
{
 m_PropertySheet.SetActivePage(&m_DirectoryPage);
}
void CDuffDlg::OnViewFileFilters()
{
 m_PropertySheet.SetActivePage(&m_FileFilterPage);
}

void CDuffDlg::OnViewDuplicates()
{
 m_PropertySheet.SetActivePage(&m_DuplicatePage);
}

void CDuffDlg::OnViewSelections()
{
 m_PropertySheet.SetActivePage(&m_SelectionPage);
}

void CDuffDlg::OnViewProcesses()
{
 m_PropertySheet.SetActivePage(&m_ProcessPage);
}

void CDuffDlg::OnViewLog()
{
 m_PropertySheet.SetActivePage(&m_StatusLogPage);
}

void CDuffDlg::OnViewOptions()
{
 m_PropertySheet.SetActivePage(&m_OptionsPage);
}



BOOL CDuffDlg::PreTranslateMessage(MSG* pMsg)
{
	bool ret;
	if ( IsDialogMessage( pMsg ) )
	{
		if ( TranslateAccelerator ( GetSafeHwnd(),m_hAccel,pMsg) )
  {
   TranslateMessage(pMsg);
   DispatchMessage(pMsg);
   ret = false;
		}
		ret = true;
	}
	else
	{
		ret = ( CWnd::PreTranslateMessage( pMsg ) != 0);
	}
	return ret;
}

bool CDuffDlg::SaveLog()
{
	CFileDialog Dlg(FALSE,StringFromResource(IDS_SAVELOG_DLG_TITLE),StringFromResource(IDS_DUFF_LOG_DEFAULT_FILENAME),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,StringFromResource(IDS_SAVELOG_FILENAME_FILTER),this);
 CString Temp;
 if ( Dlg.DoModal() == IDOK)
	{
		CString Temp;
		CFile f;
		if ( f.Open(Dlg.GetFileName(), CFile::modeCreate |CFile::modeWrite /*| CFile::typeText   | CFile::shareExclusive   */) )
		{
			for (int i= 0; i < m_StatusLogPage.m_StatusLog.GetItemCount(); i++)
			{
				CString Temp;
				Temp.Format(StringFromResource(IDS_SAVELOG_FILE_FORMAT),m_StatusLogPage.m_StatusLog.GetItemText(i,0),m_StatusLogPage.m_StatusLog.GetItemText(i,1) );
			 f.Write(Temp,Temp.GetLength());
			}
 	f.Close();
 	Temp.Format(StringFromResource(IDS_SAVELOG_FINISHED),Dlg.GetFileName());
		Log(Temp);
		}
		else
		{
 	 Temp.Format(StringFromResource(IDS_SAVELOG_ERROR),Dlg.GetFileName());
		 Log(Temp);
		}

		return true;
	}

 Log(StringFromResource(IDS_SAVELOG_CANCELLED));


 return false;
}

void CDuffDlg::OnFileSavelog()
{
	SaveLog();
}

void CDuffDlg::OnFileClearResults()
{
	ClearResults();
}

bool CDuffDlg::ClearResults()
{
	if ( Confirm() )
	{
		g_DupeFileFind.CleanUp();
		m_DuplicatePage.m_DupeList.DeleteAllItems();
		return true;
	}
	return false;
}





// static member function
UINT CDuffDlg::myThread(LPVOID me)
{
 CDuffDlg * self = (CDuffDlg *)me;
 self->Search();

 return 0;
}


int CDuffDlg::Search()
{

	m_Status.SetWindowText( StringFromResource(IDS_STATUS_BUSY) );
	if (m_bAnimateControl)
	{
		m_AnimateControl.ShowWindow(SW_SHOW);
		m_AnimateControl.Play(ALL);
	}
	g_DupeFileFind.StartSearch();

	if (m_bAnimateControl)
	{
	 m_AnimateControl.Stop();
	}

	m_Status.SetWindowText( StringFromResource(IDS_STATUS_IDLE) );


	OnTimer(TIMER_PROGRESS);
	KillTimer(TIMER_PROGRESS);

	if ( theApp.m_DuffOptions.Sound.Enabled )
		PlaySoundFile( theApp.m_DuffOptions.Sound.ProcessComplete );

 return 0;
}


void CDuffDlg::OnStart()
{
Start();
}

void CDuffDlg::OnPause()
{
Pause();
}


/////////////////////////////

void CDuffDlg::Start()
{

	if ( g_DupeFileFind.m_DuffStatus.Status != DUFFSTATUS_STOPPED )
		return;
/*
	CString Msg, Temp, TempStr;
	UINT LayerCount = 0;
 int i;

	Msg += "DUFF will create a list of directories consisting of the following:\n";
	for ( i = 0; i < m_DirectoryPage.m_IncludeDirectoriesList.GetCount();i++)
	{
		m_DirectoryPage.m_IncludeDirectoriesList.GetText(i,Temp);
		Msg += Temp;
		if ( m_DirectoryPage.m_IncludeDirectoriesList.GetCheck(i) ) Msg += " (and all subdirectories)";
		Msg += "\n";
	}

	Msg += "Then, DUFF will create a list of files found in those directories.\n";
	Msg += "Only files that match the file mask(s): '";
	m_DirectoryPage.m_FileMasks.GetWindowText(Temp);
	Msg += Temp;
	Msg += "' will be added to the list.\n";


	Temp = "";
	for ( i = 0; i < m_FileFilterPage.m_FilterCheckList.GetCount(); i++ )
	{
		if ( m_FileFilterPage.m_FilterCheckList.GetCheck(i) == BST_CHECKED )
		{
			if (i && Temp.GetLength() ) Temp += " and ";
   Temp += g_DupeFileFind.GetFileFilterArray()->GetAt( m_FileFilterPage.m_FilterCheckList.GetItemData(i) )->GetSettingString();
		}
	}
	if ( Temp.GetLength() )
	{
		Msg += "Then, DUFF will filter the file list, removing all files except those that ";
		Msg += Temp;
		Msg += ".\n";
	}

	Temp =  "DUFF will then compare all of these files with each other and create a list of files that have duplicates.\n";
	Temp += "In order for files to be considered 'duplicates,' ";

	for ( i = 0; i < m_LayerPage.m_LayerCheckList.GetCount(); i++)
	{
		if ( m_LayerPage.m_LayerCheckList.GetCheck(i) == BST_CHECKED )
		{
			if ( i && Temp.GetLength() ) Temp += " and ";
			Temp += g_DupeFileFind.GetFileComparisonLayerArray()->GetAt( m_LayerPage.m_LayerCheckList.GetItemData(i) )->GetSettingString();
			LayerCount++;
		}
	}
	if ( LayerCount )
	{
		Msg += Temp;
		Msg += ".\n";
	}
	else
	{
		Msg += "Absolutely nothing at all.\n";
	}

	Msg += "As DUFF finds files that have duplicates, it will add them to the list under the 'Duplicates' tab.\n";
	if ( m_OptionsPage.m_DuffOptions.Sound.Enabled )
	{
		Msg += "DUFF will play the WAV sound file: '";
	 Msg += m_OptionsPage.m_DuffOptions.Sound.FoundDuplicate;
		Msg += "' whenever it finds a new duplicate file.\n";
	 Msg += "When this process is complete, DUFF will play the WAV file: '";
		Msg += m_OptionsPage.m_DuffOptions.Sound.ProcessComplete;
		Msg += "'.\n";
	}


	Temp.Format("Throughout this process, DUFF will process a total of %d File Comparison Layers.",LayerCount);
 Msg += Temp;
	Msg += "\n\nAre you absolutely sure you want to do this?";


	if ( MessageBox(Msg,"What DUFF is about to do",MB_YESNO | MB_ICONINFORMATION) == IDNO )
		return;
*/

 int Cancelled;
	CString Msg;
 // init layers settings
	Cancelled =  m_LayerPage.InitDupeFileFind(g_DupeFileFind);
	if ( Cancelled != -1)
	{
		Msg.Format( StringFromResource(IDS_BAD_FCL_INPUT) , g_DupeFileFind.GetFileComparisonLayerArray()->GetAt(Cancelled)->GetName() );
		Log(Msg);
		return;
	}
	//

	// init directories settings
 Cancelled = m_DirectoryPage.InitDupeFileFind(g_DupeFileFind);
	if ( Cancelled != -1)
	{
		Msg.Format( StringFromResource(IDS_BAD_DIRECTORY_INPUT) );
		Log(Msg);
		return;
	}
 //

	// init filter settings
	Cancelled = m_FileFilterPage.InitDupeFileFind(g_DupeFileFind);
	if ( Cancelled != -1)
	{
		Msg.Format( StringFromResource(IDS_BAD_FILTER_INPUT), g_DupeFileFind.GetFileFilterArray()->GetAt(Cancelled)->GetName() );
		Log(Msg);
		return;
	}
	//

	// init marker settings
	Cancelled = m_SelectionPage.InitDupeFileFind(g_DupeFileFind);
	if ( Cancelled != -1)
	{
		Msg.Format( StringFromResource(IDS_BAD_MARKER_INPUT) , _T("TEMP") /*g_DupeFileFind.GetFileMarkerArray()->GetAt(Cancelled)->GetName()*/ );
		Log(Msg);
		return;
	}
	//

	// init processor settings
	Cancelled = m_ProcessPage.InitDupeFileFind(g_DupeFileFind);
	if ( Cancelled != -1)
	{
		Msg.Format( StringFromResource(IDS_BAD_PROCESSOR_INPUT), _T("TEMP")/* g_DupeFileFind.GetFileProcessorArray()->GetAt(Cancelled)->GetName()*/ );
		Log(Msg);
		return;
	}
	//

	// init other options
	m_OptionsPage.InitDupeFileFind(g_DupeFileFind);
	//
	int Priority;// = THREAD_PRIORITY_NORMAL;
 SetTimer(TIMER_PROGRESS, theApp.m_DuffOptions.General.UpdateInterval  ,NULL);

	switch( theApp.m_DuffOptions.General.ThreadPriority )
	{
	case 0:
  Priority = THREAD_PRIORITY_TIME_CRITICAL;
		break;
	case 1:
  Priority = THREAD_PRIORITY_HIGHEST;
		break;
	case 2:
  Priority = THREAD_PRIORITY_ABOVE_NORMAL;
		break;
	case 3:
  Priority = THREAD_PRIORITY_NORMAL;
		break;
	case 4:
  Priority = THREAD_PRIORITY_BELOW_NORMAL;
		break;
	case 5:
  Priority = THREAD_PRIORITY_LOWEST;
		break;
	case 6:
  Priority = THREAD_PRIORITY_IDLE;
		break;
default:
  Priority = THREAD_PRIORITY_NORMAL;
		break;
	}

	//m_DirectoryPage.EnableWindow(FALSE);

	m_pWorkerThread = AfxBeginThread(myThread, this,Priority);

}

void CDuffDlg::Stop()
{
	if ( (g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_RUNNING) && Confirm() )
	{
  g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_STOPPED;

		m_PauseCheckBox.SetCheck( BST_UNCHECKED );
		m_Status.SetWindowText( StringFromResource(IDS_STATUS_IDLE) );
	 m_AnimateControl.Stop();
  KillTimer(TIMER_PROGRESS);
 	Log( StringFromResource(IDS_LOGTEXT_SEARCH_STOPPED) );
	}

}

void CDuffDlg::Pause()
{
 if ( g_DupeFileFind.m_DuffStatus.Status != DUFFSTATUS_STOPPED )
	{
		if ( m_PauseCheckBox.GetCheck() == BST_CHECKED )
			g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_PAUSED;
		else
			g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_RUNNING;

	 if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_PAUSED )
		{
			KillTimer(TIMER_PROGRESS);
			Log( StringFromResource(IDS_STATUS_PAUSED) );
			m_AnimateControl.Stop() ;
	 	m_Status.SetWindowText( StringFromResource(IDS_STATUS_PAUSED) );
		 g_DupeFileFind.m_DuffStatus.Event.ResetEvent();
		}
		else
		{
			SetTimer(TIMER_PROGRESS, theApp.m_DuffOptions.General.UpdateInterval ,NULL);
			Log(StringFromResource(IDS_STATUS_UNPAUSED));
   m_AnimateControl.Play(ALL);
		 m_Status.SetWindowText( StringFromResource(IDS_STATUS_BUSY));
   g_DupeFileFind.m_DuffStatus.Event.SetEvent();
		}
	}
	else
	{
  m_PauseCheckBox.SetCheck( BST_UNCHECKED );
	}

}

/////////////////////////////


void CDuffDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType, cx, cy);
 if (nType != SIZE_MINIMIZED && m_PropertySheet )
	{
		m_PropertySheet.Resize();
	}
}


void CDuffDlg::OnDestroy()
{
	/*
	for (int i = 0; i < g_DuffObjects.GetSize(); i++)
	{
		g_DuffObjects.ElementAt(i)->SaveSettings();
	}*/


	// wait until worker thread has exited
	g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_STOPPED;
 if (m_pWorkerThread)
	{
		::WaitForSingleObject(m_pWorkerThread,INFINITE);
	}

	CResizableDialog::OnDestroy();

}


void CDuffDlg::OnTimer(UINT /*nIDEvent*/)
{
	int i;
	CString Temp;
	CFileInfo * pFileInfo;
	int PercentDone;

	if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{

		m_CurrentTaskText.SetWindowText(g_DupeFileFind.m_DuffStatus.CurrentTaskStr );
		m_CurrentTaskInfoText.SetWindowText(g_DupeFileFind.m_DuffStatus.CurrentTaskInfo );
		m_ProgressEntire.SetRange64( g_DupeFileFind.m_DuffStatus.MainProgress.Min, g_DupeFileFind.m_DuffStatus.MainProgress.Max );
		m_ProgressEntire.SetPos64( g_DupeFileFind.m_DuffStatus.MainProgress.Pos );
		PercentDone = 0;
		if ( g_DupeFileFind.m_DuffStatus.MainProgress.Max )
		PercentDone = (int) ( 100 * (double)g_DupeFileFind.m_DuffStatus.MainProgress.Pos/ (double)g_DupeFileFind.m_DuffStatus.MainProgress.Max);
		Temp.Format( _T("%03d %%") ,PercentDone);
		m_RangeEntire.SetWindowText(Temp);

		m_ProgressSub1.SetRange64( g_DupeFileFind.m_DuffStatus.SubProgress1.Min, g_DupeFileFind.m_DuffStatus.SubProgress1.Max );
		m_ProgressSub1.SetPos64( g_DupeFileFind.m_DuffStatus.SubProgress1.Pos );

		PercentDone = 0;
		if ( g_DupeFileFind.m_DuffStatus.SubProgress1.Max )
		 PercentDone = (int)(100 * (double)g_DupeFileFind.m_DuffStatus.SubProgress1.Pos / (double)g_DupeFileFind.m_DuffStatus.SubProgress1.Max);

		Temp.Format( _T("%03d %%") ,PercentDone);
		m_SubRange1.SetWindowText(Temp);

		m_ProgressSub2.SetRange64( g_DupeFileFind.m_DuffStatus.SubProgress2.Min, g_DupeFileFind.m_DuffStatus.SubProgress2.Max );
		m_ProgressSub2.SetPos64( g_DupeFileFind.m_DuffStatus.SubProgress2.Pos );
		PercentDone = 0;
		if ( g_DupeFileFind.m_DuffStatus.SubProgress2.Max )
			PercentDone = (int)(100 * (double)g_DupeFileFind.m_DuffStatus.SubProgress2.Pos / (double)g_DupeFileFind.m_DuffStatus.SubProgress2.Max);

		Temp.Format( _T("%03d %%") ,PercentDone);
		m_SubRange2.SetWindowText(Temp);

		for ( i = 0; i < g_DupeFileFind.m_DuffStatus.LogQueue.GetSize(); i++ )
		{
			Log( g_DupeFileFind.m_DuffStatus.LogQueue.ElementAt(i) );
		}
		g_DupeFileFind.m_DuffStatus.LogQueue.RemoveAll();

		if ( g_DupeFileFind.m_DuffStatus.DupeQueue.GetSize() && theApp.m_DuffOptions.Sound.Enabled )
		{
			PlaySoundFile( theApp.m_DuffOptions.Sound.FoundDuplicate);
		}

		for ( i = 0; i < g_DupeFileFind.m_DuffStatus.DupeQueue.GetSize(); i++ )
		{
			pFileInfo = g_DupeFileFind.m_DuffStatus.DupeQueue.ElementAt(i);

			ASSERT(pFileInfo);

			m_DuplicatePage.AddItem(pFileInfo);
			/*

			if ( pFileInfo->FirstFile )
			{
			m_DuplicatePage.m_DuplicateSetCounter ++;
			}

			// add duplicates to list view
			Temp.Format("%d", m_DuplicatePage.m_DuplicateSetCounter);
			m_DuplicatePage.m_DupeList.InsertItem(LVIF_PARAM | LVIF_TEXT, m_DuplicatePage.m_TotalFilesCounter, Temp,NULL,NULL,NULL,(DWORD) pFileInfo );
			m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,1, pFileInfo ->FullName    );
			buffer[0] = 0;
			ulonglong2str(buffer,pFileInfo->Size);
			m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,2,buffer);
			pFileInfo->InitVersion();
			m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,3, pFileInfo->GetFileVersionStr());
			//

			*/

		}
		g_DupeFileFind.m_DuffStatus.DupeQueue.RemoveAll();

		if ( theApp.m_DuffOptions.General.AutoScrollDupeList  )
		{
			//if ( (unsigned long)(m_DuplicatePage.m_DupeList.GetTopIndex() + m_DuplicatePage.m_DupeList.GetCountPerPage()) == m_DuplicatePage.m_TotalFilesCounter -1 ||
			//	(unsigned long)(m_DuplicatePage.m_DupeList.GetCountPerPage()) >   m_DuplicatePage.m_TotalFilesCounter -1
			//	)
			m_DuplicatePage.m_DupeList.EnsureVisible((int)m_DuplicatePage.GetNumFiles()-1, FALSE);
		}

	 g_DupeFileFind.m_DuffStatus.Unlock();

	}
	//CResizableDialog::OnTimer(nIDEvent);
}

// will change
void CDuffDlg::OnHelpIndex()
{
 int error;
	error = (int)ShellExecute(this->GetSafeHwnd(), NULL, _T("help.htm"), NULL, NULL, SW_SHOWDEFAULT );
	if ( error <= 32 )
	{
		MessageBox( GetErrorStr(error), StringFromResource(IDS_ERROR), MB_OK | MB_ICONEXCLAMATION);
	}
	/*
 MessageBox( _T("Everything about DUFF is intuatively obvious, so I decided not to write any help files."), _T("DUFF Help"), MB_OK | MB_ICONINFORMATION );
 MessageBox( _T("Just kidding. Help is not available yet."), _T("DUFF Help"), MB_OK | MB_ICONINFORMATION );
*/
}

void CDuffDlg::OnFileSaveGlobal()
{
 theApp.m_DuffOptions.SaveOptions();
	Log( StringFromResource(IDS_SAVED_GLOBAL_OPTIONS) );
}


BOOL CDuffDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	ClipChildren(pDC);

	return CResizableDialog::OnEraseBkgnd(pDC);
}


void CDuffDlg::OnFileExportCsv()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}

void CDuffDlg::OnFileExportDuplic8()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}

void CDuffDlg::OnFileExportFnd()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}

void CDuffDlg::OnFileImportDuplic8()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}

void CDuffDlg::OnFileImportFnd()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}


void CDuffDlg::SaveSettings()
{
 MessageBox(StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET), StringFromResource(IDS_MSGBOX_NOT_IMPLEMENTED_YET_TITLE), MB_OK | MB_ICONINFORMATION);
}

//typedef CFileProcessor *(*FuncPtr)();
//#define PLUGIN_INIT_FUNCTION_NAME "GetProcessorPtr"

int CDuffDlg::LoadPlugins()
{
 CString sTemp;
 CString sMsg;

	m_PluginManager.LoadPlugins();

	POSITION ListPos;

	ListPos = m_PluginManager.m_Plugins.GetHeadPosition();
 CDuffPlugin *pPlugin;

	while (ListPos)
	{
  pPlugin = & m_PluginManager.m_Plugins.GetAt(ListPos);
		switch ( pPlugin->GetType() )
		{
		 case CDuffPlugin::PLUGIN_PROCESSOR:
    m_ProcessPage.AddPlugin(pPlugin);
    sTemp = StringFromResource(IDS_PLUGINTYPE_PROCESSOR);
			break;
		}
  sMsg.Format( StringFromResource(IDS_LOADED_PLUGIN), pPlugin->GetPrimaryModule()->GetName(), sTemp , pPlugin->GetFilename() );
  Log(sMsg);
	 m_PluginManager.m_Plugins.GetNext(ListPos);
	}



	/*
 int Count = 0;
 bool Good;
 CString Msg;
 CString sFilename;
 HINSTANCE hInstance;
	CFileFind ff;
	CString SearchPath;
	int iPluginTypeIndex = 0;
 bool Loaded = false;
 FuncPtr MyFunc;
	CFileProcessor * pProcessor = NULL;

	SearchPath = _pgmptr;
	SearchPath = SearchPath.Left( SearchPath.ReverseFind( _T('\\') ) +1);
	SearchPath += _T("plugins\\*.dll");

	Good = ff.FindFile(SearchPath) != 0;
 while ( Good )
	{
		Good = ff.FindNextFile() != 0;
  sFilename = ff.GetFilePath();
		iPluginTypeIndex = 0;
		Loaded = false;
	 hInstance = LoadLibrary(sFilename);

  if (hInstance)
	 {
		 MyFunc = (FuncPtr) GetProcAddress(hInstance, PLUGIN_INIT_FUNCTION_NAME );
   if (MyFunc)
		 {

				pProcessor = MyFunc();
			 if (pProcessor)
			 {
					m_ProcessPage.AddProcessor(hInstance,pProcessor);
		   Loaded = true;
				}
		 }
	 }

		if ( Loaded )
		{
		 Msg.Format( StringFromResource(IDS_LOADED_PLUGIN), pProcessor->GetName(), _T("processor"),ff.GetFileName());
			Count++;
		}
		else
		{
		 Msg.Format( StringFromResource(IDS_SKIPPING_NON_DLL), ff.GetFileName());
		}
		Log(Msg);
	}

	return Count;
	*/
	return 0;
}


void CDuffDlg::OnTest()
{
	int i;
	for (i=0; i< m_DuplicatePage.m_DupeList.GetItemCount(); i++)
	{
		if ( ((CFileInfo *)m_DuplicatePage.m_DupeList.GetItemData(i))->Size == 666 )
			MessageBox(_T("hehe"));
	}

}
