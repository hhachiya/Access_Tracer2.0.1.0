#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>
#include "StdAfx.h"
#include "Cipher.h"

#define EUC_JP 0
#define SJIS 1

using namespace std;

void GetLicenceFilePath(char* lfilename);
void Logging(LPCTSTR agent, LPCSTR logdata);
int Tokenize(const string& str,vector<string>& tokens,const string& delimiters);
string decode(const string& src);
string utf8tosjis(string src);
string euctosjis(string src);
int getKeyword(string s, string var, string& key, string& url);
int GetDatesToExpire(CString key="");
BOOL ifUTF8(string str);
int ifEUCJP(string str);
int isInDateRange(string date_s);
#endif