// UserAdd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "UserAdd.h"

#include "ClickReporterDoc.h"
#include "ClickReporterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserAdd ダイアログ


CUserAdd::CUserAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserAdd)
	//}}AFX_DATA_INIT
	memset(m_mail_address,0,256);
	memset(m_name,0,256);
	memset(m_company,0,256);
	memset(m_item1,0,256);
	memset(m_item2,0,256);
}


void CUserAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserAdd)
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_NAME, m_name_edit);
	DDX_Control(pDX, IDC_ITEM2, m_item2_edit);
	DDX_Control(pDX, IDC_ITEM1, m_item1_edit);
	DDX_Control(pDX, IDC_COMPANY, m_company_edit);
	DDX_Control(pDX, IDC_MAIL_ADDRESS, m_mail_address_edit);
	//}}AFX_DATA_MAP

	m_ok_button.SetWindowText(m_buttonTitle);
	m_mail_address_edit.SetWindowText(m_mail_address);
	m_name_edit.SetWindowText(m_name);
	m_company_edit.SetWindowText(m_company);
	m_item1_edit.SetWindowText(m_item1);
	m_item2_edit.SetWindowText(m_item2);
}


BEGIN_MESSAGE_MAP(CUserAdd, CDialog)
	//{{AFX_MSG_MAP(CUserAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserAdd メッセージ ハンドラ


void CUserAdd::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	m_mail_address_edit.GetLine(0,m_mail_address,256);
	m_name_edit.GetLine(0,m_name,256);
	m_company_edit.GetLine(0,m_company,256);
	m_item1_edit.GetLine(0,m_item1,256);
	m_item2_edit.GetLine(0,m_item2,256);

	CDialog::OnOK();
}

void CUserAdd::SetData(string address, string name, string company, string item1, string item2){
	strcpy(this->m_mail_address,address.c_str());
	strcpy(this->m_name,name.c_str());
	strcpy(this->m_company,company.c_str());
	strcpy(this->m_item1,item1.c_str());
	strcpy(this->m_item2,item2.c_str());
}

BOOL CUserAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	SetWindowText(m_strTitle);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
