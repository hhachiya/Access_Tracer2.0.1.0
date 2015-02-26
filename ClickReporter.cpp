// ClickReporter.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "ClickReporter.h"

#include "MainFrm.h"
#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "Cipher.h"
#include "LICENCE.h"
#include "Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp

BEGIN_MESSAGE_MAP(CClickReporterApp, CWinApp)
	//{{AFX_MSG_MAP(CClickReporterApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp クラスの構築

CClickReporterApp::CClickReporterApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CClickReporterApp オブジェクト

CClickReporterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp クラスの初期化

BOOL CClickReporterApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。

#ifdef _AFXDLL
	Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

	// 設定が保存される下のレジストリ キーを変更します。
	// TODO: この文字列を、会社名または所属など適切なものに
	// 変更してください。
	SetRegistryKey(_T("Interlog"));
	LoadStdProfileSettings();  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClickReporterDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CClickReporterView));
	AddDocTemplate(pDocTemplate);

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンドラインでディスパッチ コマンドを指定します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	/*
	// chang the path of INI file
	if( m_pszProfileName ) {
		delete ((void*)m_pszProfileName);
		m_pszProfileName = new char[MAX_PATH];
		if( !m_pszProfileName ) {
			AfxMessageBox("メモリ不足エラーです。");
			return FALSE;
		}
		::GetCurrentDirectory(MAX_PATH, (LPTSTR)m_pszProfileName);
		AfxMessageBox(m_pszProfileName);
		strcat((LPTSTR)m_pszProfileName, "\\ClickReporter.ini");
	}
	*/

	//##################################
	// Licence Stuff
	//##################################
	// set licence file path
	char lfilename[256];
	GetLicenceFilePath(lfilename);
	
	// if licence file exists or not
	if(::GetFileAttributes(lfilename) != 0xFFFFFFFF){

		// get days left to expire date
		int left_day;
		if((left_day = GetDatesToExpire()) == -1000){
			AfxMessageBox("不正なライセンスキーが登録されています。ライセンスを購入してください。");

			CLICENCE dlg;
			dlg.DoModal();
			//return 0;
		}

		// 
		if(left_day >= 0 && left_day <= 15){
			CString msg;
			msg.Format(_T("ライセンスの期限まで、あと%d日です。"),left_day);
			AfxMessageBox(msg);
		}else if(left_day < 0){
			CString msg;
			msg.Format(_T("ライセンスの期限が切れました。購入してください。"),left_day);
			AfxMessageBox(msg);

			CLICENCE dlg;
			dlg.DoModal();
			//return 0;
		}

	}else{
		// get current time
		CTime current = CTime::GetCurrentTime();
		time_t current_b = current.GetTime();		//seconds

		//open file
		CFile lfile(lfilename,CFile::modeCreate|CFile::modeWrite);

		// set expire time after 15 days 
		time_t expire_b = current_b + 86400*15;
		CTime expire(expire_b);

		CString expire_s = expire.Format("%Y/%m/%d");

		// cipher
		CCipher* cipher = new CCipher("Trial","Trial",expire_s);
		cipher->encode();

		lfile.Write(cipher->key,cipher->key.GetLength());
		lfile.Close();
	}
	//##################################

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	CAboutDlg();

	// ClassWizard 仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CClickReporterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
