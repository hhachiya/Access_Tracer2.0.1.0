// ClickReporterDoc.cpp : CClickReporterDoc クラスの動作の定義を行います。
//
#include "stdafx.h"
#include "ClickReporter.h"

#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "ReportExecTheadParam.h"
#include "LICENCE.h"
#include "Tools.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClickReporterDoc

IMPLEMENT_DYNCREATE(CClickReporterDoc, CDocument)

BEGIN_MESSAGE_MAP(CClickReporterDoc, CDocument)
	//{{AFX_MSG_MAP(CClickReporterDoc)
	ON_COMMAND(ID_REPORT_EXEC, OnReportExec)
	ON_COMMAND(ID_RESOLVE_HOSTNAME, OnResolveHostname)
	ON_COMMAND(ID_STOP_DATA_ANALYZE, OnStopDataAnalyze)
	ON_COMMAND(ID_FILE_SAVE_ONLY_SHOWN, OnFileSaveOnlyShown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickReporterDoc クラスの構築/消滅

CClickReporterDoc::CClickReporterDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。
	m_save_only_shown = 0;
}

CClickReporterDoc::~CClickReporterDoc()
{
}

BOOL CClickReporterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	//get view
	POSITION posv = GetFirstViewPosition();
	CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);

	//clear all data
	if(pView->m_user_list){
		pView->m_user_list.DeleteAllItems();
		m_report.clear();
		
		//set number of user
		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		pFrame->DisplayNumberOfUser(0);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CClickReporterDoc シリアライゼーション
void CClickReporterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
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
		// loop as number of row

		if(m_save_only_shown){
			//get view
			POSITION posv = GetFirstViewPosition();
			CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);

			for(int i = 0; i < pView->m_user_list.GetItemCount(); i++ ) {
				string key0 = pView->m_user_list.GetItemText(i,1);
				string key1 = pView->m_user_list.GetItemText(i,3);

				for(int j=0;j<m_report.size();j++){
					if(!m_report[j].detail[0].date.compare(key0) && !m_report[j].hostname.compare(key1)){

						CString line;
						line.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\r\n",
							m_report[j].detail[0].date.c_str(),
							m_report[j].detail[0].path.c_str(),
							m_report[j].email.c_str(),
							m_report[j].referrer.c_str(),
							m_report[j].hostname.c_str(),
							m_report[j].keyword.c_str(),
							m_report[j].os.c_str(),
							m_report[j].browser.c_str(),
							m_report[j].cnt
						);
						ar.WriteString(line);

						for(int k=1;k<m_report[j].detail.size();k++){
							line.Format("%s\t%s\r\n",
								m_report[j].detail[k].date.c_str(),
								m_report[j].detail[k].path.c_str()
							);					
							ar.WriteString(line);
						}

						break;
					}
				}
			}
		}else{
			for(int i=0;i<m_report.size();i++){
				CString line;

				//#################################
				// 
				line.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\r\n",
					m_report[i].detail[0].date.c_str(),
					m_report[i].detail[0].path.c_str(),
					m_report[i].email.c_str(),
					m_report[i].referrer.c_str(),
					m_report[i].hostname.c_str(),
					m_report[i].keyword.c_str(),
					m_report[i].os.c_str(),
					m_report[i].browser.c_str(),
					m_report[i].cnt
				);

				ar.WriteString(line);
				//#################################

				//#################################
				// pages
				for(int j=1;j<m_report[i].detail.size();j++){
					line.Format("%s\t%s\r\n",
						m_report[i].detail[j].date.c_str(),
						m_report[i].detail[j].path.c_str()
					);
				
					ar.WriteString(line);
				}
				//#################################
			}
		}
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
		//######################
		int fyear, fmonth, fday;
		int tyear, tmonth, tday;

		m_report.clear();

		CString line;				//line buffer
		vector <string> tokens;		//tokens buffer

		while(ar.ReadString(line)){	//read lines
			tokens.clear();			//tokenize each line by tab "\t"
			if(Tokenize((string)line,tokens,"\t")){
				if(tokens.size() > 2)
					if(tokens.size() > 9) //for robot
						m_report.push_back(CReport(tokens[0].c_str(),tokens[1].c_str(),tokens[2].c_str(),tokens[3].c_str(),tokens[4].c_str(),tokens[5].c_str(),tokens[6].c_str(),tokens[7].c_str(),atoi(tokens[9].c_str())));
					else
						m_report.push_back(CReport(tokens[0].c_str(),tokens[1].c_str(),tokens[2].c_str(),tokens[3].c_str(),tokens[4].c_str(),tokens[5].c_str(),tokens[6].c_str(),tokens[7].c_str(),0));
				else{
					m_report[m_report.size()-1].cnt ++;
					m_report[m_report.size()-1].detail.push_back(CReportDetail(tokens[0].c_str(),tokens[1].c_str()));
				}
			}

		}

		//convert time format from webtime to softime
		vector<int> ntime;

		if(m_report.size()){
			//set the time for the calendar
			GetNumTimeFromSofTime(m_report[0].detail[0].date,ntime);
			fyear = ntime[0];
			fmonth = ntime[1];
			fday = ntime[2];

			//set the time for the calendar
			GetNumTimeFromSofTime(m_report[m_report.size()-1].detail[0].date,ntime);
			tyear = ntime[0];
			tmonth = ntime[1];
			tday = ntime[2];

			// set the calendar
			// set ctime
			CTime fdate(tyear, tmonth, tday, 0, 0, 0);
			CTime tdate(tyear, tmonth, tday, 0, 0, 0);

			//save to registory
			CWinApp* pApp = AfxGetApp();
			pApp->WriteProfileInt("report","fyear",tyear);
			pApp->WriteProfileInt("report","fmonth",tmonth);
			pApp->WriteProfileInt("report","fday",tday);

			pApp->WriteProfileInt("report","tyear",tyear);
			pApp->WriteProfileInt("report","tmonth",tmonth);
			pApp->WriteProfileInt("report","tday",tday);

			//get view
			POSITION posv = GetFirstViewPosition();
			CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);
			pView->m_date_from_calendar.SetCurSel(fdate);
			pView->m_date_to_calendar.SetCurSel(tdate);

			//表示可能な日付を表示
			CString drange;
			drange.Format(_T("%04d年%02d月%02d日から\n%04d年%02d月%02d日まで"),fyear,fmonth,fday,tyear,tmonth,tday);
			pView->m_daterange.SetWindowText(drange);

			//reset m_robot_view_status
			pView->m_robot_view_status = 0;
		}
		//######################
	}
}


