#include "stdafx.h"
#include <algorithm>
#include "filtr.h"
#include <vector>

using namespace System;

filtr::filtr()
{
	strony = new std::vector<Strona>();
	uruchomiony=false;
	ileZablokowano=0;
	//ileAktywnych=0;
}
bool filtr::FCzyUruchomiony()
{
	if(uruchomiony)
		return true;
	else return false;
}

std::vector<Strona> filtr::FPobierzListeStron()
{
	//if(strony->size>0)
		return *strony;
}

void filtr::FWatek()
{
	tr = gcnew Thread(gcnew ThreadStart(this,&filtr::FUruchom));
	tr->Start();
}
void filtr::FDodajStrone(Strona strona)
{
	if(czyIstnieje(strona.pobierzUrl()))
	{
		throw gcnew System::Exception();
	}
	strona.utworzRegex();
	strony->push_back(strona);
	std::sort(strony->rbegin(),strony->rend());
	Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(strona.pobierzUrl())+" - Dodano wpis!\n");
	//ileAktywnych++;
	//printf("Posortowane!");
}
void filtr::FUruchom()
{
	uruchomiony=true;
	const char block_data[] =
    "HTTP/1.1 200 OK\r\n"
    "Connection: close\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<!doctype html>\n"
    "<html>\n"
    "\t<head>\n"
    "\t\t<title>Strona zablokowana!</title>\n"
    "\t</head>\n"
    "\t<body>\n"
    "\t\t<h1>Strona zablokowana!</h1>\n"
    "\t\t<hr>\n"
    "\t\t<p>Rafa³ i Przemek zablokowali stronê! Przepraszamy!</p>\n"
    "\t</body>\n"
    "</html>\n";

	HANDLE handle;
    WINDIVERT_ADDRESS addr;
	UINT8 packet[MAXBUF];			//do zmiany
    UINT packet_len;
    PWINDIVERT_IPHDR ip_header;
    PWINDIVERT_TCPHDR tcp_header;
    PVOID payload;
    UINT payload_len;
    PACKET reset0;
    PPACKET reset = &reset0;
    PACKET finish0;
    PPACKET finish = &finish0;
    PDATAPACKET blockpage;
    UINT16 blockpage_len;

    /*PBLACKLIST blacklist;*/

    unsigned i;
    INT16 priority = 404;       // Arbitrary.



    // Initialize the pre-frabricated packets:
    blockpage_len = sizeof(DATAPACKET)+sizeof(block_data)-1;
    blockpage = (PDATAPACKET)malloc(blockpage_len);
    if (blockpage == NULL)
    {
		uruchomiony = false;
        //fprintf(stderr, "error: memory allocation failed\n");
		Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"B³¹d: nie uda³o siê zaalokowaæ pamiêci\n");
        exit(EXIT_FAILURE);
    }
    PacketInit(&blockpage->header);
    blockpage->header.ip.Length   = htons(blockpage_len);
    blockpage->header.tcp.SrcPort = htons(80);
    blockpage->header.tcp.Psh     = 1;
    blockpage->header.tcp.Ack     = 1;
    memcpy(blockpage->data, block_data, sizeof(block_data)-1);
    PacketInit(reset);
    reset->tcp.Rst = 1;
    reset->tcp.Ack = 1;
    PacketInit(finish);
    finish->tcp.Fin = 1;
    finish->tcp.Ack = 1;

    // Open the Divert device:
    handle = WinDivertOpen(
            "outbound && "              // Outbound traffic only
            "ip && "                    // Only IPv4 supported
            //"tcp.DstPort == 80 && "     // HTTP (port 80) only
            "tcp.PayloadLength > 0",    // TCP data packets only
            WINDIVERT_LAYER_NETWORK, priority, 0
        );
    if (handle == INVALID_HANDLE_VALUE)
    {
		uruchomiony = false;
		Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"B³¹d: Nie uda³o siê uruchomiæ sterownika WinDivert\n");
        //fprintf(stderr, "error: failed to open the WinDivert device (%d)\n",
            //GetLastError());
        exit(EXIT_FAILURE);
		
    }

	//printf("Uruchomiono!\n");
	Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Uruchomiono!\n");

    // Main loop:
	while (uruchomiony)
    {
        if (!WinDivertRecv(handle, packet, sizeof(packet), &addr, &packet_len))
        {
            /*fprintf(stderr, "warning: failed to read packet (%d)\n",
                GetLastError());*/
			Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Ostrze¿enie: Nie uda³o siê odczytaæ pakietu ("+GetLastError().ToString()+")\n");
            continue;
        }

        /*if (!WinDivertHelperParsePacket(packet, packet_len, &ip_header, NULL,
                NULL, NULL, &tcp_header, NULL, &payload, &payload_len) ||
            !BlackListPayloadMatch(blacklist, payload, (UINT16)payload_len))*/

		if (!WinDivertHelperParsePacket(packet, packet_len, &ip_header, NULL, //tu
			NULL, NULL, &tcp_header, NULL, &payload, &payload_len) || !DopasujStrone((char*)payload,(UINT16)payload_len))
        {
            // Packet does not match the blacklist; simply reinject it.
            if (!WinDivertSend(handle, packet, packet_len, &addr, NULL))
            {
                /*fprintf(stderr, "warning: failed to reinject packet (%d)\n",
                    GetLastError());*/
				Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Ostrze¿enie: Nie uda³o siê ponownie wys³aæ pakietu ("+GetLastError().ToString()+")\n");
            }
            continue;
        }

        // The URL matched the blacklist; we block it by hijacking the TCP
        // connection.

        // (1) Send a TCP RST to the server; immediately closing the
        //     connection at the server's end.
        reset->ip.SrcAddr       = ip_header->SrcAddr;
        reset->ip.DstAddr       = ip_header->DstAddr;
        reset->tcp.SrcPort      = tcp_header->SrcPort;
        reset->tcp.DstPort      = htons(80);
        reset->tcp.SeqNum       = tcp_header->SeqNum;
        reset->tcp.AckNum       = tcp_header->AckNum;
        WinDivertHelperCalcChecksums((PVOID)reset, sizeof(PACKET), 0);
        if (!WinDivertSend(handle, (PVOID)reset, sizeof(PACKET), &addr, NULL))
        {
            /*fprintf(stderr, "warning: failed to send reset packet (%d)\n",
                GetLastError());*/
			Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Ostrze¿enie: Nie uda³o siê wys³aæ pakietu resetuj¹cego ("+GetLastError().ToString()+")\n");
        }

        // (2) Send the blockpage to the browser:
        blockpage->header.ip.SrcAddr       = ip_header->DstAddr;
        blockpage->header.ip.DstAddr       = ip_header->SrcAddr;
        blockpage->header.tcp.DstPort      = tcp_header->SrcPort;
        blockpage->header.tcp.SeqNum       = tcp_header->AckNum;
        blockpage->header.tcp.AckNum       =
            htonl(ntohl(tcp_header->SeqNum) + payload_len);
        WinDivertHelperCalcChecksums((PVOID)blockpage, blockpage_len, 0);
        addr.Direction = !addr.Direction;     // Reverse direction.
        if (!WinDivertSend(handle, (PVOID)blockpage, blockpage_len, &addr,
                NULL))
        {
            /*fprintf(stderr, "warning: failed to send block page packet (%d)\n",
                GetLastError());*/
			Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Ostrze¿enie: Nie uda³o siê wys³aæ pakietu ze stron¹ zastêpcz¹ ("+GetLastError().ToString()+")\n");
        }

        // (3) Send a TCP FIN to the browser; closing the connection at the 
        //     browser's end.
        finish->ip.SrcAddr       = ip_header->DstAddr;
        finish->ip.DstAddr       = ip_header->SrcAddr;
        finish->tcp.SrcPort      = htons(80);
        finish->tcp.DstPort      = tcp_header->SrcPort;
        finish->tcp.SeqNum       =
            htonl(ntohl(tcp_header->AckNum) + sizeof(block_data) - 1); 
        finish->tcp.AckNum       =
            htonl(ntohl(tcp_header->SeqNum) + payload_len);
        WinDivertHelperCalcChecksums((PVOID)finish, sizeof(PACKET), 0);
        if (!WinDivertSend(handle, (PVOID)finish, sizeof(PACKET), &addr, NULL))
        {
            /*fprintf(stderr, "warning: failed to send finish packet (%d)\n",
                GetLastError());*/
			Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Ostrze¿enie: Nie uda³o siê wys³aæ pakietu zakoñczenia po³¹czenia z przegl¹dark¹ ("+GetLastError().ToString()+")\n");
        }
    }

	WinDivertClose(handle);
	//printf("\nZakonczono filtrowanie!");
	Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+"Zakoñczono filtrowanie!\n");
}
void filtr::FZatrzymaj()
{
	this->uruchomiony=false;
	tr->Join();
}
void filtr::PacketInit(PPACKET packet)
{
    memset(packet, 0, sizeof(PACKET));
    packet->ip.Version = 4;
    packet->ip.HdrLength = sizeof(WINDIVERT_IPHDR) / sizeof(UINT32);
    packet->ip.Length = htons(sizeof(PACKET));
    packet->ip.TTL = 64;
    packet->ip.Protocol = IPPROTO_TCP;
    packet->tcp.HdrLength = sizeof(WINDIVERT_TCPHDR) / sizeof(UINT32);
}

