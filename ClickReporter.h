// ClickReporter.h : CLICKREPORTER アプリケーションのメイン ヘッダー ファイル
//
#if !defined(AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_)
#define AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp:
// このクラスの動作の定義に関しては ClickReporter.cpp ファイルを参照してください。
//

class CClickReporterApp : public CWinApp
{
public:
	//int GetDatesToExpire(CString key="");
	CClickReporterApp();
	CProgressCtrl*	m_wndProgressCtrl;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CClickReporterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CClickReporterApp)
	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_)
