#include "Tools.h"
#include <windows.h>
#include <wininet.h>

/////////////////////////////////////////////////////////////////////////////
// Logging on Interlog Webserver
void GetLicenceFilePath(char* lfilename){
	::GetSystemDirectory(lfilename,256);
	strcat(lfilename,"\\at1.x.le");
}

/////////////////////////////////////////////////////////////////////////////
// Logging on Interlog Webserver
void Logging(LPCTSTR agent, LPCSTR logdata){

	HINTERNET hINet,hConnection,hData;
	string m_strContents;

	hINet = InternetOpen(agent,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);

	if(!hINet) return;

	hConnection = InternetConnect(hINet,"www.interlog.co.jp",INTERNET_DEFAULT_HTTP_PORT,"","",INTERNET_SERVICE_HTTP,0,0);

	if(!hConnection) return;
	
	//set path
	CString objname;
	objname.Format(_T("/send/index.html?%s"),logdata);

	hData = HttpOpenRequest(hConnection,"GET",objname,NULL,NULL,NULL,INTERNET_FLAG_KEEP_CONNECTION,0);

	if(!hData){
		InternetCloseHandle(hConnection);
		InternetCloseHandle(hINet);
		return;
	}

	HttpSendRequest(hData,NULL,0,NULL,0);

	InternetCloseHandle(hConnection);
	InternetCloseHandle(hINet);
	InternetCloseHandle(hData);
}

/////////////////////////////////////////////////////////////////////////////
// String Tokenizeer
int Tokenize(const string& str,vector<string>& tokens,const string& delimiter)
{
	int cnt = 0;

    // Skip delimiter at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiter, 0);
    // Find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiter, lastPos);

    while ((string::npos != pos && pos != 0) || string::npos != lastPos)
    {
		cnt++;
        // Found a token, add it to the vector.
		if(pos - lastPos == 1 && str.at(lastPos) == str.at(pos))
		{
			tokens.push_back("");
		}
		else
			tokens.push_back(str.substr(lastPos, pos - lastPos));

		if(str.find(delimiter,pos+1) == pos+1){
			lastPos = pos;
	        pos = str.find_first_of(delimiter, lastPos+1);
		}else{
			lastPos = str.find_first_not_of(delimiter, pos);
	        pos = str.find_first_of(delimiter, lastPos);
		}
    }
	return cnt;
}

string decode(const string& src)
{
	string t;
	string::const_iterator p = src.begin();
	while (p != src.end()) {
		if (*p == '%') {
			if (++p == src.end()) break;
			int d = *p;
            if (++p == src.end()) break;
			int e = *p;
			d = (d >= 'A') ? (d & 0xdf) - 'A' + 10 : d - '0';
			e = (e >= 'A') ? (e & 0xdf) - 'A' + 10 : e - '0';
			if (d >= 0 && d < 16 && e >= 0 && e < 16)
				t += char(16 * d + e);
		} else if (*p == '+') {
			t += ' ';
		} else if (*p == '&') {
			t += '\n';
		} else {
			t += *p;
		}
		p++;
	}

	return t;
}

string utf8tosjis(string src){
	string ret;			//for return
	char struni[2048];	//for unicode characters
	char strsjis[1024];	//for sjis characters

	//UTF-8 to Unicode
	//MultiByteToWideChar(CP_UTF8,0,src.c_str(),-1,(unsigned short *)struni,2048);
	MultiByteToWideChar(CP_UTF8,0,src.c_str(),-1,(LPWSTR)struni,2048);

	//Unicode to SJIS
	//WideCharToMultiByte(CP_ACP,0,(const unsigned short *)struni,-1,strsjis,sizeof(strsjis),NULL,NULL); 
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)struni,-1,strsjis,sizeof(strsjis),NULL,NULL); 

	ret = strsjis;	//char to string

	return ret;
}

