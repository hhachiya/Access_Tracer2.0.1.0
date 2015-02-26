// NET_CONF.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "NET_CONF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNET_CONF ダイアログ


CNET_CONF::CNET_CONF(CWnd* pParent /*=NULL*/)
	: CDialog(CNET_CONF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNET_CONF)
	//}}AFX_DATA_INIT
}


void CNET_CONF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNET_CONF)
	DDX_Control(pDX, IDC_TOP_PAGE, m_tpg);
	DDX_Control(pDX, IDC_WEB_URL, m_web);
	DDX_Control(pDX, IDC_SESSION_TIMEOUT, m_sto);
	DDX_Control(pDX, IDC_PATH, m_lpt);
	DDX_Control(pDX, IDC_PASWD, m_pas);
	DDX_Control(pDX, IDC_USERID, m_usr);
	DDX_Control(pDX, IDC_URL, m_url);
	//}}AFX_DATA_MAP

	//
	CWinApp* pApp = AfxGetApp();
	m_url.SetWindowText(pApp->GetProfileString("log", "url"));
	m_lpt.SetWindowText(pApp->GetProfileString("log", "local_path"));
	m_usr.SetWindowText(pApp->GetProfileString("log", "user_id"));
	m_pas.SetWindowText(pApp->GetProfileString("log", "password"));
	m_web.SetWindowText(pApp->GetProfileString("report","web_url"));
	m_tpg.SetWindowText(pApp->GetProfileString("report","top_page"));

	//for session time out
	CString buf; int val;
	if((val = pApp->GetProfileInt("report","session_timeout",0)))
		buf.Format(_T("%d"),val);
	else
		buf.Format(_T("%d"),1800);
	m_sto.SetWindowText(buf);

	//log place
	if(!pApp->GetProfileInt("log","log_place",0	)){
		((CButton *)GetDlgItem(IDC_LOGPLACE0))->SetCheck(BST_CHECKED);
		m_url.SetReadOnly(TRUE);
	}else{
		((CButton *)GetDlgItem(IDC_LOGPLACE1))->SetCheck(BST_CHECKED);
		m_lpt.SetReadOnly(TRUE);
	}

	/*
	//hostname resolve
	if(pApp->GetProfileInt("log","hostname_resolve",0	))
		((CButton *)GetDlgItem(IDC_HOSTNAME_RESOLVE))->SetCheck(BST_CHECKED);
	*/
}


BEGIN_MESSAGE_MAP(CNET_CONF, CDialog)
	//{{AFX_MSG_MAP(CNET_CONF)
	ON_BN_CLICKED(IDC_LOGPLACE0, OnLogplace0)
	ON_BN_CLICKED(IDC_LOGPLACE1, OnLogplace1)
	ON_BN_CLICKED(IDC_FILE_PATH, OnFilePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNET_CONF メッセージ ハンドラ

void CNET_CONF::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください

	//variables as lpszText
	char url[1024];		//URL
	char lpt[1024];		//Local Path
	char usr[256];		//Username
	char pas[256];		//Password
	char web[1024];
	char sto[256];		//Session Time Out
	char tpg[256];

	//initilize
	memset(url,0,1024);
	memset(lpt,0,1024);
	memset(usr,0,256);
	memset(pas,0,256);
	memset(web,0,1024);
	memset(sto,0,256);
	memset(tpg,0,256);

	//get line frm edit
	m_url.GetLine(0,url,1024);
	m_lpt.GetLine(0,lpt,1024);
	m_usr.GetLine(0,usr,256);
	m_pas.GetLine(0,pas,256);
	m_web.GetLine(0,web,1024);
	m_sto.GetLine(0,sto,256);
	m_tpg.GetLine(0,tpg,256);

	//save to ini file
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("log","url",url);
	pApp->WriteProfileString("log","local_path",lpt);
	pApp->WriteProfileString("log","user_id",usr);
	pApp->WriteProfileString("log","password",pas);
	pApp->WriteProfileString("report","web_url",web);
	pApp->WriteProfileInt("report","session_timeout",atoi(sto));
	pApp->WriteProfileString("report","top_page",tpg);

	//check radio button for type of url
	if(((CButton *)GetDlgItem(IDC_LOGPLACE0))->GetCheck() == BST_CHECKED)
		pApp->WriteProfileInt("log","log_place",0);
	else
		pApp->WriteProfileInt("log","log_place",1);

	/*
	//check checkbox button for hostname resolution
	if(((CButton *)GetDlgItem(IDC_HOSTNAME_RESOLVE))->GetCheck() == BST_CHECKED)
		pApp->WriteProfileInt("log","hostname_resolve",1);
	else
		pApp->WriteProfileInt("log","hostname_resolve",0);
	*/

	CDialog::OnOK();
}

void CNET_CONF::OnLogplace0() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_url.SetReadOnly(TRUE);
	m_lpt.SetReadOnly(FALSE);
}

void CNET_CONF::OnLogplace1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_lpt.SetReadOnly(TRUE);
	m_url.SetReadOnly(FALSE);
}

void CNET_CONF::OnFilePath() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	if(((CButton *)GetDlgItem(IDC_LOGPLACE0))->GetCheck() == BST_CHECKED){
		CFileDialog dlg( TRUE, "*.*", "test.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"logファイル (*.log)|*.log|All Files (*.*)|*.*||",this);
		// open dialog for file open
		if( dlg.DoModal() == IDOK)
			m_lpt.SetWindowText(dlg.GetPathName());
	}
}
