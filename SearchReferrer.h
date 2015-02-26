#if !defined(AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_)
#define AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchReferrer.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSearchReferrer ダイアログ

class CSearchReferrer : public CDialog
{
// コンストラクション
public:
	char m_referrer[512];
	CSearchReferrer(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSearchReferrer)
	enum { IDD = IDD_SEARCH_REFERRER };
	CEdit	m_referrer_edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSearchReferrer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSearchReferrer)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_)