string euctosjis(string src){
	CString str, strRet;	
	string ret;				//for ret
	BYTE ch1, ch2;			//character 1, 2
	WORD wcode;

	if(src.find("w3c") != string::npos)
		string mmm= ";;;";

	//string to CString
	str.Format(_T("%s\n"),src.c_str());

	for( int i = 0; i < str.GetLength(); i++){
		ch1 = str[i];
		
		if(ch1 == 0x8e){									//first byte is Hankaku Katakana
			ch2 = str[++i];
			//dump first byte
			strRet += ch2;
		}else if(ch1 == 0x20){								//first byte is space(32, 0x20)
			strRet += ' ';
		}else if(ch1 >= 0x20 && ch1 <= 0x7A){				//ASCII
			strRet += ch1;
		}else if(ch1^0x80 >= 0x21 && ch1^0x80 <= 0x7e){		//first byte is Kanji (0x21～0x7E)
			ch1 ^= 0x80;
			if(i+1 < str.GetLength())
				ch2 = str[++i] ^ 0x80;
			wcode = MAKEWORD( ch2, ch1);
			wcode = _mbcjistojms( wcode);	//jis to sjis
			strRet += HIBYTE( wcode);
			strRet += LOBYTE( wcode);
		}else
			strRet += ch1;
	}

	ret = strRet;
	return ret;
}

int getKeyword(string s, string var, string& key, string& url){
	int pos;

	vector <string> urls,paras;
	if(Tokenize(s,urls,"?")){			//split by ?
		
		if(urls.size() < 2)				//no keyword
			return 0;

		Tokenize(urls[1],paras,"&");	//split by &
		
		//get search engine url
		pos = urls[0].find_last_of("/");
		//url = urls[0].substr(0,pos);	//完全なリファラをブラウザで参照したいとのことで、コメントアウト
		url = s;
	}
			
	//get keyword
	for(int i=0;i<paras.size();i++)
		if(paras[i].find(var,0) != string::npos && paras[i].at(0) == var.at(0)){
			if((pos = paras[i].find("=")) != string::npos)
				key = decode(paras[i].substr(pos+1,paras[i].size()));
			return 1;
		}
	return 0;
}

int isInDateRange(string date_s){
	vector<string> d1;
	vector<string> d2;

	Tokenize(date_s,d1," ");		// separate by space
	Tokenize(d1[0],d2,"//");									// seprate by /

	// get time of a record
	CTime date_c(atoi(d2[0].c_str()), atoi(d2[1].c_str()), atoi(d2[2].c_str()), 0, 0, 0);
	time_t date_b = date_c.GetTime();				//seconds

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

	return 1;
}

int GetDatesToExpire(CString key)
{
	char line[1024];

	//############################
	// Get Expire Time
	//############################
	if(key.GetLength() <= 0){
		// set licence file path
		char lfilename[256];
		GetLicenceFilePath(lfilename);

		// open file
		CFile lfile(lfilename,CFile::modeRead);
		int l = lfile.Read(line,1024);
		line[l] = '\0';
		lfile.Close();
	}else{
		strcpy( line, key );
		line[key.GetLength()] = '\0';
	}

	// seperate line by : and get name and email expire
	CString name, email, expire_s;
	if(!(name = strtok(line,":"))) return -1000;		//name
	if(!(email = strtok(NULL,":"))) return -1000;		//email
	if(!(expire_s = strtok(NULL,":"))) return -1000;	//expire

	// decode expire
	CCipher* cipher = new CCipher(name,email,expire_s);
	if(cipher->decode() == FALSE) return -1000;

	// get expire time
	char buf_expire[256];
	sprintf(buf_expire,"%s",cipher->expire);

	//##############################
	// get year and month and day
	//##############################
	char *buf;
	
	//year
	if((buf = strtok(buf_expire,"/")) == NULL) return -1000;
	int yea = atoi(buf);

	//month
	if((buf = strtok(NULL,"/")) == NULL) return -1000;
	int mon = atoi(buf);

	//day
	if((buf = strtok(NULL,"/")) == NULL) return -1000;
	int day = atoi(buf);
	//##############################
	//##############################

	// make time_t structure for expire time
	if( mon > 12 || day > 31) return -1000;

	CTime expire(yea, mon, day, 0, 0, 0);
	time_t expire_b = expire.GetTime();

	// get current time
	CTime current = CTime::GetCurrentTime();
	time_t current_b = current.GetTime();		//seconds
	//############################
	//############################

	return (int)((double)(expire_b-current_b)/86400)+1;
}

