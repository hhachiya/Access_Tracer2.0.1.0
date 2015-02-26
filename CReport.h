#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL

#include <string>
#include <vector>

using namespace std;

class CReportDetail{
public:
	CReportDetail(string date, string path);

	string date;
	string path;
};

class CReport{
public:
	CReport(string email, string hostname, string agent,string date, string path, string referrer);
	CReport(string date, string path, string email, string referrer, string hostname, string keyword, string os, string browser, boolean robot);

	string keyword;
	string email;
	string hostname;
	string os;
	string browser;
	string agent;
	string referrer;
	boolean robot;
	int cnt;
	vector <CReportDetail> detail;
};
