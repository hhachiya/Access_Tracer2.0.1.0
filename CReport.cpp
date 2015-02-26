#include "stdafx.h"
#include "Tools.h"

#include "CReport.h"

CReport::CReport(string date, string path, string email, string referrer, string hostname, string keyword, string os, string browser, boolean robot){
	this->email = email;
	this->referrer = referrer;
	this->hostname = hostname;
	this->keyword = keyword;
	this->os = os;
	this->browser = browser;
	if(robot != 1)
		this->robot = 0;
	else
		this->robot = robot;

	cnt = 1;
	detail.push_back(CReportDetail(date,path));	
}

CReport::CReport(string email, string hostname, string agent,string date, string path, string referrer){
	this->email = email;
	this->agent = agent;
	this->referrer = referrer;
	this->hostname = hostname;
	robot = 0;

	//##############################
	//check os

	//Windows
	if(agent.find("Windows 95") != string::npos)			os = "Windows 95";
	else if(agent.find("Win95") != string::npos)			os = "Windows 95";
	else if(agent.find("Windows 98") != string::npos)		os = "Windows 98";
	else if(agent.find("Win98") != string::npos)			os = "Windows 98";
	else if(agent.find("Win 9x") != string::npos)			os = "Windows Me";
	else if(agent.find("Windows 2000") != string::npos)		os = "Windows 2000";
	else if(agent.find("Windows NT 5.0") != string::npos)	os = "Windows 2000";
	else if(agent.find("Windows NT 5.1") != string::npos)	os = "Windows XP";
	else if(agent.find("Windows NT 5.2") != string::npos)	os = "Windows 2003";
	else if(agent.find("WinNT") != string::npos)			os = "Windows NT4.0";
	else if(agent.find("Windows NT") != string::npos)		os = "Windows NT4.0";
	else if(agent.find("Windows") != string::npos)			os = "Windows";

	//Mac
	else if(agent.find("Mac OS X") != string::npos)			os = "Mac OS X";
	else if(agent.find("Mac_PowerPC") != string::npos)		os = "PowerMac";
	else if(agent.find("Macintosh") != string::npos)		os = "Macintosh";

	//UNIX
	else if(agent.find("SunOS") != string::npos)			os = "Sun";
	else if(agent.find("Linux") != string::npos)			os = "Linux";

	//Mobile
	else if(agent.find("ASTEL") != string::npos)			//ASTEL
	{
		vector <string> tokens;
		Tokenize(agent,tokens,"//");
		os = "ASTEL ";

		if(tokens.size() > 2)
			os += tokens[2];
	}
	else if(agent.find("DoCoMo") != string::npos)			//Docomo
	{
		vector <string> tokens;
		Tokenize(agent,tokens,"//");
		os = "DoCoMo ";

		if(tokens.size() > 2)
			os += tokens[2];
	}
	else if(agent.find("UP.Browser") != string::npos)		os = "EZweb";
	else if(agent.find("KDDI-") != string::npos)			os = "EZweb WAP2.0";
	else if(agent.find("PDXGW") != string::npos)			os = "H\"";
	else if(agent.find("J-PHONE") != string::npos)
	{
		vector <string> tokens;
		Tokenize(agent,tokens,"//");
		os = "J-PHONE ";

		if(tokens.size() > 2)
			os += tokens[2];
	}	
	else if(agent.find("L-mode") != string::npos)			os = "L-mode";

	//Robots
	else if(agent.find("Googlebot-Image") != string::npos){		os = "Googlebot-Image";		robot = 1;}
	else if(agent.find("Googlebot") != string::npos){			os = "Googlebot";			robot = 1;}
	else if(agent.find("Slurp/cat") != string::npos){			os = "Inktomi Slurp/cat";	robot = 1;}
	else if(agent.find("Yahoo! Slurp") != string::npos){		os = "Yahoo! Slurp";		robot = 1;}
	else if(agent.find("Ask Jeeves") != string::npos){			os = "Ask Jeeves";			robot = 1;}
	else if(agent.find("msnbot") != string::npos){				os = "MSNbot";				robot = 1;}
	else if(agent.find("psbot") != string::npos){				os = "Psbot";				robot = 1;}
	else if(agent.find("Hatena") != string::npos){				os = "Hatena Antenna";		robot = 1;}
	else if(agent.find("WWWC") != string::npos){				os = "WWWC";				robot = 1;}
	else if(agent.find("livedoorCheckers") != string::npos){	os = "livedoorCheckers";	robot = 1;}
	else if(agent.find("ZyBorg") != string::npos){				os = "ZyBorg";				robot = 1;}
	else if(agent.find("cfetch") != string::npos){				os = "cfetch";				robot = 1;}
	else if(agent.find("InternetLinkAgent") != string::npos){	os = "InternetLinkAgent";	robot = 1;}
	else if(agent.find("MarkAgent") != string::npos){			os = "MarkAgent";			robot = 1;}
	else if(agent.find("SurveyBot") != string::npos){			os = "SurveyBot";			robot = 1;}
	else if(agent.find("Steeler") != string::npos){				os = "Steeler";				robot = 1;}
	else if(agent.find("grub-client") != string::npos){			os = "grub-client";			robot = 1;}
	else if(agent.find("NPBot") != string::npos){				os = "NPBot";				robot = 1;}
	else if(agent.find("QuepasaCreep") != string::npos){		os = "QuepasaCreep";		robot = 1;}
	else if(agent.find("AOL-IWENG") != string::npos){			os = "AOL";					robot = 1;}
	else if(agent.find("appie") != string::npos){				os = "Walhello";			robot = 1;}
	else if(agent.find("proodleBot ") != string::npos){			os = "proodleBot ";			robot = 1;}
	else if(agent.find("ScSpider ") != string::npos){			os = "ScSpider ";			robot = 1;}
	else if(agent.find("TutorGigBot ") != string::npos){		os = "TutorGigBot ";		robot = 1;}
	else if(agent.find("YottaShopping_Bot") != string::npos){	os = "YottaShopping_Bot";	robot = 1;}
	else if(agent.find("Faxobot ") != string::npos){			os = "Faxobot";				robot = 1;}
	else if(agent.find("MJ12bot") != string::npos){				os = "MJ12bot";				robot = 1;}


	//Monitoring
	else if(agent.find("InternetSeer.com") != string::npos){	os ="InternetSeer";			robot = 1;}
	else if(agent.find("netkids") != string::npos){				os ="Netkids";				robot = 1;}


	//Unknown
	else if(agent.size() > 5)									os = agent;
	else{
		if(hostname.find("wispertel") != string::npos)			browser = "Wispertel";
		else if(hostname.find("aol") != string::npos)			browser = "AOL Browser";
	}
	//##############################

	//##############################
	//check browser

	//IE
	if(agent.find("MSIE 3.0") != string::npos)				browser = "IE 3.0x";
	else if(agent.find("MSIE 4.0") != string::npos)			browser = "IE 4.0x";
	else if(agent.find("MSIE 4.5") != string::npos)			browser = "IE 4.5x";
	else if(agent.find("MSIE 5.0") != string::npos)			browser = "IE 5.0x";
	else if(agent.find("MSIE 5.5") != string::npos)			browser = "IE 5.5";
	else if(agent.find("MSIE 6.0") != string::npos)			browser = "IE 6.0";
	else if(agent.find("MSIE") != string::npos)				browser = "IE";

	//Firefox
	else if(agent.find("Firefox") != string::npos)			browser = "Firefox";
	
	//Netscape
	else if(agent.find("Netscape //7") != string::npos)		browser = "Netscape 7.x";
	else if(agent.find("Netscape") != string::npos)			browser = "Netscape";


	//Opera
	else if(agent.find("Konqueror") != string::npos)		browser = "Opera 6.x";
	else if(agent.find("Opera//7") != string::npos)			browser = "Opera 7.x";
	else if(agent.find("Opera//8") != string::npos)			browser = "Opera 8.x";
	else if(agent.find("Opera") != string::npos)			browser = "Opera";

	//Adobe Acrobat
	else if(agent.find("WebCapture ") != string::npos)		browser = "Adobe Acrobat";

	//Lynx
	else if(agent.find("Lynx") != string::npos)				browser = "Lynx";

	//iCab
	else if(agent.find("iCab") != string::npos)				browser = "iCab";

	//BTRON
	else if(agent.find("BTRON") != string::npos)			browser = "BTRON";

	//Dreampassport
	else if(agent.find("DreamPassport") != string::npos)	browser = "Dreampassport";

	//Konqueror
	else if(agent.find("Konqueror") != string::npos)		browser = "Konqueror";

	//Safari
	else if(agent.find("Safari") != string::npos)			browser = "Safari";

	//Sleipnir
	else if(agent.find("Sleipnir") != string::npos)			browser = "Sleipnir";
	//##############################

	//##############################
	//check referrer
	if(referrer.find("www.google") != string::npos)							// Google
	{
		if(!getKeyword(referrer, "q=", this->keyword, this->referrer))
			getKeyword(referrer, "as_q=", this->keyword, this->referrer);	// Google2

		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
			break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}
	}
	else if(referrer.find("search.lycos.co.jp") != string::npos)		// Lycos.co.jp
		getKeyword(referrer, "qt=", this->keyword, this->referrer);

	else if(referrer.find("www.infoseek.co.jp") != string::npos)		// Infoseek.co.jp
	{
		getKeyword(referrer, "qt=", this->keyword, this->referrer);
//		this->keyword = euctosjis(this->keyword);
		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}

	}
	else if(referrer.find("goo.ne.jp") != string::npos)					// Goo
	{
		getKeyword(referrer, "MT=", this->keyword, this->referrer);

		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}
	}
	else if(referrer.find("search.aaacafe.ne.jp") != string::npos)		// AAA!Cafe
	{
		getKeyword(referrer, "key=", this->keyword, this->referrer);
		this->keyword = euctosjis(this->keyword);
	}
	else if(referrer.find("search.yahoo.co.jp") != string::npos)		// YahooJapan
	{
		getKeyword(referrer, "p=", this->keyword, this->referrer);

		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}
	}
	else if(referrer.find("excite.co.jp") != string::npos)				// Excite.co.jp
		getKeyword(referrer, "search=", this->keyword, this->referrer);

	else if(referrer.find("search.msn.co.jp") != string::npos)			// msn
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);
		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}
	}
	else if(referrer.find("search.naver.co.jp") != string::npos)		// NAVERJAPAN
	{
		getKeyword(referrer, "query=", this->keyword, this->referrer);
		this->keyword = euctosjis(this->keyword);
	}
	else if(referrer.find("www.alltheweb.com") != string::npos)			// alltheweb
		getKeyword(referrer, "q=", this->keyword, this->referrer);

	else if(referrer.find("search.nifty.com") != string::npos)			// @Nifty
	{
		getKeyword(referrer, "Text=", this->keyword, this->referrer);

		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}

	}
	else if(referrer.find("search.biglobe.ne.jp") != string::npos)		// BIGLOBE
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);

		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}
	}
	else if(referrer.find("search.lycos.com") != string::npos)			// Lycos.com
		getKeyword(referrer, "query=", this->keyword, this->referrer);

	else if(referrer.find("go.google.com") != string::npos)				// Infoseek.com
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);
		this->keyword = utf8tosjis(this->keyword);
	}
	else if(referrer.find("search.yahoo.com") != string::npos)			// Yahoo
	{
		getKeyword(referrer, "p=", this->keyword, this->referrer);
		this->keyword = utf8tosjis(this->keyword);
	}
	else if(referrer.find("search.msn.com") != string::npos)			// msn
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);
		this->keyword = utf8tosjis(this->keyword);
	}
	else if(referrer.find("altavista.com") != string::npos)				// Altavista
		getKeyword(referrer, "q=", this->keyword, this->referrer);

	else if(referrer.find("s.teoma.com") != string::npos)				// Teoma
		getKeyword(referrer, "q=", this->keyword, this->referrer);

	else if(referrer.find("www.wisenut.com") != string::npos)			// wiseNut
		getKeyword(referrer, "q=", this->keyword, this->referrer);

	else if(referrer.find("www.ceek.jp") != string::npos)				// Ceek
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);
		this->keyword = euctosjis(this->keyword);
	}

	else if(referrer.find("www.blogoon.net") != string::npos)			// Blogoon
	{
		getKeyword(referrer, "key=", this->keyword, this->referrer);
		//this->keyword = euctosjis(this->keyword);
		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}

	}

	else if(referrer.find("search.live.com") != string::npos)			// Live Search
	{
		getKeyword(referrer, "q=", this->keyword, this->referrer);
//		this->keyword = euctosjis(this->keyword);
		string bstr;

		switch(ifEUCJP(this->keyword)){
		case EUC_JP:
			bstr = euctosjis(this->keyword); 
			if(bstr.size())
				this->keyword = bstr;
			else
				if(ifUTF8(this->keyword))
					this->keyword = utf8tosjis(this->keyword);
				break;
		case SJIS:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		case -1:
			if(ifUTF8(this->keyword))
				this->keyword = utf8tosjis(this->keyword);
			break;
		}

	}
	cnt = 1;
	detail.push_back(CReportDetail(date,path));
}

CReportDetail::CReportDetail(string date, string path){
	this->date = date;
	this->path = path;
}