bool filtr::DopasujStrone(char * dane, UINT16 dlugosc)
{
	bool h=true;
	
	static const char get_str[] = "GET /";
    static const char post_str[] = "POST /";
	static const char http_str[] = " HTTP/1.1";
	static const char http_host[] = "\r\nHost: ";
	//char domena[255];
	char* domena = nullptr;
	char* uri = nullptr;
	char* pozycja = nullptr;
	char* pozycja2 = nullptr;

	if(strlen(dane)<strlen(http_host))
	{
		return false;
	}
	
	if(strncmp(get_str,dane,strlen(get_str))!=0)
	{
		if(strncmp(post_str,dane,strlen(post_str))!=0)
		{
			return false;
		}else
		{
			if(!strncmp(http_str,dane+strlen(post_str)-1,strlen(http_str)))
			{
				return false;
			}
			uri=WyluskajUri(dane,(char*)post_str,(char*)http_str);
		}
	}
	else
	{
		if(!strncmp(http_str,dane+strlen(get_str)-1,strlen(http_str)))
		{
			return false;
		}
		uri=WyluskajUri(dane,(char*)get_str,(char*)http_str);
	}

	pozycja=nullptr;
	pozycja2=nullptr;

	//printf("%s","Pakiet HTTP!");
	pozycja=strstr(dane,http_host);
	if(pozycja==nullptr)
		return false;
	pozycja2=strchr(pozycja+strlen(http_host),'\r');
	if(pozycja2!=nullptr)
	{
		int tempDl =pozycja2-pozycja-strlen(http_host);//
		domena = new char[tempDl];
		strncpy(domena,pozycja+1+strlen(http_host)-1,tempDl); //+1 bo inaczej bra³o spacje xD
		domena[tempDl]='\0';
	}

	
	//printf("\nDomena: %s\n",domena);
	if(WyszukajRE(domena,uri))
	{
		Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(domena) + " - zablokowano!\n");
		//printf("Zablokowano!");
		this->ileZablokowano++;
	}else
	{
		return false;
	}
	return true;
}

