// Search.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "Search.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearch ダイアログ


CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearch)
	//}}AFX_DATA_INIT

	//initialize variables
	memset(m_wayin,0,256);
	memset(m_wayout,0,256);
	memset(m_page1,0,256);
	memset(m_page2,0,256);
	memset(m_referrer,0,256);
}


void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearch)
	DDX_Control(pDX, IDC_SEARCH_REFERRER, m_referrer_edit);
	DDX_Control(pDX, IDC_SEARCH_PAGE1, m_page1_edit);
	DDX_Control(pDX, IDC_SEARCH_PAGE2, m_page2_edit);
	DDX_Control(pDX, IDC_SEARCH_WAYOUT, m_wayout_edit);
	DDX_Control(pDX, IDC_SEARCH_WAYIN, m_wayin_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearch, CDialog)
	//{{AFX_MSG_MAP(CSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearch メッセージ ハンドラ


void CSearch::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください

	//get each data from edit
	m_wayin_edit.GetLine(0,m_wayin,256);
	m_wayout_edit.GetLine(0,m_wayout,256);
	m_page1_edit.GetLine(0,m_page1,256);
	m_page2_edit.GetLine(0,m_page2,256);
	m_referrer_edit.GetLine(0,m_referrer,256);

	CDialog::OnOK();
}
