// ClickReporterView.h : CClickReporterView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_)
#define AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

using namespace std;

class CClickReporterView : public CFormView
{
protected: // シリアライズ機能のみから作成します。
	CClickReporterView();
	DECLARE_DYNCREATE(CClickReporterView)

public:
	//{{AFX_DATA(CClickReporterView)
	enum { IDD = IDD_CLICKREPORTER_FORM };
	CStatic	m_daterange;
	CMonthCalCtrl	m_date_to_calendar;
	CMonthCalCtrl	m_date_from_calendar;
	CListCtrl	m_user_list;
	//}}AFX_DATA

// アトリビュート
public:
	CClickReporterDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CClickReporterView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	virtual void OnInitialUpdate(); // 構築後の最初の１度だけ呼び出されます。
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	int m_sort_index;
	BOOL m_sort_order;
	string m_search_referrer;
	string m_search_wayin;
	string m_search_wayout;
	string m_search_page1;
	string m_search_page2;
	virtual ~CClickReporterView();
	int AddToList(int index);
#ifdef _DEBUG  
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	static int CALLBACK SortData(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CClickReporterView)
	afx_msg void OnNetConfig();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnShowDetail();
	afx_msg void OnEditSelectedUser();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLicenceInfo();
	afx_msg void OnSearch();
	afx_msg void OnDblclkUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchMinimumPages();
	afx_msg void OnColumnclickUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchReferrer();
	afx_msg void OnViewReferrerpage();
	afx_msg void OnInsertitemUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDateSelect();
	afx_msg void OnSelchangeMonthcalendarTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMonthcalendarFrom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetDate();
	afx_msg void OnSearchNoRobot();
	afx_msg void OnUpdateSearchNoRobot(CCmdUI* pCmdUI);
	afx_msg void OnSearchOnlyMail();
	//}}AFX_MSG
public:
	int m_robot_view_status;
	int m_mail_view_status;
	int view_cnt;
	afx_msg void OnViewAll();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ClickReporterView.cpp ファイルがデバッグ環境の時使用されます。
inline CClickReporterDoc* CClickReporterView::GetDocument()
   { return (CClickReporterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_)
