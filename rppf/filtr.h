#pragma once

#include <vector>
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include "windivert.h"
#include <regex>
#include "Strona.h"

#define MAXBUF 0xFFFF

using namespace System::Threading;


typedef struct
	{
		WINDIVERT_IPHDR  ip;
		WINDIVERT_TCPHDR tcp;
	} PACKET, *PPACKET;
	typedef struct 
	{
		PACKET header;
		UINT8 data[];
	} DATAPACKET, *PDATAPACKET;

ref class filtr
{
	std::vector<Strona>* strony;

private:
	bool czyIstnieje(char* adres);
	Thread^ tr;
	//void FWatek();
	bool DopasujStrone(char* dane, UINT16 dlugosc);
	bool Wyszukaj(char* domena);
	bool WyszukajRE(char* domena, char* uri);
	void PacketInit(PPACKET packet);

	void FUruchom();
	bool uruchomiony;
	char* WyluskajUri(char* dane, char* metoda , char* wersjaHTTP);
public:
	std::vector<Strona> FPobierzListeStron();
	void FWatek();
	void WczytajPlik();
	filtr();


	bool FCzyUruchomiony();
	void FZatrzymaj();
	void FDodajStrone(Strona strona);
	bool FUsunStrone(char* strona);
	void FAktywujStrone(bool a, char* adres);
};

