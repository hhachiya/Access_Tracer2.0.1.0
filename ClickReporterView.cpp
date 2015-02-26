// ClickReporterView.cpp : CClickReporterView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "ClickReporter.h"

#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "NET_CONF.h"
#include "DetailReport.h"
#include "UserAdd.h"
#include "MainFrm.h"
#include "LICENCE.h"
#include "Search.h"
#include "SearchReferrer.h"
#include "MINIMUMPAGES.h"
#include "Sort.h"
#include "Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClickReporterView

IMPLEMENT_DYNCREATE(CClickReporterView, CFormView)

BEGIN_MESSAGE_MAP(CClickReporterView, CFormView)
	//{{AFX_MSG_MAP(CClickReporterView)
	ON_COMMAND(ID_NET_CONFIG, OnNetConfig)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SHOW_DETAIL, OnShowDetail)
	ON_COMMAND(ID_EDIT_SELECTED_USER, OnEditSelectedUser)
	ON_WM_SIZE()
	ON_COMMAND(ID_LICENCE_INFO, OnLicenceInfo)
	ON_COMMAND(ID_SEARCH, OnSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_USER_LIST, OnDblclkUserList)
	ON_COMMAND(ID_SEARCH_MINIMUM_PAGES, OnSearchMinimumPages)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_USER_LIST, OnColumnclickUserList)
	ON_COMMAND(ID_SEARCH_REFERRER, OnSearchReferrer)
	ON_COMMAND(ID_VIEW_REFERRERPAGE, OnViewReferrerpage)
	ON_NOTIFY(LVN_INSERTITEM, IDC_USER_LIST, OnInsertitemUserList)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR_TO, OnSelchangeMonthcalendarTo)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR_FROM, OnSelchangeMonthcalendarFrom)
	ON_BN_CLICKED(IDC_SET_DATE, OnSetDate)
	ON_COMMAND(ID_SEARCH_NO_ROBOT, OnSearchNoRobot)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_NO_ROBOT, OnUpdateSearchNoRobot)
	ON_COMMAND(ID_VIEW_ALL, OnViewAll)
	ON_COMMAND(ID_SEARCH_ONLY_MAIL, OnSearchOnlyMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickReporterView クラスの構築/消滅

CClickReporterView::CClickReporterView()
	: CFormView(CClickReporterView::IDD)
{
	//{{AFX_DATA_INIT(CClickReporterView)
	//}}AFX_DATA_INIT
	// TODO: この場所に構築用のコードを追加してください。

}

CClickReporterView::~CClickReporterView()
{
}

void CClickReporterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClickReporterView)
	DDX_Control(pDX, IDC_DATERANGE, m_daterange);
	DDX_Control(pDX, IDC_MONTHCALENDAR_TO, m_date_to_calendar);
	DDX_Control(pDX, IDC_MONTHCALENDAR_FROM, m_date_from_calendar);
	DDX_Control(pDX, IDC_USER_LIST, m_user_list);
	//}}AFX_DATA_MAP
}

BOOL CClickReporterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CFormView::PreCreateWindow(cs);
}

