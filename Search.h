#if !defined(AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_)
#define AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Search.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSearch ダイアログ

class CSearch : public CDialog
{
// コンストラクション
public:
	char m_page1[256];
	char m_page2[256];
	char m_wayin[256];
	char m_wayout[256];
	char m_referrer[256];
	CSearch(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSearch)
	enum { IDD = IDD_SEARCH };
	CEdit	m_referrer_edit;
	CEdit	m_page1_edit;
	CEdit	m_page2_edit;
	CEdit	m_wayout_edit;
	CEdit	m_wayin_edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSearch)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_)
