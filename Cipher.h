#ifndef CCipher_H
#define CCipher_H

class CCipher{
public:
	BOOL decode();
	void encode();
	CCipher(CString name, CString email, CString expire);
	
	CString name;
	CString email;
	CString expire;
	CString key;

private:
	BOOL unify(CString &str, BOOL check=false);
	void crypt(CString& str, CString phr);
	void duplicate(CString& str);

};
#endif