/////////////////////////////////////////////////////////////////////////////
// CClickReporterDoc クラスの診断

#ifdef _DEBUG
void CClickReporterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClickReporterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClickReporterDoc コマンド

void CClickReporterDoc::OnReportExec() 
{
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

	//App pointer
	CClickReporterApp* m_App = (CClickReporterApp*)AfxGetApp();

	// Get Frame Pointer
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();

	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//get view
	POSITION posv = GetFirstViewPosition();
	CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);

	//#####################################################
	// PREPARATION OF PARAMETERS FOR DOWNLOADING LOG FILES

	//get url from ini file
    CWinApp* pApp = AfxGetApp();
	string fqdn = pApp->GetProfileString("log", "url");
	string lpath = pApp->GetProfileString("log", "local_path");
	CString user_id = pApp->GetProfileString("log", "user_id");
	CString password = pApp->GetProfileString("log", "password");
	int log_place = pApp->GetProfileInt("log","log_place",0);
	string web_url = pApp->GetProfileString("report", "web_url");
	int session_timeout = pApp->GetProfileInt("report","session_timeout",0);
	CString top_page = pApp->GetProfileString("report","top_page");

	//check fqdn and lpath
	if(!fqdn.size() && !lpath.size()){
		AfxMessageBox("ログファイルパスまたはURLを設定してから、もう一度実行して下さい。");
		return;
	}

	//log_place = 0 : local disk
	//            1 : remote disk (through http)
	if(log_place){

		//eliminate "http://" from fqdn
		string::size_type pos;
		if((pos = fqdn.find_first_not_of("http://",0)) != string::npos)
			fqdn = fqdn.substr(pos,fqdn.length());

		//find first slash and split fqdn into url and path
		string path;
		string url;

		if((pos = fqdn.find_first_of("/",0)) != string::npos){
			url = fqdn.substr(0,pos);
			path = fqdn.substr(pos,fqdn.size());
		}else{
			url = fqdn;
			path = "/";
		}

		if(!url.size()){
			AfxMessageBox("ログファイルURLが正しく設定されていません。ご確認下さい。");
			return;
		}

		//################################
		//# INTERNET STUFF
		//################################
		HINTERNET hINet,hConnection,hData;

		// show status
		pFrame->ShowStatus("サーバへ接続しています");

		hINet = InternetOpen("AccessTracer 1.3",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);

		if(hINet == NULL){
			AfxMessageBox("サーバへの接続に失敗しました。");
			pFrame->ShowStatus("");
			return;
		}

		hConnection = InternetConnect(hINet,url.c_str(),INTERNET_DEFAULT_HTTP_PORT,"","",INTERNET_SERVICE_HTTP,0,0);

		if(hConnection == NULL){
			InternetCloseHandle(hINet);
			AfxMessageBox("サーバへの接続に失敗しました。");
			pFrame->ShowStatus("");
			return;
		}
		
		if( user_id.GetLength() || password.GetLength() ){
			if(!InternetSetOption( hConnection, INTERNET_OPTION_USERNAME, (LPVOID)(LPCSTR)user_id, user_id.GetLength() )){
				InternetCloseHandle(hConnection);
				InternetCloseHandle(hINet);
				AfxMessageBox("認証設定に失敗しました。");
				pFrame->ShowStatus("");
				return;
			}

			if(!InternetSetOption( hConnection, INTERNET_OPTION_PASSWORD, (LPVOID)(LPCSTR)password, password.GetLength() )){
				InternetCloseHandle(hConnection);
				InternetCloseHandle(hINet);
				AfxMessageBox("認証設定に失敗しました。");
				pFrame->ShowStatus("");
				return;
			}
		}
	
		// show status
		pFrame->ShowStatus("ログファイルをダウンロードしています");

		//HINTERNET HttpOpenRequest(IN HINTERNET hHttpSession,IN LPCSTR lpszVerb,
		//IN LPCSTR lpszObjectName,IN LPCSTR lpszVersion,IN LPCSTR lpszReferer,
		//IN LPCSTR FAR * lpszAcceptTypes,IN DWORD dwFlags,IN DWORD dwContext);
		//hData = HttpOpenRequest(hConnection,"HEAD",path,"HTTP/1.0",NULL,NULL,INTERNET_FLAG_KEEP_CONNECTION,0);
		hData = HttpOpenRequest(hConnection,"GET",path.c_str(),NULL,NULL,NULL,INTERNET_FLAG_RELOAD,0);
	
		if(!hData){
			InternetCloseHandle(hConnection);
			InternetCloseHandle(hINet);
			AfxMessageBox("ダウンロードに失敗しました。");
			pFrame->ShowStatus("");
			return;
		}
	
		//
		HttpSendRequest(hData,NULL,0,NULL,0);

		// get status code
		DWORD status_code;
		DWORD size = sizeof(status_code);
	
		if(!HttpQueryInfo(hData,HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,(LPVOID)&status_code,&size,NULL)){
			InternetCloseHandle(hConnection);
			InternetCloseHandle(hINet);
			AfxMessageBox("ステータスコードが取得できませんでした。");
			pFrame->ShowStatus("");
			return;
		}

		if( status_code == HTTP_STATUS_DENIED ){
			InternetCloseHandle(hConnection);
			InternetCloseHandle(hINet);
			AfxMessageBox("認証に失敗しました。");
			pFrame->ShowStatus("");
			return;
		}

		if( status_code == HTTP_STATUS_NOT_FOUND ){
			InternetCloseHandle(hConnection);
			InternetCloseHandle(hINet);
			AfxMessageBox("ログファイルが見つかりません。");
			pFrame->ShowStatus("");
			return;
		}

		//
		char content_length[100];
		size = sizeof(content_length);
		int size_downloaded = 0;
		int content_length_left;

		if(HttpQueryInfo(hData,HTTP_QUERY_CONTENT_LENGTH,content_length,&size,NULL)){
			content_length[size] = '\0';
		}else{
			InternetCloseHandle(hConnection);
			InternetCloseHandle(hINet);
			AfxMessageBox("サーバへの接続に失敗しました。");
			//AfxMessageBox("ログファイルサイズを取得できませんでした。");
			pFrame->ShowStatus("");
			return;
		}

		// show status
		pFrame->ShowStatus("ログファイルのダウンロードに成功しました");

		// the size of content
		content_length_left = atoi(content_length);

		//Logging
		CString logdata;
		logdata.Format(_T("Apr=AccessTracer1.2&URL=http://%s%s"),url.c_str(),path.c_str());
		Logging("AccessTracer 1.2",logdata);

		// show status
		pFrame->ShowStatus("ログファイルを展開しています");

		//download data
		char buffer[10240];
		DWORD dwRead;

		m_data = "";


		//#######################
		//To speed up, save data to file temporarily
		CFile dlFile;
		CFileException fileException;

		::GetSystemDirectory(m_filename,256);
		strcat(m_filename,"\\at.log");

		if(!dlFile.Open(m_filename,CFile::modeCreate | CFile::modeWrite,&fileException)){
			AfxMessageBox("ログファイルを開けません。");
			return;
		}else
			// show status
			pFrame->ShowStatus("ログファイルを保存しています");
		//#######################

		while(InternetReadFile(hData,buffer,10239,&dwRead)){
			if(dwRead == 0)
				break;
			buffer[dwRead] = '\n';
			//m_data += buffer;
			dlFile.Write(buffer,10239);

			content_length_left -= dwRead;

			//set progress status
			m_App->m_wndProgressCtrl->SetPos((int)((1 - (double)content_length_left/atoi(content_length))*100));
		}

		// show status
		pFrame->ShowStatus("インターネットの接続を閉じます");

		//close
		InternetCloseHandle(hConnection);
		InternetCloseHandle(hINet);
		InternetCloseHandle(hData);

	}else{

		//################################
		//# FILE STUFF
		//################################
		strcpy(m_filename,lpath.c_str());
/*		
		CFile myFile;
		CFileException fileException;
		if(!myFile.Open(lpath.c_str(),CFile::modeRead,&fileException)){
			AfxMessageBox("ログファイルを開けません。");
		}else
			// show status
			pFrame->ShowStatus("ログファイルを開いています");

		char buffer[10240];
		DWORD dwRead;

		m_data = "";
		while((dwRead = myFile.Read(buffer,10239))){
			buffer[dwRead] = '\0';
			m_data += buffer;
		}
		myFile.Close();
*/
	}

	pFrame->ShowStatus("ログファイルを分析しています");

	//clear m_report and list
	m_report.clear();
	
	pView->m_user_list.DeleteAllItems();

	//set progress status
	m_App->m_wndProgressCtrl->SetPos(0);
	
	//set title
	pFrame->SetMyTitle(web_url.c_str());

	//reset m_robot_view_status
	pView->m_robot_view_status = 0;

	//####################################
	//## Analyze data
	//####################################
	m_data_analyze_flag = 1;
	CReportExecTheadParam* _param = new CReportExecTheadParam(this, m_App, pView);
	AfxBeginThread(AccessDataAnalyzeThread, _param);
}