int ifEUCJP(string str){

	int vote[2] = {0, 0};	//vote
	int code = -1;			//fix code index (EUC_JP or SJIS)
	int state = -1;			//fix state,
							//  -2  : highly possible or fix
							//  -1  : no doubt
							//   0- : doubtful index

	for(int i=0;i<str.size();i++){
			
		if( !(code==-1 || code==EUC_JP || code==SJIS) ||
			 (vote[EUC_JP]==-1 && vote[SJIS]==-1) )
			return code;

		//0x8E is an escape sequence for 半角カナ on EUC
		if((unsigned char)str.at(i) == 0x8E && i+1 < str.size() && (code == EUC_JP || code == -1) && vote[EUC_JP] == -1)
			if((unsigned char)str.at(i+1) >= 0xA1 && (unsigned char)str.at(i+1) <= 0xDF && (state != -2 || state == EUC_JP))
			{	//EUCJP
				vote[EUC_JP] ++;
				state = -2;
				i++;
				continue;	//EUCJP (Highly Possible)
			}
			else if((unsigned char)str.at(i+1) >= 0x80 && str.at(i+1) <= 0xA0 && vote[SJIS] != -1)
			{	//SJIS
				vote[SJIS]++;
				code=SJIS;
				state = -2;
				i+=2;
				return code;	//SJIS (FIX)
			}
			else
				continue;	//UNKNOW

		//0x8F is an escape sequence for 補助漢字 on EUC
		if((unsigned char)str.at(i) == 0x8F && i+2 < str.size() && (code == EUC_JP || code == -1) && vote[EUC_JP] != -1)
			
			if( (unsigned char)str.at(i+1) >= 0xA1 && (unsigned char)str.at(i+1) <= 0xFE &&
				(unsigned char)str.at(i+2) >= 0xA1 && (unsigned char)str.at(i+1) <= 0xFE )
			{
				vote[EUC_JP] ++;
				state = -2;

				if( (unsigned char)str.at(i+1) == 0xFD || (unsigned char)str.at(i+1) == 0xFE ||
					(unsigned char)str.at(i+2) == 0xFD || (unsigned char)str.at(i+2) == 0xFE )
				{	//0xFD 0xFE is 美乳 on EUC
					i+=2;
					code=EUC_JP;
					return code;	//EUC（FIX）
				}

				i++;
				continue;

			}
			else if((unsigned char)str.at(i+1) >= 0x80 && (unsigned char)str.at(i+1) <= 0xA0 && vote[SJIS] != -1)
			{	//SJIS
				vote[SJIS]++;
				code = SJIS;
				state = -2;
				i+=2;
				return code;	//SJIS (FIX)
			}
			else
				continue;		//UNKNOWN

		//
		else
		{
			if( (unsigned char)str.at(i) >= 0x80 && (unsigned char)str.at(i) <= 0xA0 && (code == SJIS || code == -1) && vote[SJIS] != -1 )
			{	//SJIS
				code = SJIS;
				state = -2;
				i++;
				return code;	//SJIS (FIX)
			}
			else if( (unsigned char)str.at(i) >= 0xA1 && (unsigned char)str.at(i) <= 0xDF &&
				    (code == -1 || code == SJIS) &&
					(state != -2 || state == SJIS) &&
					vote[SJIS] != -1)
			{ //SJIS 半角カナ
				if(i+1 < str.size())
				{
					if( (unsigned char)str.at(i) == 0xA4 && ( (unsigned char)str.at(i+1) >= 0xA1 && str.at(i+1) <= 0xF3 ) ||
						(unsigned char)str.at(i) == 0xA5 && ( (unsigned char)str.at(i+1) >= 0xA1 && str.at(i+1) <= 0xF6 && vote[EUC_JP] != -1) )
					{
						//on EUC, A4+? is かな and A5+? is カナ
						//A4 + A1 <= ? >= F3
						//A5 + A1 <= ? >= F6
						vote[EUC_JP] ++;
						code = EUC_JP;
						i+=2;
						continue; //EUC全角カナの可能性
					}
					else if( (unsigned char)str.at(i+1) >= 0xE0 && (unsigned char)str.at(i+1) <= 0xFE && vote[EUC_JP] != -1 )
					{	//{//SJIS半角カナ以外でのEUC範囲がでたためEUC
						vote[EUC_JP] ++;
						state = -2;
						if(str.length()-1 >= i+2){
							if( ((unsigned char)str.at(i+1) == 0xFD || (unsigned char)str.at(i+1) == 0xFE) || 
								((unsigned char)str.at(i+2) == 0xFD || (unsigned char)str.at(i+2) == 0xFE))
							{	//0xFD 0xFE EUC美乳
								i+=2;
								code = EUC_JP;
								return EUC_JP;	//EUC_JP (FIX)
							}
						}
						i++;
						continue;	//EUC_JP (Highly Possible)
					}
					else
					{	//except EUC, SJIS半角 is highly possible
						vote[SJIS]++;
						state = -2;
						i++;
						continue;	//SJIS (Highly Possible)
					}
				}
				else
				{	//SJIS Highly Possible
					vote[SJIS]++;
					state = -2;
					i++;
					continue;	//SJIS (Highly possible)
				}
			}	
			else if( (unsigned char)str.at(i) >= 0xA1 && (unsigned char)str.at(i) <= 0xFE &&
					 (code == EUC_JP || code == -1) &&
					 vote[EUC_JP] != -1)
			{	//EUC
				vote[EUC_JP] ++;
				state = -2;

				if((unsigned char)str.at(i) == 0xFD || (unsigned char)str.at(i) == 0xFE)
				{	//0xFD 0xFE EUC美乳
					code = EUC_JP;
					return code;
				}

				i++;
				continue;
			}
			else
				continue;
		}
	}

	if(vote[EUC_JP] > vote[SJIS])
		return EUC_JP;
	else if(vote[EUC_JP] < vote[SJIS])
		return SJIS;
	else
		return -1;
}

