#pragma once

#include "Strona.h"
#include "StronaZastepcza.h"
#include "XML\rapidxml.hpp"
#include "XML\rapidxml_print.hpp"
#include "XML\rapidxml_iterators.hpp"
#include "XML\rapidxml_utils.hpp"
//#include <rapidxml.hpp>
//#include <rapidxml_print.hpp>
//#include <rapidxml_iterators.hpp>
//#include <rapidxml_utils.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

//#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace rapidxml;
using namespace std;
using namespace System::Security::Cryptography;
using namespace System::IO;

ref class BazaDanych
{
private:
	string* filename;
	memory_pool<> *po;
	xml_document<> *xmld;

	bool sToBool(char* str)
	{
		if(str[0] == '0') return false;
		else return true;
	};
	string intToString(int i)
	{
	stringstream ss;
	ss << i;
	return ss.str();
	};
	void readWebpages(xml_document<>* doc, vector<Strona>* v);
	vector<StronaZastepcza> readErrorPages(xml_document<>* doc);
	xml_document<>* createBlankDocument(memory_pool<>* p);
	void insertWebpageNode(Strona w,xml_document<>* doc,memory_pool<>* p);
	array<Byte>^ xorArrays(array<Byte>^ a1, array<Byte>^ a2);
	String^ encryptXML(xml_document<>* document);
	String^ decryptXML(String^ encoded);
public:
	BazaDanych(void);
	BazaDanych(char* sciezka);
	vector<Strona>* OdczytajListeStron();
	void ZapiszListeStron(vector<Strona>* listaStron);
};