string CClickReporterDoc::decURL(int seed, const char *table, string crypted)
{
	int  len = (table ? strlen(table) : 0);
	char TheString[1024];
	memset(TheString,0,1024);
	strcpy(TheString, crypted.c_str());
	
	char* pp = TheString;

	if ( *pp == '%' ) {
		while( *++pp ) {
			if ( len ) {
				for ( int i=0; i<len; i++ ) {
					if ( *pp == table[i] ) {
						*pp = i + seed + 0x21;
						break;
					}
				}
			}else {
				if ( *pp == 0x5f ) *pp = 0x55;
				else if ( *pp >= 0x61 ) *pp -= 0x0b;
				else if ( *pp >= 0x40 ) *pp -= 0x06;
			}
		}

		//pack( 0 );
		for(int i=0;i<strlen(TheString);i++){
			if(TheString[i] == '%' || TheString[i] == 0){
				for(int j=i;j<strlen(TheString)-1;j++)
					TheString[j] = TheString[j+1];
				TheString[strlen(TheString)-1] = 0x00;
			}else{
				break;
			}
		}
		decrypt( seed, TheString );
		string decrypted = TheString;
		return decrypted;
	}
	return crypted;
}

void CClickReporterDoc::decrypt(int seed, char *TheString)
{
	char* pp = TheString;
	char* qq = TheString;
	char base = 0x20 + seed;
	char c1, c2;
	while ( (c1=*pp++) ) {
		c2 = *pp++;
		if ( ++base == 0x70-seed ) base = 0x21 + seed;

		*qq++ = ( (c1 - (0x9f-seed-base) ) << 4 ) + ( c2 - base );
	}
	*qq = 0x00;
}


