// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "ClickReporter.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//create tool bar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//indicators
	static UINT indicators[] =
	{
		ID_SEPARATOR, // status line indicator
		ID_INDICATOR_STATUS,
		ID_INDICATOR_USERNUM,
	};

	//create status bar
	if (!m_wndStatusBar.Create(this, WS_CHILD|WS_VISIBLE|CBRS_BOTTOM) ||	!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//App pointer
	CClickReporterApp* m_pApp = (CClickReporterApp*)AfxGetApp();

	//configure progress bar
	CRect	rctProg;
	m_wndStatusBar.SetPaneInfo( 0, m_wndStatusBar.GetItemID( 0 ), m_wndStatusBar.GetPaneStyle( 0 ), 50 );
	rctProg.top = 2;
	rctProg.left = 10;
	rctProg.right = 160;
	rctProg.bottom = 18;

	//create progress bar
	m_pApp->m_wndProgressCtrl = new CProgressCtrl;
	m_pApp->m_wndProgressCtrl->Create( WS_CHILD | WS_VISIBLE, rctProg, &m_wndStatusBar, 1 );
	
	// set progress bar
	m_pApp->m_wndProgressCtrl->SetRange( 0, 100 );
	m_pApp->m_wndProgressCtrl->SetPos(0);

	//##################################
	// DATE SETTING

	//today
	CTime today = CTime::GetCurrentTime();
	time_t today_b = today.GetTime();
	
	//a week ago
    time_t aweekago_b = today_b - 86400*6;
	CTime aweekago(aweekago_b);


    // set to registor
	CWinApp* pApp = AfxGetApp();

	// date from
	pApp->WriteProfileInt("report","fyear",aweekago.GetYear());
	pApp->WriteProfileInt("report","fmonth",aweekago.GetMonth());
	pApp->WriteProfileInt("report","fday",aweekago.GetDay());

	// date to
	pApp->WriteProfileInt("report","tyear",today.GetYear());
	pApp->WriteProfileInt("report","tmonth",today.GetMonth());
	pApp->WriteProfileInt("report","tday",today.GetDay());
	//##################################

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	// get rid of file name from title menu
	cs.style ^= FWS_ADDTOTITLE;

	SetTitle("アクセス追跡隊");

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ


void CMainFrame::DisplayNumberOfUser(int num)
{
	int index = m_wndStatusBar.CommandToIndex(ID_INDICATOR_USERNUM);
	if(index >= 0) {
		CString str_msg;
		str_msg.Format(_T("訪問者 %d人"),num);
		m_wndStatusBar.SetPaneText(index, str_msg);
	}
}

void CMainFrame::ShowStatus(CString msg)
{
	int index = m_wndStatusBar.CommandToIndex(ID_INDICATOR_STATUS);
	m_wndStatusBar.SetPaneText(index, msg);
}

BOOL CMainFrame::CopyToClipboard(LPCSTR lpString)
{
    HGLOBAL hMem = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, strlen(lpString) + 1);

    if (!hMem)
        return FALSE;

    if (::lstrcpy((char*)::GlobalLock(hMem), lpString) && OpenClipboard())
    {
        ::GlobalUnlock(hMem);
        if (::EmptyClipboard())
        {
            if (::SetClipboardData(CF_TEXT, hMem))
            {
                ::CloseClipboard();
                return TRUE;
            }
        }
        ::CloseClipboard();
    }
    ::GlobalFree(hMem);
    return FALSE;
}

void CMainFrame::SetMyTitle(CString msg)
{
	CString title;
	title.Format(_T("%s - アクセス追跡隊"),msg);
	SetWindowText(title);
}
