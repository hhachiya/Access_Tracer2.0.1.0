#if !defined(AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_)
#define AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DetailReport.h : ヘッダー ファイル
//
#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDetailReport ダイアログ

class CDetailReport : public CDialog
{
// コンストラクション
public:
	CString m_strTitle;
	void SetDetailData(vector< vector< string > > details);
	CDetailReport(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDetailReport)
	enum { IDD = IDD_DETAIL };
	CListCtrl	m_detail;
	vector < vector<string> > details;
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDetailReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDetailReport)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDetailCopyAsItIs();
	afx_msg void OnDetailCopyExchangeDateClient();
	afx_msg void OnViewPage();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_)