int CClickReporterDoc::month_text2num(string month)
{
	string month_texts[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	for(int i=0;i<12;i++)
		if(!month.compare(month_texts[i]))
			return i+1;
	return 0;
}

int CClickReporterDoc::GetTimeDifference(string stime1, string stime2)
{
	//
	// an example of the format of time1 and time2
	// 28/Jun/2004:15:13:54
	//
	vector<int> ntime;

	//##############################
	// get numeric time from stime1
	GetNumTimeFromSofTime(stime1, ntime);

	//CTime time(year, month, day, hour, minute, second)
	CTime ctime1(ntime[0],ntime[1],ntime[2],ntime[3],ntime[4],ntime[5]);
	time_t time1 = ctime1.GetTime();


	//clear
	ntime.clear();

	//##############################
	// get numeric time from stime2
	GetNumTimeFromSofTime(stime2, ntime);

	//CTime time(year, month, day, hour, minute, second)
	CTime ctime2(ntime[0],ntime[1],ntime[2],ntime[3],ntime[4],ntime[5]);
	time_t time2 = ctime2.GetTime();

	return (int)(time1-time2);

}

int CClickReporterDoc::GetNumTimeFromWebTime(string webtime, vector<int> &numtime)
{
	//
	vector<string> d1;
	vector<string> d2;

	//##############################
	// get numeric time from stime1
	Tokenize(webtime,d1,"//");		// separate by /
	if(d1.size() < 3) return 0;
	Tokenize(d1[2],d2,":");			// seprate by :
	if(d2.size() < 4) return 0;

	numtime.push_back(atoi(d2[0].c_str()));		//year
	numtime.push_back(month_text2num(d1[1]));	//month
	numtime.push_back(atoi(d1[0].c_str()));		//day
	numtime.push_back(atoi(d2[1].c_str()));		//hour
	numtime.push_back(atoi(d2[2].c_str()));		//minute
	numtime.push_back(atoi(d2[3].c_str()));		//second

	return 1;
}

void CClickReporterDoc::GetNumTimeFromSofTime(string softime, vector<int> &numtime)
{
	//
	vector<string> d1;
	vector<string> d2;
	vector<string> d3;

	//##############################
	// get numeric time from stime1
	Tokenize(softime,d1," ");	// separate by Space into day and time
	Tokenize(d1[0],d2,"//");		// separate by / into year and month and day
	Tokenize(d1[1],d3,":");		// seprate by : into hour and minute and second


	numtime.push_back(atoi(d2[0].c_str()));		//year
	numtime.push_back(atoi(d2[1].c_str()));		//month
	numtime.push_back(atoi(d2[2].c_str()));		//day
	numtime.push_back(atoi(d3[0].c_str()));		//hour
	numtime.push_back(atoi(d3[1].c_str()));		//minute
	numtime.push_back(atoi(d3[2].c_str()));		//second
}


void CClickReporterDoc::OnResolveHostname() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//App pointer
	CClickReporterApp* m_App = (CClickReporterApp*)AfxGetApp();

	// Get Frame Pointer
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();

	//get view
	POSITION posv = GetFirstViewPosition();
	CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);

	//set progress status
	m_App->m_wndProgressCtrl->SetPos(0);

	//set number
	pFrame->DisplayNumberOfUser(m_report.size());

	//set status
	pFrame->ShowStatus("ホスト名を解決する準備をしています");

	m_data_analyze_flag = 2;

	CReportExecTheadParam* _param = new CReportExecTheadParam(this, m_App, pView);
	AfxBeginThread(HostnameResolveThread, _param);
}

