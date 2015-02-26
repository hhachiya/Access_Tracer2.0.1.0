#if !defined(AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_)
#define AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NET_CONF.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CNET_CONF ダイアログ

class CNET_CONF : public CDialog
{
// コンストラクション
public:
	CNET_CONF(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CNET_CONF)
	enum { IDD = IDD_NET_CONF };
	CEdit	m_tpg;
	CEdit	m_web;
	CEdit	m_sto;
	CEdit	m_lpt;
	CEdit	m_pas;
	CEdit	m_usr;
	CEdit	m_url;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CNET_CONF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CNET_CONF)
	virtual void OnOK();
	afx_msg void OnLogplace0();
	afx_msg void OnLogplace1();
	afx_msg void OnFilePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_)