void CClickReporterView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	//get pointer for doc
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();
	if(pDoc->m_report.size())
		OnViewAll();

	//initialize m_user_list
	if(!m_user_list.GetHeaderCtrl()->GetItemCount()){
		//Full Row Select
		ListView_SetExtendedListViewStyle(m_user_list.m_hWnd, LVS_EX_FULLROWSELECT );

		m_user_list.InsertColumn(0,"",LVCFMT_LEFT,18,-1);
		m_user_list.InsertColumn(1,"訪問日時",LVCFMT_LEFT,120,-1);
		m_user_list.InsertColumn(2,"リファラ",LVCFMT_LEFT,180,-1);
		m_user_list.InsertColumn(3,"ホスト名・IPアドレス",LVCFMT_LEFT,180,-1);
		m_user_list.InsertColumn(4,"キーワード",LVCFMT_LEFT,180,-1);
		m_user_list.InsertColumn(5,"OS・携帯",LVCFMT_LEFT,100,-1);
		m_user_list.InsertColumn(6,"ブラウザ",LVCFMT_LEFT,60,-1);
		m_user_list.InsertColumn(7,"ページ数",LVCFMT_LEFT,60,-1);

		// set image list
		CImageList* m_pImage = new CImageList();
		m_pImage->Create(16,16,TRUE,4,4);
		m_pImage->Add(AfxGetApp()->LoadIcon(IDR_REFERRER));
		m_pImage->Add(AfxGetApp()->LoadIcon(IDR_DIRECT));
		m_pImage->Add(AfxGetApp()->LoadIcon(IDR_EMAIL));
		m_pImage->Add(AfxGetApp()->LoadIcon(IDI_ROBOT));
		m_user_list.SetImageList(m_pImage,LVSIL_SMALL);

		//*****************************
		// set calendars

		// get from registor
		CWinApp* pApp = AfxGetApp();
		int fyear = pApp->GetProfileInt("report","fyear",0);
		int fmonth = pApp->GetProfileInt("report","fmonth",0);
		int fday = pApp->GetProfileInt("report","fday",0);
		int tyear = pApp->GetProfileInt("report","tyear",0);
		int tmonth = pApp->GetProfileInt("report","tmonth",0);
		int tday = pApp->GetProfileInt("report","tday",0);
	
		// set ctime
		CTime fdate(fyear, fmonth, fday, 0, 0, 0);
		CTime tdate(tyear, tmonth, tday, 0, 0, 0);

		m_date_from_calendar.SetCurSel(fdate);
		m_date_to_calendar.SetCurSel(tdate);

		// color			
		m_date_from_calendar.SetColor(MCSC_TITLEBK, RGB(200,0,200));
		m_date_to_calendar.SetColor(MCSC_TITLEBK, RGB(0,200,200));
		//*****************************

	}

	m_mail_view_status = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CClickReporterView クラスの診断

#ifdef _DEBUG
void CClickReporterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CClickReporterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CClickReporterDoc* CClickReporterView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClickReporterDoc)));
	return (CClickReporterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClickReporterView クラスのメッセージ ハンドラ


void CClickReporterView::OnNetConfig() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

		//######################################
		//# Check Licence Expire
		//######################################
		// get days left to expire date
		// App pointer
		int left_day;
		if((left_day = GetDatesToExpire()) == -1000){
			AfxMessageBox("不正なライセンスキーが登録されています。ライセンスを購入して下さい。");
			
			CLICENCE dlg;
			dlg.DoModal();
			return;
		}

		// 
		if(left_day < 0){
			AfxMessageBox("使用期限が切れました。ライセンスを取得して登録してください。");

			CLICENCE dlg;
			dlg.DoModal();
			return;
		}
		//######################################
		//# Check Licence Expire
		//######################################

	CNET_CONF dlg;
	dlg.DoModal();
}

void CClickReporterView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if(m_user_list.GetNextItem(-1,LVNI_SELECTED) >= 0){
		CMenu menu;

		//Get the content of referrer column
		int index = m_user_list.GetNextItem(-1,LVNI_SELECTED);
		string referrer = m_user_list.GetItemText(index,2);

		if(referrer.size() && referrer.find("@") == string::npos)
			menu.LoadMenu(MAKEINTRESOURCE(IDR_MENU_MAIN));
		else
			menu.LoadMenu(MAKEINTRESOURCE(IDR_MENU_MAIN2));

		CMenu* submenu = menu.GetSubMenu(0);
		submenu->TrackPopupMenu(TPM_CENTERALIGN,point.x,point.y,this);
	}
}

void CClickReporterView::OnShowDetail() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	int index = m_user_list.GetNextItem(-1,LVNI_SELECTED);
	string key0 = m_user_list.GetItemText(index,1);
	string key1 = m_user_list.GetItemText(index,3);

	for(unsigned int i=0;i< pDoc->m_report.size(); i++){
		if(!pDoc->m_report[i].detail[0].date.compare(key0) && !pDoc->m_report[i].hostname.compare(key1)){

			vector< vector< string > > data;
			vector< string > buf;

			for(int j=0;j<pDoc->m_report[i].cnt;j++){
				buf.clear();
				buf.push_back(pDoc->m_report[i].detail[j].date);
				buf.push_back(pDoc->m_report[i].detail[j].path);
				data.push_back(buf);
			}

			//show dialog
			CDetailReport dlg;
			dlg.m_strTitle.Format(_T("%dページ - 訪問者:%s [%s, %s] - アクセス追跡隊"),pDoc->m_report[i].cnt,pDoc->m_report[i].hostname.c_str(),pDoc->m_report[i].os.c_str(),pDoc->m_report[i].browser.c_str());
			dlg.SetDetailData(data);
			dlg.DoModal();
		}
	}
}