UINT CClickReporterDoc::HostnameResolveThread (LPVOID param)
{
    CReportExecTheadParam* p = (CReportExecTheadParam*)param;

	p->m_Doc->m_analyze_status = "ホスト名を解決しています";

	WSADATA wsaData;
 	WORD wVersionRequested = MAKEWORD(1,1);

	if(WSAStartup(wVersionRequested,&wsaData) != 0)
		AfxMessageBox("WinSock DLLが見つかりません。");
	else{
		p->m_View->m_user_list.DeleteAllItems();

		unsigned long longaddr;

		for(int i=0; i< p->m_Doc->m_report.size(); i++){
			if(!p->m_Doc->m_data_analyze_flag)
				break;

			//**********************
			// date range check
			if(!isInDateRange(p->m_Doc->m_report[i].detail[0].date)){
				//AfxMessageBox(p->m_Doc->m_report[i].detail[0].date.c_str());
				continue;
			}
			//**********************
			
			longaddr = inet_addr(p->m_Doc->m_report[i].hostname.c_str());
			struct hostent *host;
			host = gethostbyaddr(reinterpret_cast<char *>(&longaddr),4,AF_INET);
			
			if(host != NULL){
				if(host->h_name != NULL)
					p->m_Doc->m_report[i].hostname = host->h_name;
			}

			if(i == p->m_Doc->m_report.size()-1)
				p->m_Doc->m_analyze_status = "";

			//
			p->m_View->AddToList(i);

			//set progress status
			p->m_App->m_wndProgressCtrl->SetPos((int)((1 - (double)(p->m_Doc->m_report.size()-i)/p->m_Doc->m_report.size())*100));
		}
	}

	//set progress status
	p->m_App->m_wndProgressCtrl->SetPos(0);
	p->m_Doc->m_data_analyze_flag = 0;

    return 1;
}