char* filtr::WyluskajUri(char* dane, char* metoda , char* wersjaHTTP)
{
	char* pozycja = nullptr;
	char* pozycja2 = nullptr;
	char* uri = nullptr;

	pozycja=strstr(dane,metoda)+sizeof(metoda);
	if(pozycja==nullptr)
		return false;
	pozycja2=strchr(pozycja,' ');
	if(pozycja2!=nullptr)
	{
		int tempDl = pozycja2-pozycja;
		if(tempDl>1)
		{
			uri = new char[tempDl];
			strncpy(uri,pozycja,tempDl);
			uri[tempDl]='\0';
		}
	}

	return uri;
	//return nullptr;
}
int PunktSrodkowy(int min, int max)
{
	int n = max - min;

	if(n==0)
		return max;
	int mid = n/2;
	if(min>0)
		return min+mid;
	else
		return mid;
}

bool filtr::FUsunStrone(char* adres)
{
	std::vector<Strona>::iterator temp;
	bool znaleziono = false;
	for(std::vector<Strona>::iterator it = strony->begin();it!=strony->end() && !znaleziono;it++)
	{
		if(strcmp(adres,it->pobierzUrl())==0)
		{
			znaleziono=true;
			temp=it;
			
		}
	}
	if(znaleziono)
	{
		/*if(temp->czyAktywna())
			ileAktywnych--;*/
		strony->erase(temp);	
	}
	//std::sort(strony->rbegin(),strony->rend());
	return znaleziono;
}