void CClickReporterView::OnEditSelectedUser() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int index = m_user_list.GetNextItem(-1,LVNI_SELECTED);

	if(index >= 0){
		//get dat from ListView
		string mail_address = m_user_list.GetItemText(index,1);
		string name = m_user_list.GetItemText(index,2);
		string company = m_user_list.GetItemText(index,3);
		string item1 = m_user_list.GetItemText(index,4);
		string item2 = m_user_list.GetItemText(index,5);

		//show dialog
		CUserAdd dlg;
		dlg.SetData(mail_address,name,company,item1,item2);
		dlg.m_strTitle.Format("選択ユーザの編集");
		dlg.m_buttonTitle.Format("更新");
		dlg.DoModal();

		//update selected item
		m_user_list.SetItem( index, 1, LVIF_TEXT, dlg.m_mail_address, 0, 0, 0, 0);
		m_user_list.SetItem( index, 2, LVIF_TEXT, dlg.m_name, 0, 0, 0, 0);
		m_user_list.SetItem( index, 3, LVIF_TEXT, dlg.m_company, 0, 0, 0, 0);
		m_user_list.SetItem( index, 4, LVIF_TEXT, dlg.m_item1, 0, 0, 0, 0);
		m_user_list.SetItem( index, 5, LVIF_TEXT, dlg.m_item2, 0, 0, 0, 0);
	}
}

void CClickReporterView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if(m_user_list)
		m_user_list.SetWindowPos(NULL,175,0,cx-175,cy,SWP_NOZORDER);
}

void CClickReporterView::OnLicenceInfo() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CLICENCE dlg;
	dlg.DoModal();
}

void CClickReporterView::OnSearch() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CSearch dlg;
	dlg.DoModal();

	m_search_wayin = dlg.m_wayin;
	m_search_wayout = dlg.m_wayout;
	m_search_page1 = dlg.m_page1;
	m_search_page2 = dlg.m_page2;
	m_search_referrer = dlg.m_referrer;

	// check if cancel was clicked
	if(!strlen(dlg.m_wayin) && !strlen(dlg.m_wayout) && !strlen(dlg.m_page1) && !strlen(dlg.m_page2) && !strlen(dlg.m_referrer))
		return;

	// delete all items from list
	m_user_list.DeleteAllItems();

	//get pointer for document
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	int flag;
	for(unsigned int i=0;i<pDoc->m_report.size();i++){
		flag = 0;

		if(pDoc->m_report[i].cnt >= 1){
			
			//check way in page
			if(m_search_wayin.size() && pDoc->m_report[i].detail[0].path.find(m_search_wayin) == string::npos)
				continue;

			//check way out page
			if(m_search_wayout.size() && pDoc->m_report[i].detail[pDoc->m_report[i].detail.size()-1].path.find(m_search_wayout) == string::npos)
				continue;

			//check referrer
			if(m_search_referrer.size() && pDoc->m_report[i].referrer.find(m_search_referrer) == string::npos)
				continue;

			int lflag1 = 0; //local flag for page 1
			int lflag2 = 0;	//local flag for page 2

			//check intermediate pages
			for(int j=0;j<pDoc->m_report[i].detail.size();j++){

				//page 1 with empty page2
				if( !m_search_page2.size() && pDoc->m_report[i].detail[j].path.find(m_search_page1) != string::npos )
					flag = 1;

				//page 2 with empty page1
				else if( !m_search_page1.size() && pDoc->m_report[i].detail[j].path.find(m_search_page2) != string::npos )
					flag = 1;

				//page 1 and page2
				else if( m_search_page2.size() && pDoc->m_report[i].detail[j].path.find(m_search_page1) != string::npos){

					if(lflag2)
						flag = 1;
					else
						lflag1 = 1;

				//page 2 and page1
				}else if( m_search_page1.size() && pDoc->m_report[i].detail[j].path.find(m_search_page2) != string::npos ){

					if(lflag1)
						flag = 1;
					else
						lflag2 = 1;

				}
			}
		}

		if(flag){
			AddToList(i);
		}
	}

	//#################################################
	// Set message on menu title
	CString msg;
	string bst; //buffer string
	flag = 0;

	//way in
	if(m_search_wayin.size()){
		bst.append("入口=");
		bst.append(m_search_wayin);
		flag = 1;
	}

	//page 1
	if(m_search_page1.size()){
		if(flag)
			bst.append(" & ");
		bst.append(m_search_page1);
		flag = 1;
	}

	//page 2
	if(m_search_page2.size()){
		if(flag)
			bst.append(" & ");
		bst.append(m_search_page2);
		flag = 1;
	}

	//way out
	if(m_search_wayout.size()){
		if(flag)
			bst.append(" & ");
		bst.append("出口=");
		bst.append(m_search_wayout);
		flag = 1;
	}

	//get web_url from registory
	CWinApp* pApp = AfxGetApp();
	string web_url = pApp->GetProfileString("report","web_url");

	msg.Format(_T("%s [閲覧ページ：%s]"),web_url.c_str(),bst.c_str());

	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
	pFrame->SetMyTitle(msg);

}

