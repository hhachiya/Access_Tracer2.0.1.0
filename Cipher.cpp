#include "stdafx.h"
#include "Cipher.h"


CCipher::CCipher(CString name, CString email, CString expire)
{
	this->name = name;
	this->email = email;
	this->expire = expire;
}

void CCipher::encode()
{
	CString _name = name;
	CString _email = email;
	CString _expire = expire;

	duplicate(_name);
	duplicate(_email);
	duplicate(_expire);

	crypt(_name,"7s6h1a02");
	crypt(_email,"^h8=S5_");
	crypt(_expire,"Hachiya");

	key.Format(_T("%s:%s:%s"),_name,_email,_expire);
}

BOOL CCipher::decode()
{
	crypt(name,"7s6h1a02");
	crypt(email,"^h8=S5_");
	crypt(expire,"Hachiya");

	unify(name);
	unify(email);
	if(unify(expire,TRUE) == FALSE) return FALSE;

	return TRUE;
}

void CCipher::duplicate(CString& str)
{
	CString buf = str;

	str.Empty();

	// 
	for(int i=0;i<buf.GetLength();i++){
		str.Insert(i*2,buf[i]);
		str.Insert(i*2+1,buf[i]);
	}
}

void CCipher::crypt(CString &str, CString phr)
{
	int size = phr.GetLength();
	CString _str = str;

	str.Empty();

	for(int i=0;i<_str.GetLength();i++)
		if((_str.GetAt(i) ^ phr.GetAt(i%size)) > 0x20 && (_str.GetAt(i) ^ phr.GetAt(i%size)) <= 0x7E && (_str.GetAt(i) ^ phr.GetAt(i%size)) != 0x3a)
			str.Insert(i,_str.GetAt(i) ^ phr.GetAt(i%size));
		/*else if((_str.GetAt(i) ^ i) > 0x20 && (_str.GetAt(i) ^ i) <= 0x7E && (_str.GetAt(i) ^ i) != 0x3a)
			str.Insert(i,_str.GetAt(i) ^ i);*/
		else
			str.Insert(i,_str.GetAt(i));
}

BOOL CCipher::unify(CString &str, BOOL check)
{
	CString buf = str;

	int len = (int)((double)str.GetLength()/2);

	str.Empty();

	//
	for(int i=0;i<len;i++){
		char first = buf.GetAt(i*2);

		if(check==TRUE){
			char second = buf.GetAt(i*2+1);
			
			if(first != second) return FALSE;
		}

		str.Insert(i,first);
	}

	return TRUE;
}


