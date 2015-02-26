#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
using namespace std;
#if !defined(AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_)
#define AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// UserAdd.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CUserAdd ダイアログ

class CUserAdd : public CDialog
{
// コンストラクション
public:
	CString m_buttonTitle;
	CString m_strTitle;
	char m_mail_address[256];
	char m_name[256];
	char m_company[256];
	char m_item1[256];
	char m_item2[256];
	CUserAdd(CWnd* pParent = NULL);   // 標準のコンストラクタ
	void SetData(string address, string name, string company, string item1, string item2);
// ダイアログ データ
	//{{AFX_DATA(CUserAdd)
	enum { IDD = IDD_USER_ADD };
	CButton	m_ok_button;
	CEdit	m_name_edit;
	CEdit	m_item2_edit;
	CEdit	m_item1_edit;
	CEdit	m_company_edit;
	CEdit	m_mail_address_edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CUserAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CUserAdd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_)
