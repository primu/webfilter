#include <string>
#include <regex>
using namespace System;
public class Strona

{
public:
	Strona
();
	~Strona
();

	Strona(char* url, char* idStronyZastepczej=nullptr);

	char* pobierzUrl();
	char* pobierzRegexp();

	bool czyAktywna(){return aktywna;};
	void ustawJakoAktywna(bool a){aktywna=a;};

	bool operator<(Strona &rhs){ return strcmp(url,rhs.url)>0?true:false; }
	bool operator ==( Strona &rhs ){ return strcmp(url,rhs.url)==0?true:false; }
	//bool operator ==( char* &rhs ){ return strcmp(url,rhs)==0?true:false; }
	void utworzRegex();

private:
	char * url;
	char * idStronyZastepczej;
	char * regexp;
	bool aktywna;
	void czyPoprawna(char*);
};