BOOL ifUTF8(string str){

	for(int i=0;i<str.size();i++){
			
		unsigned char cich = str.at(i);				//current index character

		if(cich >= 0x20 && cich <= 0x7E)					//ASCII
			continue;

		if(cich >= 0xC2 && cich <= 0xFD)					//UTF-8
		{													//the range of character at 1 byte is |0xC2, 0xFD|
			//check number of bytes
			int nbyte = 1;
			if((cich & 0xFC) == 0xFC)		//6byte
				nbyte = 6;
			else if((cich & 0xF8) == 0xF8)	//5byte
				nbyte = 5;
			else if((cich & 0xF0) == 0xF0)	//4byte
				nbyte = 4;
			else if((cich & 0xE0) == 0xE0)	//3byte
				nbyte = 3;
			else if((cich & 0xC0) == 0xC0)	//2byte
				nbyte = 2;

			//####################################
			//after 1 byte, the range is |0x80, 0xBF|
			int flag = 1;
			unsigned char afc;

			for(int j=1;j<nbyte;j++){
				if(i+j < str.size())
					afc = str.at(i+j);			//after first character
				else							//over length of str
					return false;

				if(afc < 0x80 || afc > 0xBF)	//|0x80, 0xBF|
					flag = 0;
			}
			//#####################################

			//guaranteed with UTF 8 
			if(flag)
				return true;

			i+=nbyte;
		}else
			return false;
	}
	return false;
}