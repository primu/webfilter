#include "stdafx.h"
#include "Strona.h"

Strona
::Strona
()
{
}

Strona
::~Strona
()
{
}

char* Strona::pobierzUrl()
{
	return this->url;
};

char* replace_char(char* stringPelny, char znak, char* stringZastepczy )
{
	if(stringPelny==nullptr)
		return nullptr;
	if(stringZastepczy==nullptr)
	{
		return nullptr;
	}
	if(strchr(stringPelny,znak)==nullptr)
	{
		return nullptr;
	}
	char* poz = stringPelny;
	char* pozp = stringPelny;
	char* nowy = nullptr;
	char* temp = nullptr;
	size_t dlugosc = 0;
	

	while(poz=strchr(poz,znak))
	{
		dlugosc=poz-pozp;
		if(nowy==nullptr)
		{
			nowy=new char[dlugosc+strlen(stringZastepczy)+1];
			strncpy(nowy,pozp,dlugosc);
			strcpy(nowy+dlugosc,stringZastepczy);
			nowy[dlugosc+strlen(stringZastepczy)]='\0';
		}else
		{
			temp=new char[strlen(nowy)+strlen(stringZastepczy)+dlugosc+1];

			strcpy(temp,nowy);
			strncpy(temp+strlen(nowy),pozp,dlugosc);
			strcpy(temp+strlen(nowy)+dlugosc,stringZastepczy);
			temp[strlen(nowy)+strlen(stringZastepczy)+dlugosc]='\0';
			delete[] nowy;
			nowy = temp;
			temp = nullptr;
		}
		poz++;
		pozp=poz;
	}
	temp=new char[strlen(nowy)+strlen(pozp)+1];
	strcpy(temp,nowy);
	strcpy(temp+strlen(nowy),pozp);
	temp[strlen(nowy)+strlen(pozp)]='\0';
	delete[] nowy;
	nowy = temp;
	temp=nullptr;
	
	return nowy;
}
char* regexFix(char* str)
{
	char* temp = new char[strlen(str)+2];
	temp[0]='^';
	strcpy(temp+1,str);
	temp[strlen(str)+1]='$';
	temp[strlen(str)+2]='\0';
	delete[] str;
	return temp;
}
void Strona::utworzRegex()
{
	char* tempRegex = "(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9]|[a-zA-Z0-9])";
	char* poz = nullptr;
	char* pozOst = this->url;
	char* pozReg = nullptr;

	if(regexp==nullptr)
	{
		char* k = "\\.";
		char* temp = replace_char(this->url,'.',k);
		if(temp!=nullptr)
		{ 
			char* temp2=replace_char(temp,'*',tempRegex);
			if(temp2!=nullptr)
				this->regexp = regexFix(temp2);
			else
				this->regexp = regexFix(temp);
		}
		
	}
}

Strona::Strona(char* url)
{
	try
	{
		czyPoprawna(url);
	}catch(std::exception *e)
	{
		throw gcnew System::Exception();
	}
	this->url=url;
	this->aktywna=true;
	this->regexp = nullptr;
}

void Strona::czyPoprawna(char* url)
{
	char* wrc = "(^((([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)|\\*\\.)+(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])|\\*)$)|(^[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9]$)";
	std::regex wr(wrc);
	if(regex_match(url,wr))
		Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(url)+" - OK\n");
		//printf("%s - OK\n",url);
	else throw -1;

	
}

char* Strona::pobierzRegexp()
{
	return this->regexp;
}