UINT CClickReporterDoc::AccessDataAnalyzeThread (LPVOID param)
{
    CReportExecTheadParam* p = (CReportExecTheadParam*)param;
	// Get Frame Pointer

	int session_timeout = p->m_App->GetProfileInt("report","session_timeout",0);
	CString top_page = p->m_App->GetProfileString("report","top_page");

	//
//	vector <string> line;		//seprated by new line
	vector <string> data_sp;	//seprated by space
	vector <string> data_dq;	//separated by double quatation

	//acquire lines
//	Tokenize(p->m_Doc->m_data,line,"\n");

	//clear m_report
	p->m_Doc->m_report.clear();

	//set progress status
	//なぜかエラーがでるのでコメントアウト
	//	p->m_App->m_wndProgressCtrl->SetPos(0);

	//#######################
	//To speed up, save data to file temporarily
	CFile dlFile;
	CFileException fileException;

	if(!dlFile.Open(p->m_Doc->m_filename,CFile::modeRead,&fileException)){
		AfxMessageBox("ログファイルを開けません。");
		return 1;
	}
	CArchive ar(&dlFile, CArchive::load);

	//#######################

	int fyear, fmonth, fday;
	int tyear, tmonth, tday;
	CString buffer;
	string line;
	int cnt = 0;

	int length = dlFile.GetLength();
	int opened = 0;

	while(ar.ReadString(buffer)){	//read lines
		line = buffer;
		
		if(buffer.GetLength()<1)
			break;

		opened += buffer.GetLength();

		if(!p->m_Doc->m_data_analyze_flag)
			break;

		//replace "" into "-"
		int pos = 0;
		while((pos = line.find("\"\"",pos)) != string::npos)
			line.insert(pos+1,"-");

		//clear old data
		data_sp.clear();
		data_dq.clear();

		//separate each line by some character
		// data_sp
		// 0  : hostname	ex) 211.128.246.118
		// 2  : user id
		// 3  : date		ex) [01/Apr/2004:16:38:40
		// 4  : date2		ex) +0900]
		// 5  : request		ex) "GET
		// 6  : path		ex) /index.html
		// 7  : protocol	ex) HTTP/1.1"
		// 10 : referer		ex) "http://www.yahoo.co.jp"
		// 11 : client1		ex) "Mozilla/4.0 
		// 12 : client2		ex) (compatible;
		// 13 : client3		ex) MSIE
		//................
		// data_dq
		// 1 : request	ex) GET /index.html HTTP/1.1
		// 5 : client	ex) Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)

		Tokenize(line,data_sp," ");
		Tokenize(line,data_dq,"\"");

		int b = data_sp.size();
		int d = data_dq.size();
		string liddd = line;
		string lidfdmm = data_sp[0];

		// check if data_sp[0] is hostname or ip address
		// check if data_sp[3] contains [
		// check if data_dq is correctly given
		if(data_sp[0].size() < 2 || data_sp[3].find("[") == string::npos || data_dq.size() < 6)
			continue;

		//######################################
		// Embroidery of User id (data_sp[2])
		//
		//decrypt email address
		data_sp[2] = p->m_Doc->decURL(15,NULL,data_sp[2]);

		//eliminate - from data_sp[2]
		if((pos = data_sp[2].find("-")) != string::npos && data_sp[2].size() < 2)
			data_sp[2].replace(pos,1,"");
		//######################################

		//######################################
		// Embroidery of Time (data_sp[3])
		//
		//eliminate dust character like ] and " from the data
		data_sp[3].replace(0,1,"");	//data_sp[3] indicates the time when client accessed

		//convert time format from webtime to softime
		vector<int> ntime;
		if(!p->m_Doc->GetNumTimeFromWebTime(data_sp[3],ntime)) continue;
		CString ctime;
		ctime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),ntime[0],ntime[1],ntime[2],ntime[3],ntime[4],ntime[5]);

		//set the start time for the calendar
		if(!p->m_Doc->m_report.size()){
			fyear = ntime[0];
			fmonth = ntime[1];
			fday = ntime[2];
		}

		//set the end time of the calender
		tyear = ntime[0];
		tmonth = ntime[1];
		tday = ntime[2];

		//set softime at data_sp[3]
		//data_sp[3] = "";
		data_sp[3].erase();
		data_sp[3] += ctime;
		//######################################

		//######################################
		// Embroidery of Referrer (data_sp[10])
		//eliminate " from data_sp[10]
		data_sp[10].replace(0,1,"");
		if(data_sp[10].size() > 1)
			data_sp[10].replace(data_sp[10].size()-1,1,"");

		//eliminate - from data_sp[10]
		if((pos = data_sp[10].find("-")) != string::npos && data_sp[10].size() < 2)
			data_sp[10].replace(pos,1,"");
		//######################################

		//######################################
		// Embroidery of Path (data_sp[6])
		//if(data_sp[6].size() == 1 && (pos = data_sp[6].find("/")) != string::npos)
		//	data_sp[6] += top_page;

		if( data_sp[6].find(".html") == string::npos &&
			data_sp[6].find(".htm") == string::npos  &&
			data_sp[6].find(".shtml") == string::npos &&
			data_sp[6].find(".cgi") == string::npos  &&
			data_sp[6].find(".php") == string::npos &&
			data_sp[6].find(".xml") == string::npos &&
			data_sp[6].find(".xhtml") == string::npos &&
			data_sp[6].find(".jsp") == string::npos &&
			data_sp[6].find(".asp") == string::npos &&
			data_sp[6].find(".cfm") == string::npos &&
			data_sp[6].find(".swf") == string::npos &&
			data_sp[6].find("?") == string::npos &&
			data_sp[6].at(data_sp[6].size()-1) != '/'
		  )
			continue;
		//######################################

		int flag = 0;

		//to speed up, reduce the comparison
		int start = p->m_Doc->m_report.size() - 100;
		if(start < 0) start = 0;
		
		for(unsigned int j=start;j<p->m_Doc->m_report.size();j++){
			//check if there already is the data which has the same hostname and agent
			//furthermore, check if the difference in time is less than session_timeout
			if(!p->m_Doc->m_report[j].hostname.compare(data_sp[0]) && !p->m_Doc->m_report[j].agent.compare(data_dq[5]) && p->m_Doc->GetTimeDifference(data_sp[3], p->m_Doc->m_report[j].detail[p->m_Doc->m_report[j].cnt-1].date) < session_timeout){
				p->m_Doc->m_report[j].cnt++;
				p->m_Doc->m_report[j].detail.push_back(CReportDetail(data_sp[3],data_sp[6]));
				flag = 1;
			}
		}

		if(!flag)
			p->m_Doc->m_report.push_back(CReport(data_sp[2],data_sp[0],data_dq[5],data_sp[3],data_sp[6],data_sp[10]));
		
		//set progress status
		//p->m_App->m_wndProgressCtrl->SetPos((int)((1 - (double)(line.size()-i)/line.size())*100));
		p->m_App->m_wndProgressCtrl->SetPos((int)((1 - (double)(length-opened)/length)*100));
	}

	//######################
	//set the calendar
	// set ctime
	CTime fdate(tyear, tmonth, tday, 0, 0, 0);
	CTime tdate(tyear, tmonth, tday, 0, 0, 0);

	//save to registory
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("report","fyear",tyear);
	pApp->WriteProfileInt("report","fmonth",tmonth);
	pApp->WriteProfileInt("report","fday",tday);

	pApp->WriteProfileInt("report","tyear",tyear);
	pApp->WriteProfileInt("report","tmonth",tmonth);
	pApp->WriteProfileInt("report","tday",tday);

	p->m_View->m_date_from_calendar.SetCurSel(fdate);
	p->m_View->m_date_to_calendar.SetCurSel(tdate);

	//表示可能な日付を表示
	CString drange;
	drange.Format(_T("%04d年%02d月%02d日から\n%04d年%02d月%02d日まで"),fyear,fmonth,fday,tyear,tmonth,tday);
	p->m_View->m_daterange.SetWindowText(drange);
	//######################

	p->m_Doc->m_analyze_status = "";

	//list up!!
	p->m_View->OnViewAll();
	int view_cnt = p->m_View->view_cnt;
	//int view_cnt =p->m_View->OnViewAll();

	// show the simple result
	CString msg;
	msg.Format("訪問者%d人のページ遷移が確認できました。\nその内一日分の%d件を表示しました。",p->m_Doc->m_report.size(),view_cnt);
	AfxMessageBox(msg);

	//set progress status
	p->m_App->m_wndProgressCtrl->SetPos(0);

	p->m_Doc->m_data_analyze_flag = 0;

	return 0;
}

void CClickReporterDoc::OnStopDataAnalyze() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if(!m_data_analyze_flag) return;


	// Get Frame Pointer
	CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();

	//set status
	pFrame->ShowStatus("");
	switch(m_data_analyze_flag){
	case 1:
		m_analyze_status = "解析を停止しました";
		break;
	case 2:
		m_analyze_status = "ホスト名の解決を停止しました";
		break;
	}

	m_data_analyze_flag = 0;

	//App pointer
	CClickReporterApp* m_App = (CClickReporterApp*)AfxGetApp();

	//set progress status
	m_App->m_wndProgressCtrl->SetPos(0);

	//get view
	POSITION posv = GetFirstViewPosition();
	CClickReporterView* pView = (CClickReporterView*)this->GetNextView(posv);

	pView->m_user_list.DeleteAllItems();
	pView->OnViewAll();

}


void CClickReporterDoc::OnFileSaveOnlyShown() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	m_save_only_shown = 1;
	OnFileSaveAs();
	m_save_only_shown = 0;
}
