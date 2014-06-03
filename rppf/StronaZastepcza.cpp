#include "stdafx.h"
#include "StronaZastepcza.h"

StronaZastepcza::StronaZastepcza(void)
{
}
StronaZastepcza::StronaZastepcza(char* nazwa, char* kod)
{
	czyPoprawna();
	this->nazwa=nazwa;
	this->kodStrony=kod;
}
bool StronaZastepcza::czyPoprawna()
{
	char* wrc = "^<(html|HTML)>.*<\\/(html|HTML)>$";
	std::regex wr(wrc);
	if(regex_match(kodStrony,wr))
		Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(nazwa)+" - Kod strony OK\n");
	else throw -1;
}

StronaZastepcza::~StronaZastepcza(void)
{
}