void CClickReporterView::OnViewAll() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//get pointer for doc
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	//get pointer for frame
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();

	// delete all items from list
	m_user_list.DeleteAllItems();

	int cnt = 0;
	for(unsigned int i=0;i< pDoc->m_report.size();i++){
		if(pDoc->m_report[i].cnt > 0)
			if(AddToList(i)) cnt++;
	}

	//get web_url from registory
	CWinApp* pApp = AfxGetApp();
	string web_url = pApp->GetProfileString("report","web_url");

	// set title as 全表示
	pFrame->SetMyTitle(web_url.c_str());
	view_cnt = cnt;
	//return cnt;
}

void CClickReporterView::OnDblclkUserList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnShowDetail();
	*pResult = 0;
}

void CClickReporterView::OnSearchMinimumPages() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMINIMUMPAGES dlg;
	dlg.DoModal();

	if(!strlen(dlg.m_mnp))
		return;

	//get pointer for document
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	//get pointer for frame
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();

	// delete all items from list
	m_user_list.DeleteAllItems();

	int cnt = 0;
	for(unsigned int i=0;i< pDoc->m_report.size();i++){
		if(pDoc->m_report[i].cnt >= atoi(dlg.m_mnp))
			AddToList(i);
	}

	//get web_url from registory
	CWinApp* pApp = AfxGetApp();
	string web_url = pApp->GetProfileString("report","web_url");

	CString msg;
	msg.Format(_T("%s [閲覧ページ数：%s以上]"),web_url.c_str(),dlg.m_mnp);
	pFrame->SetMyTitle(msg);
}

void CClickReporterView::OnColumnclickUserList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	// set m_sort_order
	if(m_sort_index == pNMListView->iSubItem)
		if(m_sort_order == FALSE) m_sort_order = TRUE;
		else m_sort_order = FALSE;
	else
		m_sort_order = FALSE;

	// set m_sort_index
	m_sort_index = pNMListView->iSubItem;

	LV_ITEM lvItem;
	lvItem.iSubItem = 0;

	for( int i = 0; i < m_user_list.GetItemCount(); i++ ) {
		lvItem.iItem = i;

		CString *sort_item = new CString;

		if(m_sort_index == 0){			//column is icon
			lvItem.mask = LVIF_IMAGE;
			m_user_list.GetItem(&lvItem);
			sort_item->Format(_T("%d"),lvItem.iImage);
		}else{
			sort_item->Format(_T("%s"),m_user_list.GetItemText(i,m_sort_index));
		}

		lvItem.mask = LVIF_PARAM;
		lvItem.lParam = (LPARAM)sort_item;
		m_user_list.SetItem(&lvItem);
	}

	CSort* sortparam = new CSort(m_sort_index, m_sort_order);

	m_user_list.SortItems( SortData, (LPARAM)sortparam );

	*pResult = 0;
}

