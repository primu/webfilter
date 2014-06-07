#include "stdafx.h"
#include "BazaDanych.h"


BazaDanych::BazaDanych(void)
{
}
BazaDanych::BazaDanych(char* sciezka)
{
	//string filename = "C:\\out.xml";
	filename=new string(sciezka);
	
	po = new memory_pool<>();

	//xmld = new xml_document<>();
	xmld=createBlankDocument(po);


	//ifstream in(*filename, std::ios::in | std::ios::binary);
	//in.seekg(0, std::ios::end);

	//string text="";
 //   text.resize(in.tellg());
	//in.seekg(0, std::ios::beg);
 //   in.read(&text[0], text.size());
 //   in.close();
	//
	//	char* temp = (char*)text.c_str();
	//
	//xmld->parse<0>(temp);
	//
	//vector<Strona> strony;
	////readWebpages(&x,&strony);
	//cout<<strony.capacity();
	//cout<< strony.begin()->pobierzNazwe();
	//cout<< strony.begin()->pobierzUrl();
	//Strona* s = new Strona("http://ssss.com","test46","1");
	
	//insertWebpageNode(*s,&x,po);
}

void BazaDanych::readWebpages(xml_document<>* doc, vector<Strona>* v)
{
	xml_node<> *node =  doc->first_node()->first_node("Webpages");
	//vector<Strona> Webpages;
	//cout<<*doc;
	for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
	//	string temp = (*child).first_node("URL")->value();
	//	cout<<temp;
		v->push_back(Strona(child->first_node("URL")->value()));//,
			 //child->first_node("Name")->value(),
		 //child->first_node("ErrorPageID")->value()));
	}

	//return Webpages;
}

vector<StronaZastepcza> BazaDanych::readErrorPages(xml_document<>* doc)
{
	xml_node<> *node =  doc->first_node()->first_node("ErrorPages");
	vector<StronaZastepcza> protocols;



	for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
	std::stringstream ss;
    ss <<*child->first_node("Content")->first_node();
	
		protocols.push_back(StronaZastepcza(child->first_node("Name")->value(),(char*)ss.str().c_str()));
		//protocols.push_back(StronaZastepcza(//stoi(child->first_attribute("id")->value()),
		//	sToBool(child->first_attribute("active")->value()),
		// child->first_node("Name")->value(),
		// ss.str()));
	}

	return protocols;
}

xml_document<>* BazaDanych::createBlankDocument(memory_pool<>* p)
{

	xml_document<> ret;
	xml_node<> *node = ret.allocate_node(node_element, "WEBFilterDatabase");

	ret.append_node(node);
	ret.first_node()->append_node(ret.allocate_node(node_element, p->allocate_string("Header")," "));
	ret.first_node()->append_node(ret.allocate_node(node_element, p->allocate_string("Webpages")," "));
	//ret.first_node()->append_node(ret.allocate_node(node_element, p->allocate_string("Ports")," "));
	//ret.first_node()->append_node(ret.allocate_node(node_element, p->allocate_string("Protocols")," "));
	ret.first_node()->append_node(ret.allocate_node(node_element, p->allocate_string("ErrorPages")," "));

	return &ret;
}

void BazaDanych::insertWebpageNode(Strona w,xml_document<>* doc,memory_pool<>* p)
{
	xml_node<>* newnode = p->allocate_node(node_element,"Webpage");

	doc->first_node()->first_node("Webpages")->append_node(newnode);
	//doc->first_node()->first_node("Webpages")->last_node()->append_node( p->allocate_node(node_element,"Name",w.pobierzNazwe()));
	doc->first_node()->first_node("Webpages")->last_node()->append_node( p->allocate_node(node_element,"URL",w.pobierzUrl()));
	//doc->first_node()->first_node("Webpages")->last_node()->append_node( p->allocate_node(node_element,"ErrorPageID","1"));
	cout<<*doc;

}

array<Byte>^ BazaDanych::xorArrays(array<Byte>^ a1, array<Byte>^ a2)
{
	if(a1->Length != a2->Length) throw;
	array<Byte>^ ret = gcnew array<Byte>(a1->Length);

	for(int i=0;i<a1->Length;i++)
	{
		ret[i] = a1[i] ^ a2[i];
	}
	return ret;
}