bool filtr::WyszukajRE(char* domena, char* uri)
{
	bool znaleziono = false;
	bool aktywna = true;
	for(std::vector<Strona>::iterator it = strony->begin();it!=strony->end() && !znaleziono;it++)
	{
		if(it->pobierzRegexp()==nullptr)
		{
			std::regex wr(it->pobierzUrl());
			znaleziono=std::regex_search(domena, wr);
			if(!znaleziono && uri!=nullptr)
			{
				znaleziono=std::regex_search(uri, wr);
			}
			if(!it->czyAktywna() && znaleziono)
			{
				aktywna=false;
			}
		}else
		{
			//printf("%s \n",it->pobierzUrl());
			//printf("%s \n",it->pobierzRegexp());
			std::regex wr(it->pobierzRegexp());
			znaleziono=std::regex_match(domena,wr);
			if(!it->czyAktywna() && znaleziono)
			{
				aktywna=false;
			}
		}
	}
	if(!aktywna && znaleziono)
	{
		return false;
	}
	return znaleziono;
}

bool filtr::Wyszukaj(char* domena)
{
	int koniec = strony->size()-1;//liczbaStron-1;
	int poczatek = 0;

	int srodek;
	int wyn;


	while(poczatek<=koniec)
	{
		srodek = PunktSrodkowy(poczatek,koniec);

		wyn = strcmp(strony->at(srodek).pobierzUrl(),domena);
		if(wyn==0)
		{
			return true;
		}else
		{
			if(wyn<0)
			{
				poczatek=srodek+1;
			}else
			{
				koniec=srodek-1;
			}
		}
	}
	if(strcmp(strony->at(srodek).pobierzUrl(),domena)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void filtr::WczytajPlik() //tymczasowe rozwi¹zanie
{
	int j=0;
	std::fstream myReadFile;
	myReadFile.open("C:\\tmp\\strony.txt");
	
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			char* output = new char[sizeof(myReadFile)];
			myReadFile.getline(output,sizeof(myReadFile));
			Strona* str = new Strona(output);
			//ileAktywnych++;
			str->utworzRegex();
			strony->push_back(*str);
			//printf("%s\n",strony->at(j).pobierzUrl());
			//Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(strony->at(j).pobierzUrl())+"\n");
			j++;
		}
	}
	myReadFile.close();
}

void filtr::FAktywujStrone(bool a, char* adres)
{
	bool znaleziono = false;
	for(std::vector<Strona>::iterator it = strony->begin();it!=strony->end() && !znaleziono;it++)
	{
		if(strcmp(it->pobierzUrl(),adres)==0)
		{
			znaleziono=true;
			it->ustawJakoAktywna(a);
			if(a)
			{
				//printf("%s - aktywna\n",it->pobierzUrl());
				//this->ileAktywnych++;
				Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(it->pobierzUrl())+" - aktywna\n");
			}
			else
			{
				Console::Write(System::DateTime::Now.ToString("[yyyy-MM-dd HH:mm:ss]")+" "+gcnew String(it->pobierzUrl())+" - nieaktywna\n");
				//this->ileAktywnych--;
			}
				//printf("%s - nieaktywna\n",it->pobierzUrl());
		}
	}
}

bool filtr::czyIstnieje(char* adres)
{
	for(std::vector<Strona>::iterator it = strony->begin();it!=strony->end();it++)
	{
		if(strcmp(adres,it->pobierzUrl())==0)
		{
			return true;
		}
	}
	return false;
}

int filtr::FileAktywnych()
{
	int ileAktywnych=0;
	for(std::vector<Strona>::iterator it = strony->begin();it!=strony->end();it++)
	{
		if(it->czyAktywna())
			ileAktywnych++;
	}
	return ileAktywnych;
}

void filtr::ZapiszDoPliku()
{
	BazaDanych^ baza = gcnew BazaDanych("log.dat");

	baza->ZapiszListeStron(strony);
	vector<Strona> *sssss = baza->OdczytajListeStron();
}

