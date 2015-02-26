#if !defined(AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_)
#define AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MINIMUMPAGES.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES ダイアログ

class CMINIMUMPAGES : public CDialog
{
// コンストラクション
public:
	char m_mnp[256];
	CMINIMUMPAGES(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMINIMUMPAGES)
	enum { IDD = IDD_MINIMUM_PAGES };
	CEdit	m_mnp_edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMINIMUMPAGES)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMINIMUMPAGES)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_)
