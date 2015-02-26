#if !defined(AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_)
#define AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LICENCE.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLICENCE ダイアログ

class CLICENCE : public CDialog
{
// コンストラクション
public:
	CLICENCE(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLICENCE)
	enum { IDD = IDD_LICENCE_INFO };
	CEdit	m_key;
	CStatic	m_email;
	CStatic	m_expire;
	CStatic	m_username;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLICENCE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLICENCE)
	afx_msg void OnClose();
	afx_msg void OnLicenceRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowLicenceInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_)