int CClickReporterView::SortData(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSort* sortparam = (CSort *)lParamSort;
	CString* pstrData1 = (CString *)lParam1;
	CString* pstrData2 = (CString *)lParam2;
	int nSort;

	if(sortparam->index == 0 || sortparam->index == 7)	//number of page
		nSort = atoi(*pstrData1) - atoi(*pstrData2);
	else
		nSort = pstrData1->CompareNoCase(*pstrData2);

    // ascending order
    if( sortparam->order == TRUE )	return nSort * -1;

	// descending order
    return nSort;	
}

void CClickReporterView::OnSearchReferrer() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CSearchReferrer dlg;
	dlg.DoModal();

	m_search_referrer = dlg.m_referrer;

	// check if cancel was clicked
	if(!strlen(dlg.m_referrer))
		return;

	// delete all items from list
	m_user_list.DeleteAllItems();

	//get pointer for document
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	int flag;
	for(unsigned int i=0;i<pDoc->m_report.size();i++){
		flag = 0;

		if(pDoc->m_report[i].cnt >= 1){
			//check way in page
			if(m_search_referrer.size() && (pDoc->m_report[i].referrer.find(m_search_referrer) != string::npos || pDoc->m_report[i].email.find(m_search_referrer) != string::npos)){
				AddToList(i);
			}
		}
	}


	//#################################################
	//get web_url from registory
	CWinApp* pApp = AfxGetApp();
	string web_url = pApp->GetProfileString("report","web_url");

	//#################################################
	// Set message on menu title
	CString msg;
	msg.Format(_T("%s [閲覧ページ：リファラ=%s]"),web_url.c_str(),m_search_referrer.c_str());

	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
	pFrame->SetMyTitle(msg);
}

void CClickReporterView::OnViewReferrerpage() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//get selected index
	int index = m_user_list.GetNextItem(-1,LVNI_SELECTED);

	if(index >= 0){
		string referrer = m_user_list.GetItemText(index,2);

		::ShellExecute(NULL,"open",referrer.c_str(),NULL,NULL,SW_SHOWNORMAL);
	}
}

int CClickReporterView::AddToList(int index)
{
	//get pointer for document
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	//#######################
	//test
	/*
	vector<string> d1;
	vector<string> d2;

	Tokenize(pDoc->m_report[index].detail[0].date,d1," ");		// separate by space
	Tokenize(d1[0],d2,"//");									// seprate by /

	// get time of a record
	CTime date(atoi(d2[0].c_str()), atoi(d2[1].c_str()), atoi(d2[2].c_str()), 0, 0, 0);
	time_t date_b = date.GetTime();				//seconds

	// get from registor
	CWinApp* pApp = AfxGetApp();
	int fyear = pApp->GetProfileInt("report","fyear",0);
	int fmonth = pApp->GetProfileInt("report","fmonth",0);
	int fday = pApp->GetProfileInt("report","fday",0);
	int tyear = pApp->GetProfileInt("report","tyear",0);
	int tmonth = pApp->GetProfileInt("report","tmonth",0);
	int tday = pApp->GetProfileInt("report","tday",0);

	// date from
	CTime fdate(fyear,fmonth,fday,0,0,0);
	time_t fdate_b = fdate.GetTime();

	// date to
	CTime tdate(tyear,tmonth,tday,0,0,0);
	time_t tdate_b = tdate.GetTime();

	if(!(date_b >= fdate_b && date_b <= tdate_b))
		return 0;
	*/

	//date range check
	if(!isInDateRange(pDoc->m_report[index].detail[0].date))
		return 0;

	//robot check
	if(m_robot_view_status && pDoc->m_report[index].robot)
		return 0;

	//mail check
	if(m_mail_view_status && pDoc->m_report[index].email.size() == 0)
		return 0;

    //#######################

	int nItem = m_user_list.InsertItem(m_user_list.GetItemCount(), "", 0);
	m_user_list.SetItem( nItem, 1, LVIF_TEXT, pDoc->m_report[index].detail[0].date.c_str(), 0, 0, 0, 0);

	if(pDoc->m_report[index].referrer.size()){
		m_user_list.SetItem( nItem, 0, LVIF_IMAGE, "", 0, 0, 0, 0);
		m_user_list.SetItem( nItem, 2, LVIF_TEXT, pDoc->m_report[index].referrer.c_str(), 0, 0, 0, 0);
	}else if(pDoc->m_report[index].email.size()){
		m_user_list.SetItem( nItem, 0, LVIF_IMAGE, "", 2, 0, 0, 0);
		m_user_list.SetItem( nItem, 2, LVIF_TEXT, pDoc->m_report[index].email.c_str(), 0, 0, 0, 0);
	}else{
		if(pDoc->m_report[index].robot)
			m_user_list.SetItem( nItem, 0, LVIF_IMAGE, "", 3, 0, 0, 0);
		else
			m_user_list.SetItem( nItem, 0, LVIF_IMAGE, "", 1, 0, 0, 0);
	}

	m_user_list.SetItem( nItem, 3, LVIF_TEXT, pDoc->m_report[index].hostname.c_str(), 0, 0, 0, 0);
	m_user_list.SetItem( nItem, 4, LVIF_TEXT, pDoc->m_report[index].keyword.c_str(), 0, 0, 0, 0);
	m_user_list.SetItem( nItem, 5, LVIF_TEXT, pDoc->m_report[index].os.c_str(), 0, 0, 0, 0);
	m_user_list.SetItem( nItem, 6, LVIF_TEXT, pDoc->m_report[index].browser.c_str(), 0, 0, 0, 0);
	
	CString num; num.Format("%d",pDoc->m_report[index].detail.size());
	m_user_list.SetItem( nItem, 7, LVIF_TEXT, num, 0, 0, 0, 0);

	return 1;
}

