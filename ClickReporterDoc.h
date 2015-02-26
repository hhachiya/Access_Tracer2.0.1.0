// ClickReporterDoc.h : CClickReporterDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
#include <vector>
#include <wininet.h>
#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <wspiapi.h>

using namespace std;
#include "CReport.h"

#if !defined(AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_)
#define AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClickReporterDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CClickReporterDoc();
	DECLARE_DYNCREATE(CClickReporterDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CClickReporterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CClickReporterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CClickReporterDoc)
	afx_msg void OnReportExec();
	afx_msg void OnResolveHostname();
	afx_msg void OnStopDataAnalyze();
	afx_msg void OnFileSaveOnlyShown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	char m_filename[256];
	string m_analyze_status;
	string m_data;
	int m_data_analyze_flag;
	int month_text2num(string month);
	int GetTimeDifference(string stime1, string stime2);
	int GetNumTimeFromWebTime(string webtime, vector<int> &numtime);
	void GetNumTimeFromSofTime(string softime, vector<int> &numtime);
	int m_save_only_shown;
	void decrypt( int seed, char* TheString );
	string decURL( int seed, const char* table, string crypted );
	int m_download_progress;
	vector <CReport> m_report;

	//controlling function header
	static UINT HostnameResolveThread (LPVOID param);
	static UINT AccessDataAnalyzeThread (LPVOID param);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_)
