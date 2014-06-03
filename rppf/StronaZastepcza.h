#pragma once
#include <string>
#include <regex>
using namespace System;

public class StronaZastepcza
{
private:
	char* nazwa;
	char* kodStrony;

	bool czyPoprawna();

public:
	bool operator<(StronaZastepcza &rhs){ return strcmp(kodStrony,rhs.kodStrony)>0?true:false; }
	bool operator ==( StronaZastepcza &rhs ){ return strcmp(kodStrony,rhs.kodStrony)==0?true:false; }

	char* pobierzNazwe(){return nazwa;};
	char* pobierzKod(){return kodStrony;};



	StronaZastepcza(void);
	StronaZastepcza(char* nazwa, char* kod);
	~StronaZastepcza(void);
};

