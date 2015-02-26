// MINIMUMPAGES.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "MINIMUMPAGES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES ダイアログ


CMINIMUMPAGES::CMINIMUMPAGES(CWnd* pParent /*=NULL*/)
	: CDialog(CMINIMUMPAGES::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMINIMUMPAGES)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT

	//init m_mnpt
	memset(m_mnp,0,256);

}


void CMINIMUMPAGES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMINIMUMPAGES)
	DDX_Control(pDX, IDC_MINIMU_PAGES, m_mnp_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMINIMUMPAGES, CDialog)
	//{{AFX_MSG_MAP(CMINIMUMPAGES)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES メッセージ ハンドラ

void CMINIMUMPAGES::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください

	//get line from edit
	m_mnp_edit.GetLine(0,m_mnp,256);

	CDialog::OnOK();
}