String^ BazaDanych::encryptXML(xml_document<>* document)//, array<Byte>^ key, array<Byte>^ iv)
{
	Random^ rand= gcnew Random(0xffddffee);
	string temp;
	print(std::back_inserter(temp),*document);
	
	String^ plaintext = gcnew String(temp.c_str());

	RijndaelManaged^ r = gcnew RijndaelManaged;

	r->Padding = System::Security::Cryptography::PaddingMode::PKCS7;

	array<Byte>^ a1 = gcnew array<Byte>(r->KeySize/8);
	array<Byte>^ a2 = gcnew array<Byte>(r->KeySize/8);
	array<Byte>^ iv = gcnew array<Byte>(r->IV->Length);

	rand->NextBytes(a1);
	rand->NextBytes(a2);

	rand->NextBytes(iv);

	MemoryStream^   msEncrypt;
    CryptoStream^   csEncrypt;
    StreamWriter^   swEncrypt;

  	ICryptoTransform^ enc = r->CreateEncryptor(xorArrays(a1,a2), iv);

	msEncrypt = gcnew MemoryStream();
	csEncrypt = gcnew CryptoStream(msEncrypt, enc, System::Security::Cryptography::CryptoStreamMode::Write);
    swEncrypt = gcnew StreamWriter(csEncrypt);

	swEncrypt->Write(plaintext);
	swEncrypt->Flush();
	csEncrypt->FlushFinalBlock();
	msEncrypt->Flush();

	array<Byte>^ encrypted = msEncrypt->ToArray();
	String^ encbase = Convert::ToBase64String(encrypted);

	return encbase;
}

String^ BazaDanych::decryptXML(String^ encoded)//, array<Byte>^ key, array<Byte>^ iv)
{
	Random^ rand= gcnew Random(0xffddffee);
	array<Byte>^ encrypted = Convert::FromBase64String(encoded);

	String^ plaintext;

	MemoryStream^ msDecrypt;
	CryptoStream^ csDecrypt;
	StreamReader^ srDecrypt;

	RijndaelManaged^ r = gcnew RijndaelManaged;

	r->Padding = System::Security::Cryptography::PaddingMode::PKCS7;

	array<Byte>^ a1 = gcnew array<Byte>(r->KeySize/8);
	array<Byte>^ a2 = gcnew array<Byte>(r->KeySize/8);
	array<Byte>^ iv = gcnew array<Byte>(r->IV->Length);

	rand->NextBytes(a1);
	rand->NextBytes(a2);

	rand->NextBytes(iv);

	ICryptoTransform^ dec = r->CreateDecryptor(xorArrays(a1,a2), iv);

	msDecrypt = gcnew MemoryStream(encrypted);
	csDecrypt = gcnew CryptoStream(msDecrypt, dec, System::Security::Cryptography::CryptoStreamMode::Read);
	srDecrypt = gcnew StreamReader(csDecrypt);

	plaintext = srDecrypt->ReadToEnd();

	return plaintext;
}
vector<Strona>* BazaDanych::OdczytajListeStron(){
	ifstream in(*filename, std::ios::in | std::ios::binary);
	in.seekg(0, std::ios::end);

	string text="";
    text.resize(in.tellg());
	in.seekg(0, std::ios::beg);
    in.read(&text[0], text.size());
    in.close();
	
		char* temp = (char*)text.c_str();

	String^ zaszyfrowany = gcnew String(temp);
	String^ odszyfrowany = gcnew String(this->decryptXML(zaszyfrowany));

	char* txt =(char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(odszyfrowany).ToPointer();
	xmld->parse<0>(txt);
	
	vector<Strona>* strony = new vector<Strona>();
	readWebpages(xmld,strony);
	return strony;
};
void BazaDanych::ZapiszListeStron(vector<Strona>* listaStron){
	for(int i=0;i<listaStron->size();i++)
	{
		insertWebpageNode(listaStron->at(i),xmld,po);
	}
	String^ zaszyfrowany = encryptXML(xmld);

	ofstream in(*filename, std::ios::out | std::ios::binary | std::ios::trunc);
	//in.seekg(0, std::ios::end);
	char* k = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(zaszyfrowany).ToPointer();
	//in.write(k);
	in<<k<<endl;
	//string text="";
 //   text.resize(in.tellg());
	//in.seekg(0, std::ios::beg);
 //   in.read(&text[0], text.size());

    in.close();
	//Strona* s = new Strona("http://ssss.com","test46","1");
	
	//insertWebpageNode(*s,&x,po);
};