void CClickReporterView::OnInsertitemUserList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	//#################################################
	// Set number of user
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
	pFrame->DisplayNumberOfUser(m_user_list.GetItemCount());

	//get pointer for doc
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();
	pFrame->ShowStatus(pDoc->m_analyze_status.c_str());

	*pResult = 0;
}

void CClickReporterView::OnSelchangeMonthcalendarFrom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    NMDAYSTATE* pDayState= (NMDAYSTATE *)pNMHDR;
    SYSTEMTIME date = pDayState->stStart;

	//save to registory
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("report","fyear",date.wYear);
	pApp->WriteProfileInt("report","fmonth",date.wMonth);
	pApp->WriteProfileInt("report","fday",date.wDay);
	
	*pResult = 0;
}

void CClickReporterView::OnSelchangeMonthcalendarTo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    NMDAYSTATE* pDayState= (NMDAYSTATE *)pNMHDR;
    SYSTEMTIME date = pDayState->stStart;

	//save to registory
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("report","tyear",date.wYear);
	pApp->WriteProfileInt("report","tmonth",date.wMonth);
	pApp->WriteProfileInt("report","tday",date.wDay);

	*pResult = 0;
}

void CClickReporterView::OnSetDate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnViewAll();
}

void CClickReporterView::OnSearchNoRobot() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	// delete all items from list
	m_user_list.DeleteAllItems();

	//get pointer for document
	CClickReporterDoc* pDoc = (CClickReporterDoc*)GetDocument();

	//set m_robot_view_status
	if(m_robot_view_status)
		m_robot_view_status = 0;
	else
		m_robot_view_status = 1;
	
	OnViewAll();

/*
		int flag;
		for(unsigned int i=0;i<pDoc->m_report.size();i++){
			flag = 0;

			if(pDoc->m_report[i].cnt >= 1){		
				//check way in page
				if(!pDoc->m_report[i].robot){
					AddToList(i);
				}
			}
		}

		//#################################################
		//get web_url from registory
		CWinApp* pApp = AfxGetApp();
		string web_url = pApp->GetProfileString("report","web_url");

		//#################################################
		// Set message on menu title
		CString msg;
		msg.Format(_T("%s [閲覧ページ：リファラ=%s]"),web_url.c_str(),m_search_referrer.c_str());

		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		pFrame->SetMyTitle(msg);	
	}
	*/
}

void CClickReporterView::OnUpdateSearchNoRobot(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->SetCheck(m_robot_view_status);
}

void CClickReporterView::OnSearchOnlyMail() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	// delete all items from list
	m_user_list.DeleteAllItems();

	//set m_mail_view_status
	m_mail_view_status = 1;
	
	OnViewAll();

	m_mail_view_status = 0;
	
}
