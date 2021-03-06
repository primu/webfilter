#pragma once
#include "filtr.h"
#include "NowaStrona.h"
#include "ConsoleTextWriter.h"
#include "PasswordHash.h"
#include "MyForm.h"
#include "OknoHasla2.h"

namespace rppf {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class OknoGlowne : public System::Windows::Forms::Form
	{
	public:
		
		OknoGlowne(void)
		{
			InitializeComponent();
			odblokowane=true;
			hash=String::Empty;
			gui=true;
			
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OknoGlowne()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected: 
	private: System::Windows::Forms::TabPage^  TPOgolne;
	private: System::Windows::Forms::TabPage^  TPStrony;
	private: System::Windows::Forms::TabPage^  TPLog;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::ListView^  LVStrony;

	private: System::Windows::Forms::Button^  BUsunStrone;
	private: System::Windows::Forms::Button^  BDodajStrone;
	private: System::Windows::Forms::RichTextBox^  RTBLog;
	private: System::Windows::Forms::Button^  BZatrzymaj;
	private: System::Windows::Forms::Button^  BUruchom;
	private: System::Windows::Forms::Label^  LInfo;
	private: System::Windows::Forms::TabPage^  TPUstawienia;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::SplitContainer^  splitContainer4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::SplitContainer^  splitContainer5;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  LLiczbaAStron;
	private: System::Windows::Forms::Label^  LLiczbaS;
	private: System::Windows::Forms::Label^  LLiczbaZStron;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ListView^  LVStronyZ;


	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::RadioButton^  RBWlasna;
	private: System::Windows::Forms::RadioButton^  RBDomyslna;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ColumnHeader^  CHNazwa;
	private: System::Windows::Forms::Button^  BUsunStroneZ;
	private: System::Windows::Forms::Button^  BDodajStroneZ;
	private: System::Windows::Forms::Button^  BUsunHaslo;
	private: System::Windows::Forms::Button^  BHaslo;
	private: System::Windows::Forms::Label^  label1;

	private:
		String^ hash;
	private: System::Windows::Forms::Button^  BOdblokuj;
			 bool odblokowane;

		String^ PobierzHaslo()
		{
			MyForm^ a = gcnew MyForm();
			a->ShowDialog();
			String^ b = a->zwrocHaslo();
			a->Close();
			return b;
		}
		bool SprawdzHaslo(String^ haslo)
		{
			PasswordHash^ gen = gcnew PasswordHash();
			if(!String::IsNullOrEmpty(hash))
			{
				if(!String::IsNullOrEmpty(haslo))
				{
					if(gen->ValidatePassword(haslo,hash))
					{
						return true;
					}
					MessageBox::Show("B喚dne has這!");
				}
				return false;
			}
			return true;
		}

		void ZablokujInterfejs()
		{
			odblokowane=false;
			BUruchom->Enabled=false;
			BZatrzymaj->Enabled=false;
			TPStrony->Enabled=false;
			TPUstawienia->Enabled=false;
		}
		void OdblokujInterfejs()
		{
			odblokowane=true;
			if(silnik->FCzyUruchomiony())
				BZatrzymaj->Enabled=true;
			else
				BUruchom->Enabled=true;
			TPStrony->Enabled=true;
			TPUstawienia->Enabled=true;
		}

		bool UtworzHaslo(String^ haslo)
		{
			PasswordHash^ gen = gcnew PasswordHash();
			if(String::IsNullOrEmpty(hash))
			{
				if(!String::IsNullOrEmpty(haslo))
				{
					hash = gen->CreateHash(haslo);
					MessageBox::Show("Utworzono has這!");
					return true;
				}
			}
			else
			{
				/*if(gen->ValidatePassword(haslo,hash))
				{*/
					hash = gen->CreateHash(haslo);
					MessageBox::Show("Has這 zosta這 zmienione!");
					return true;
				/*}
				else
				{
					MessageBox::Show("B喚dne has這!");
					return false;
				}*/
			}
			return false;
		}
		void UsunHaslo(String^ haslo)
		{
			PasswordHash^ gen = gcnew PasswordHash();
			if(!String::IsNullOrEmpty(haslo))
			{
				if(!String::IsNullOrEmpty(hash))
				{
					if(gen->ValidatePassword(haslo,hash))
					{
						hash = String::Empty;
						MessageBox::Show("Has這 usuni皻e!");
					}
					else
					{
						MessageBox::Show("B喚dne has這!");
					}
				}
			}
		}

		delegate void AktualizujRTB(TextWriter^ ctw);
		void zmien(RichTextBox^ rtb, String^ wartosc)
		{
			rtb->AppendText(wartosc);
		}

		filtr^ silnik;
		bool gui;
		void AktualizujStatystyki()
		{
			LLiczbaAStron->Text=silnik->FileAktywnych().ToString();
			LLiczbaS->Text=silnik->FileStron().ToString();
			LLiczbaZStron->Text=silnik->FileZablokowano().ToString();
		}
		void AktualizujListeStron()
		{
			gui=false;
			LVStrony->Items->Clear();
			std::vector<Strona> strony = silnik->FPobierzListeStron();
			for(int i=0;i<strony.size();i++)
			{
//				String^ s = gcnew String(strony[i].pobierzNazwe());
				
				String^ u = gcnew String(strony[i].pobierzUrl());
				ListViewItem^ temp = gcnew ListViewItem(u);
				temp->Checked=strony[i].czyAktywna();
				//temp->SubItems->Add(u);
				LVStrony->Items->Add(temp);
			}
			gui=true;
		}

	private: System::Windows::Forms::ColumnHeader^  CHUrl;
	private: System::Windows::Forms::Button^  BModyfikujStrone;

			 /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->TPOgolne = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer5 = (gcnew System::Windows::Forms::SplitContainer());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->BOdblokuj = (gcnew System::Windows::Forms::Button());
			this->LLiczbaAStron = (gcnew System::Windows::Forms::Label());
			this->LLiczbaS = (gcnew System::Windows::Forms::Label());
			this->LLiczbaZStron = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->BZatrzymaj = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BUruchom = (gcnew System::Windows::Forms::Button());
			this->LInfo = (gcnew System::Windows::Forms::Label());
			this->TPStrony = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->LVStrony = (gcnew System::Windows::Forms::ListView());
			this->CHUrl = (gcnew System::Windows::Forms::ColumnHeader());
			this->BUsunStrone = (gcnew System::Windows::Forms::Button());
			this->BDodajStrone = (gcnew System::Windows::Forms::Button());
			this->BModyfikujStrone = (gcnew System::Windows::Forms::Button());
			this->TPUstawienia = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer4 = (gcnew System::Windows::Forms::SplitContainer());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->BUsunStroneZ = (gcnew System::Windows::Forms::Button());
			this->BDodajStroneZ = (gcnew System::Windows::Forms::Button());
			this->LVStronyZ = (gcnew System::Windows::Forms::ListView());
			this->CHNazwa = (gcnew System::Windows::Forms::ColumnHeader());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->RBWlasna = (gcnew System::Windows::Forms::RadioButton());
			this->RBDomyslna = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->BUsunHaslo = (gcnew System::Windows::Forms::Button());
			this->BHaslo = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->TPLog = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->RTBLog = (gcnew System::Windows::Forms::RichTextBox());
			this->tabControl1->SuspendLayout();
			this->TPOgolne->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer5))->BeginInit();
			this->splitContainer5->Panel1->SuspendLayout();
			this->splitContainer5->Panel2->SuspendLayout();
			this->splitContainer5->SuspendLayout();
			this->TPStrony->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->TPUstawienia->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer4))->BeginInit();
			this->splitContainer4->Panel1->SuspendLayout();
			this->splitContainer4->Panel2->SuspendLayout();
			this->splitContainer4->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->TPLog->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer3))->BeginInit();
			this->splitContainer3->Panel1->SuspendLayout();
			this->splitContainer3->Panel2->SuspendLayout();
			this->splitContainer3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Left;
			this->tabControl1->Controls->Add(this->TPOgolne);
			this->tabControl1->Controls->Add(this->TPStrony);
			this->tabControl1->Controls->Add(this->TPUstawienia);
			this->tabControl1->Controls->Add(this->TPLog);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(662, 509);
			this->tabControl1->TabIndex = 0;
			this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &OknoGlowne::tabControl1_SelectedIndexChanged);
			// 
			// TPOgolne
			// 
			this->TPOgolne->BackColor = System::Drawing::Color::White;
			this->TPOgolne->Controls->Add(this->splitContainer5);
			this->TPOgolne->Location = System::Drawing::Point(23, 4);
			this->TPOgolne->Name = L"TPOgolne";
			this->TPOgolne->Padding = System::Windows::Forms::Padding(3);
			this->TPOgolne->Size = System::Drawing::Size(635, 501);
			this->TPOgolne->TabIndex = 0;
			this->TPOgolne->Text = L"Ogolne";
			// 
			// splitContainer5
			// 
			this->splitContainer5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer5->Location = System::Drawing::Point(3, 3);
			this->splitContainer5->Name = L"splitContainer5";
			this->splitContainer5->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer5.Panel1
			// 
			this->splitContainer5->Panel1->Controls->Add(this->label8);
			this->splitContainer5->Panel1->Controls->Add(this->label9);
			// 
			// splitContainer5.Panel2
			// 
			this->splitContainer5->Panel2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->splitContainer5->Panel2->Controls->Add(this->BOdblokuj);
			this->splitContainer5->Panel2->Controls->Add(this->LLiczbaAStron);
			this->splitContainer5->Panel2->Controls->Add(this->LLiczbaS);
			this->splitContainer5->Panel2->Controls->Add(this->LLiczbaZStron);
			this->splitContainer5->Panel2->Controls->Add(this->label12);
			this->splitContainer5->Panel2->Controls->Add(this->label11);
			this->splitContainer5->Panel2->Controls->Add(this->label10);
			this->splitContainer5->Panel2->Controls->Add(this->BZatrzymaj);
			this->splitContainer5->Panel2->Controls->Add(this->label1);
			this->splitContainer5->Panel2->Controls->Add(this->BUruchom);
			this->splitContainer5->Panel2->Controls->Add(this->LInfo);
			this->splitContainer5->Size = System::Drawing::Size(629, 495);
			this->splitContainer5->SplitterDistance = 88;
			this->splitContainer5->TabIndex = 4;
			// 
			// label8
			// 
			this->label8->Location = System::Drawing::Point(1, 32);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(622, 51);
			this->label8->TabIndex = 3;
			this->label8->Text = L"W tym oknie mo瞠sz sprawdzi� aktualny stan programu, statystk� blokowanych stron," 
				L" a tak瞠 zatrzyma� b鉅� uruchomi� us逝g� filtrowania.";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label9->Location = System::Drawing::Point(0, -3);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(101, 31);
			this->label9->TabIndex = 2;
			this->label9->Text = L"Og鏊ne";
			// 
			// BOdblokuj
			// 
			this->BOdblokuj->Location = System::Drawing::Point(558, 345);
			this->BOdblokuj->Name = L"BOdblokuj";
			this->BOdblokuj->Size = System::Drawing::Size(65, 53);
			this->BOdblokuj->TabIndex = 7;
			this->BOdblokuj->Text = L"Odblokuj";
			this->BOdblokuj->UseVisualStyleBackColor = true;
			this->BOdblokuj->Visible = false;
			this->BOdblokuj->Click += gcnew System::EventHandler(this, &OknoGlowne::BOdblokuj_Click);
			// 
			// LLiczbaAStron
			// 
			this->LLiczbaAStron->AutoSize = true;
			this->LLiczbaAStron->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->LLiczbaAStron->Location = System::Drawing::Point(302, 167);
			this->LLiczbaAStron->Name = L"LLiczbaAStron";
			this->LLiczbaAStron->Size = System::Drawing::Size(18, 20);
			this->LLiczbaAStron->TabIndex = 6;
			this->LLiczbaAStron->Text = L"0";
			// 
			// LLiczbaS
			// 
			this->LLiczbaS->AutoSize = true;
			this->LLiczbaS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->LLiczbaS->Location = System::Drawing::Point(302, 138);
			this->LLiczbaS->Name = L"LLiczbaS";
			this->LLiczbaS->Size = System::Drawing::Size(18, 20);
			this->LLiczbaS->TabIndex = 6;
			this->LLiczbaS->Text = L"0";
			// 
			// LLiczbaZStron
			// 
			this->LLiczbaZStron->AutoSize = true;
			this->LLiczbaZStron->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->LLiczbaZStron->ForeColor = System::Drawing::Color::DarkRed;
			this->LLiczbaZStron->Location = System::Drawing::Point(302, 96);
			this->LLiczbaZStron->Name = L"LLiczbaZStron";
			this->LLiczbaZStron->Size = System::Drawing::Size(19, 20);
			this->LLiczbaZStron->TabIndex = 6;
			this->LLiczbaZStron->Text = L"0";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label12->Location = System::Drawing::Point(7, 96);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(238, 20);
			this->label12->TabIndex = 5;
			this->label12->Text = L"Liczba zablokowanych stron:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label11->Location = System::Drawing::Point(7, 167);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(200, 20);
			this->label11->TabIndex = 4;
			this->label11->Text = L"Liczba aktywnych adres闚:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label10->Location = System::Drawing::Point(7, 138);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(283, 20);
			this->label10->TabIndex = 4;
			this->label10->Text = L"Liczba wszystkich adres闚 w systemie:";
			// 
			// BZatrzymaj
			// 
			this->BZatrzymaj->Location = System::Drawing::Point(401, 25);
			this->BZatrzymaj->Name = L"BZatrzymaj";
			this->BZatrzymaj->Size = System::Drawing::Size(104, 29);
			this->BZatrzymaj->TabIndex = 3;
			this->BZatrzymaj->Text = L"Zatrzymaj";
			this->BZatrzymaj->UseVisualStyleBackColor = true;
			this->BZatrzymaj->Click += gcnew System::EventHandler(this, &OknoGlowne::BZatrzymaj_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(6, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Silnik:";
			// 
			// BUruchom
			// 
			this->BUruchom->Enabled = false;
			this->BUruchom->Location = System::Drawing::Point(279, 25);
			this->BUruchom->Name = L"BUruchom";
			this->BUruchom->Size = System::Drawing::Size(104, 30);
			this->BUruchom->TabIndex = 2;
			this->BUruchom->Text = L"Uruchom";
			this->BUruchom->UseVisualStyleBackColor = true;
			this->BUruchom->Click += gcnew System::EventHandler(this, &OknoGlowne::BUruchom_Click);
			// 
			// LInfo
			// 
			this->LInfo->AutoSize = true;
			this->LInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->LInfo->Location = System::Drawing::Point(97, 26);
			this->LInfo->Name = L"LInfo";
			this->LInfo->Size = System::Drawing::Size(123, 24);
			this->LInfo->TabIndex = 1;
			this->LInfo->Text = L"Uruchomiony";
			// 
			// TPStrony
			// 
			this->TPStrony->BackColor = System::Drawing::Color::White;
			this->TPStrony->Controls->Add(this->splitContainer1);
			this->TPStrony->Location = System::Drawing::Point(23, 4);
			this->TPStrony->Name = L"TPStrony";
			this->TPStrony->Padding = System::Windows::Forms::Padding(3);
			this->TPStrony->Size = System::Drawing::Size(635, 501);
			this->TPStrony->TabIndex = 1;
			this->TPStrony->Text = L"Strony";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(3, 3);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->label3);
			this->splitContainer1->Panel1->Controls->Add(this->label2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->splitContainer2);
			this->splitContainer1->Size = System::Drawing::Size(629, 495);
			this->splitContainer1->SplitterDistance = 88;
			this->splitContainer1->TabIndex = 0;
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(1, 32);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(622, 51);
			this->label3->TabIndex = 1;
			this->label3->Text = L"W tym oknie mo瞠sz zarz鉅za� wpisami bokowanych stron. Masz mo磧iwo�� definiowani" 
				L"a nowych domen oraz s堯w kluczowych, kt鏎e po odnalezieniu zostan� zablokowane.";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(0, -3);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 31);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Strony";
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->LVStrony);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->splitContainer2->Panel2->Controls->Add(this->BUsunStrone);
			this->splitContainer2->Panel2->Controls->Add(this->BDodajStrone);
			this->splitContainer2->Panel2->Controls->Add(this->BModyfikujStrone);
			this->splitContainer2->Size = System::Drawing::Size(629, 403);
			this->splitContainer2->SplitterDistance = 510;
			this->splitContainer2->TabIndex = 0;
			// 
			// LVStrony
			// 
			this->LVStrony->CheckBoxes = true;
			this->LVStrony->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->CHUrl});
			this->LVStrony->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LVStrony->FullRowSelect = true;
			this->LVStrony->GridLines = true;
			this->LVStrony->Location = System::Drawing::Point(0, 0);
			this->LVStrony->MultiSelect = false;
			this->LVStrony->Name = L"LVStrony";
			this->LVStrony->Size = System::Drawing::Size(510, 403);
			this->LVStrony->TabIndex = 0;
			this->LVStrony->UseCompatibleStateImageBehavior = false;
			this->LVStrony->View = System::Windows::Forms::View::Details;
			this->LVStrony->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &OknoGlowne::LVStrony_ItemCheck);
			// 
			// CHUrl
			// 
			this->CHUrl->Text = L"URL";
			this->CHUrl->Width = 503;
			// 
			// BUsunStrone
			// 
			this->BUsunStrone->Location = System::Drawing::Point(6, 106);
			this->BUsunStrone->Name = L"BUsunStrone";
			this->BUsunStrone->Size = System::Drawing::Size(106, 41);
			this->BUsunStrone->TabIndex = 1;
			this->BUsunStrone->Text = L"Usu� wybran� stron�";
			this->BUsunStrone->UseVisualStyleBackColor = true;
			this->BUsunStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BUsunStrone_Click);
			// 
			// BDodajStrone
			// 
			this->BDodajStrone->Location = System::Drawing::Point(6, 3);
			this->BDodajStrone->Name = L"BDodajStrone";
			this->BDodajStrone->Size = System::Drawing::Size(106, 33);
			this->BDodajStrone->TabIndex = 0;
			this->BDodajStrone->Text = L"Dodaj now� stron�";
			this->BDodajStrone->UseVisualStyleBackColor = true;
			this->BDodajStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BDodajStrone_Click);
			// 
			// BModyfikujStrone
			// 
			this->BModyfikujStrone->Location = System::Drawing::Point(6, 42);
			this->BModyfikujStrone->Name = L"BModyfikujStrone";
			this->BModyfikujStrone->Size = System::Drawing::Size(106, 33);
			this->BModyfikujStrone->TabIndex = 1;
			this->BModyfikujStrone->Text = L"Modyfikuj stron�";
			this->BModyfikujStrone->UseVisualStyleBackColor = true;
			this->BModyfikujStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BModyfikujStrone_Click);
			// 
			// TPUstawienia
			// 
			this->TPUstawienia->BackColor = System::Drawing::Color::White;
			this->TPUstawienia->Controls->Add(this->splitContainer4);
			this->TPUstawienia->Location = System::Drawing::Point(23, 4);
			this->TPUstawienia->Name = L"TPUstawienia";
			this->TPUstawienia->Padding = System::Windows::Forms::Padding(3);
			this->TPUstawienia->Size = System::Drawing::Size(635, 501);
			this->TPUstawienia->TabIndex = 3;
			this->TPUstawienia->Text = L"Ustawienia";
			// 
			// splitContainer4
			// 
			this->splitContainer4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer4->Location = System::Drawing::Point(3, 3);
			this->splitContainer4->Name = L"splitContainer4";
			this->splitContainer4->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer4.Panel1
			// 
			this->splitContainer4->Panel1->Controls->Add(this->label6);
			this->splitContainer4->Panel1->Controls->Add(this->label7);
			// 
			// splitContainer4.Panel2
			// 
			this->splitContainer4->Panel2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->splitContainer4->Panel2->Controls->Add(this->groupBox2);
			this->splitContainer4->Panel2->Controls->Add(this->groupBox1);
			this->splitContainer4->Panel2->Controls->Add(this->button1);
			this->splitContainer4->Size = System::Drawing::Size(629, 495);
			this->splitContainer4->SplitterDistance = 88;
			this->splitContainer4->TabIndex = 0;
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(1, 32);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(622, 51);
			this->label6->TabIndex = 3;
			this->label6->Text = L"W tym oknie mo瞠sz zdefiniowa� w豉sn� stron� b喚du po zablokowaniu strony, a tak�" 
				L"e zmieni� inne parametry programu.";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label7->Location = System::Drawing::Point(0, -3);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(148, 31);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Ustawienia";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->BUsunStroneZ);
			this->groupBox2->Controls->Add(this->BDodajStroneZ);
			this->groupBox2->Controls->Add(this->LVStronyZ);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->RBWlasna);
			this->groupBox2->Controls->Add(this->RBDomyslna);
			this->groupBox2->Location = System::Drawing::Point(6, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(338, 397);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Strona zast瘼cza";
			// 
			// BUsunStroneZ
			// 
			this->BUsunStroneZ->Enabled = false;
			this->BUsunStroneZ->Location = System::Drawing::Point(223, 356);
			this->BUsunStroneZ->Name = L"BUsunStroneZ";
			this->BUsunStroneZ->Size = System::Drawing::Size(109, 35);
			this->BUsunStroneZ->TabIndex = 3;
			this->BUsunStroneZ->Text = L"Usu� stron�";
			this->BUsunStroneZ->UseVisualStyleBackColor = true;
			// 
			// BDodajStroneZ
			// 
			this->BDodajStroneZ->Enabled = false;
			this->BDodajStroneZ->Location = System::Drawing::Point(6, 356);
			this->BDodajStroneZ->Name = L"BDodajStroneZ";
			this->BDodajStroneZ->Size = System::Drawing::Size(211, 35);
			this->BDodajStroneZ->TabIndex = 3;
			this->BDodajStroneZ->Text = L"Dodaj stron�";
			this->BDodajStroneZ->UseVisualStyleBackColor = true;
			// 
			// LVStronyZ
			// 
			this->LVStronyZ->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->CHNazwa});
			this->LVStronyZ->Enabled = false;
			this->LVStronyZ->GridLines = true;
			this->LVStronyZ->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->LVStronyZ->HideSelection = false;
			this->LVStronyZ->Location = System::Drawing::Point(10, 83);
			this->LVStronyZ->MultiSelect = false;
			this->LVStronyZ->Name = L"LVStronyZ";
			this->LVStronyZ->Size = System::Drawing::Size(322, 266);
			this->LVStronyZ->TabIndex = 2;
			this->LVStronyZ->UseCompatibleStateImageBehavior = false;
			this->LVStronyZ->View = System::Windows::Forms::View::Details;
			// 
			// CHNazwa
			// 
			this->CHNazwa->Text = L"Nazwa";
			this->CHNazwa->Width = 316;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(7, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(205, 13);
			this->label13->TabIndex = 1;
			this->label13->Text = L"Wybierz stron� wysy豉n� do u篡tkownika:";
			// 
			// RBWlasna
			// 
			this->RBWlasna->AutoSize = true;
			this->RBWlasna->Location = System::Drawing::Point(10, 59);
			this->RBWlasna->Name = L"RBWlasna";
			this->RBWlasna->Size = System::Drawing::Size(66, 17);
			this->RBWlasna->TabIndex = 0;
			this->RBWlasna->Text = L"W豉sna:";
			this->RBWlasna->UseVisualStyleBackColor = true;
			// 
			// RBDomyslna
			// 
			this->RBDomyslna->AutoSize = true;
			this->RBDomyslna->Checked = true;
			this->RBDomyslna->Location = System::Drawing::Point(10, 36);
			this->RBDomyslna->Name = L"RBDomyslna";
			this->RBDomyslna->Size = System::Drawing::Size(71, 17);
			this->RBDomyslna->TabIndex = 0;
			this->RBDomyslna->TabStop = true;
			this->RBDomyslna->Text = L"Domy�lna";
			this->RBDomyslna->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->BUsunHaslo);
			this->groupBox1->Controls->Add(this->BHaslo);
			this->groupBox1->Location = System::Drawing::Point(350, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(273, 105);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Has這 administratora";
			// 
			// BUsunHaslo
			// 
			this->BUsunHaslo->Location = System::Drawing::Point(6, 59);
			this->BUsunHaslo->Name = L"BUsunHaslo";
			this->BUsunHaslo->Size = System::Drawing::Size(261, 35);
			this->BUsunHaslo->TabIndex = 3;
			this->BUsunHaslo->Text = L"Usu� has這";
			this->BUsunHaslo->UseVisualStyleBackColor = true;
			this->BUsunHaslo->Click += gcnew System::EventHandler(this, &OknoGlowne::BUsunHaslo_Click);
			// 
			// BHaslo
			// 
			this->BHaslo->Location = System::Drawing::Point(6, 18);
			this->BHaslo->Name = L"BHaslo";
			this->BHaslo->Size = System::Drawing::Size(261, 35);
			this->BHaslo->TabIndex = 3;
			this->BHaslo->Text = L"Utw鏎z/Zmie� has這";
			this->BHaslo->UseVisualStyleBackColor = true;
			this->BHaslo->Click += gcnew System::EventHandler(this, &OknoGlowne::BHaslo_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(495, 364);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(111, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Test bazy danych";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &OknoGlowne::button1_Click);
			// 
			// TPLog
			// 
			this->TPLog->BackColor = System::Drawing::Color::White;
			this->TPLog->Controls->Add(this->splitContainer3);
			this->TPLog->Location = System::Drawing::Point(23, 4);
			this->TPLog->Name = L"TPLog";
			this->TPLog->Size = System::Drawing::Size(635, 501);
			this->TPLog->TabIndex = 2;
			this->TPLog->Text = L"Log";
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->Location = System::Drawing::Point(0, 0);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this->splitContainer3->Panel1->Controls->Add(this->label4);
			this->splitContainer3->Panel1->Controls->Add(this->label5);
			// 
			// splitContainer3.Panel2
			// 
			this->splitContainer3->Panel2->Controls->Add(this->RTBLog);
			this->splitContainer3->Size = System::Drawing::Size(635, 501);
			this->splitContainer3->SplitterDistance = 88;
			this->splitContainer3->TabIndex = 1;
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(4, 35);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(622, 51);
			this->label4->TabIndex = 3;
			this->label4->Text = L"W tym oknie mo瞠sz przegl鉅a� komunikaty otrzymywane od silnika aplikacji.";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(59, 31);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Log";
			// 
			// RTBLog
			// 
			this->RTBLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RTBLog->Location = System::Drawing::Point(0, 0);
			this->RTBLog->Name = L"RTBLog";
			this->RTBLog->ReadOnly = true;
			this->RTBLog->Size = System::Drawing::Size(635, 409);
			this->RTBLog->TabIndex = 0;
			this->RTBLog->Text = L"";
			// 
			// OknoGlowne
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(662, 509);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"OknoGlowne";
			this->Text = L"Rafa豉 i Przemka Program Filtruj鉍y";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &OknoGlowne::OknoGlowne_FormClosed);
			this->Load += gcnew System::EventHandler(this, &OknoGlowne::OknoGlowne_Load);
			this->tabControl1->ResumeLayout(false);
			this->TPOgolne->ResumeLayout(false);
			this->splitContainer5->Panel1->ResumeLayout(false);
			this->splitContainer5->Panel1->PerformLayout();
			this->splitContainer5->Panel2->ResumeLayout(false);
			this->splitContainer5->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer5))->EndInit();
			this->splitContainer5->ResumeLayout(false);
			this->TPStrony->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->TPUstawienia->ResumeLayout(false);
			this->splitContainer4->Panel1->ResumeLayout(false);
			this->splitContainer4->Panel1->PerformLayout();
			this->splitContainer4->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer4))->EndInit();
			this->splitContainer4->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->TPLog->ResumeLayout(false);
			this->splitContainer3->Panel1->ResumeLayout(false);
			this->splitContainer3->Panel1->PerformLayout();
			this->splitContainer3->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer3))->EndInit();
			this->splitContainer3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void OknoGlowne_Load(System::Object^  sender, System::EventArgs^  e) {
				 TextWriter^ a = gcnew ConsoleTextWriter(RTBLog);
				
				Console::SetOut(a);

				silnik= gcnew filtr();
				silnik->WczytajPlik();
				silnik->FWatek();

				gui=false;
				 AktualizujListeStron();
				 gui=true;
				 AktualizujStatystyki();

				 if(silnik->FCzyUruchomiony())
				 {
					 LInfo->Text=L"Uruchomiony";
					 LInfo->ForeColor=Color::Green;
					 BUruchom->Enabled=false;
					 BZatrzymaj->Enabled=true;
				 }else
				 {
					 LInfo->Text=L"Wy章czony";
					 LInfo->ForeColor=Color::DarkRed;
					 BUruchom->Enabled=true;
					 BZatrzymaj->Enabled=false;
				 }
				 if(String::IsNullOrEmpty(hash))
				 {
					 OdblokujInterfejs();
				 }else
				 {
					 if(!SprawdzHaslo(PobierzHaslo()))
						ZablokujInterfejs();
					 else
						 OdblokujInterfejs();
				 }
			 }
private: System::Void BUruchom_Click(System::Object^  sender, System::EventArgs^  e) {
				silnik->FWatek();
				if(silnik->FCzyUruchomiony())
				{
					LInfo->Text=L"Uruchomiony";
					LInfo->ForeColor=Color::Green;
					BUruchom->Enabled=false;
					BZatrzymaj->Enabled=true;
				}else
				{
					LInfo->Text=L"Wy章czony";
					LInfo->ForeColor=Color::DarkRed;
					BUruchom->Enabled=true;
					BZatrzymaj->Enabled=false;
				}
				
		 }
private: System::Void BZatrzymaj_Click(System::Object^  sender, System::EventArgs^  e) {
				silnik->FZatrzymaj();//funkcja czekaj鉍a na w靖ek;
				if(silnik->FCzyUruchomiony())
				 {
					 LInfo->Text=L"Uruchomiony";
					 LInfo->ForeColor=Color::Green;
					 BUruchom->Enabled=false;
					 BZatrzymaj->Enabled=true;
				 }else
				 {
					 LInfo->Text=L"Wy章czony";
					 LInfo->ForeColor=Color::DarkRed;
					 BUruchom->Enabled=true;
					 BZatrzymaj->Enabled=false;
				 }
		 }
private: System::Void BDodajStrone_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ url;// = gcnew String("");
			 NowaStrona^ okienko = gcnew NowaStrona();
			 okienko->ShowDialog();
			 okienko->Wartosc(url);
			 
			 if(!String::IsNullOrEmpty(url))
			 {
				 try{
					Strona temp((char*)(Marshal::StringToHGlobalAnsi(url)).ToPointer());
					silnik->FDodajStrone(temp);
					AktualizujListeStron();
				 }catch(Exception ^e)
				 {
					MessageBox::Show("B喚dny adres lub strona ju� na li�cie!");
				 }
				
			 }
		 }
private: System::Void BUsunStrone_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ a;
			 if(LVStrony->SelectedItems->Count==1)
			 {
				a = LVStrony->SelectedItems[0]->Text;
			 }
			 if(!String::IsNullOrEmpty(a))
			 {
				 silnik->FUsunStrone((char*)(Marshal::StringToHGlobalAnsi(a)).ToPointer());
				 AktualizujListeStron();
			 }
		 }
private: System::Void BModyfikujStrone_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ a;
			 if(LVStrony->SelectedItems->Count==1)
			 {
				a = LVStrony->SelectedItems[0]->Text;
			 }
			 if(!String::IsNullOrEmpty(a))
			 {
				 String^ url;// = gcnew String("");
				 NowaStrona^ okienko = gcnew NowaStrona(a);
				 okienko->ShowDialog();
				 okienko->Wartosc(url);

				 if(!String::IsNullOrEmpty(url))
				 {
					 try{
						Strona temp((char*)(Marshal::StringToHGlobalAnsi(url)).ToPointer());
						silnik->FUsunStrone((char*)(Marshal::StringToHGlobalAnsi(a)).ToPointer());
						silnik->FDodajStrone(temp);

						AktualizujListeStron();
					 }catch(Exception ^e)
					 {
						 MessageBox::Show("B喚dny adres lub strona ju� na li�cie!");
					 }
				 }

				 
			 }

		 }
private: System::Void LVStrony_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) {
			 if(gui)
			 {
				 if(e->CurrentValue == CheckState::Unchecked)
				 {
					 silnik->FAktywujStrone(true,(char*)(Marshal::StringToHGlobalAnsi(this->LVStrony->Items[e->Index]->Text)).ToPointer());
				 }else
				 {
					 if(e->CurrentValue == CheckState::Checked)
						silnik->FAktywujStrone(false,(char*)(Marshal::StringToHGlobalAnsi(this->LVStrony->Items[e->Index]->Text)).ToPointer());
				 }
			 }
		 }

private: System::Void OknoGlowne_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 if(!silnik->FCzyUruchomiony())
				silnik->FZatrzymaj();
		 }

private: System::Void tabControl1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(tabControl1->SelectedTab==tabControl1->TabPages["TPOgolne"])
				 AktualizujStatystyki();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 silnik->ZapiszDoPliku();
		 }
private: System::Void BHaslo_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(String::IsNullOrEmpty(hash))
			 {
				 if(UtworzHaslo(PobierzHaslo()))
				 {
					BOdblokuj->Visible=true;
					BOdblokuj->Text="Zablokuj";
				 }
			 }else
			 {
				 OknoHasla2^ aa = gcnew OknoHasla2();
				 aa->ShowDialog();
				 String^ h = aa->ZHaslo();
				 String^ n = aa->ZNowe();
				 if(!String::IsNullOrEmpty(h) || !String::IsNullOrEmpty(n))
				 {
					 if(SprawdzHaslo(h))
					 {
						 if(UtworzHaslo(n))
						 {
							 BOdblokuj->Visible=true;
							 BOdblokuj->Text="Zablokuj";
						 }
					 }
				 }
			 }
		 }
private: System::Void BUsunHaslo_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!String::IsNullOrEmpty(hash))
			 {
				 if(MessageBox::Show("Czy na pewno chcesz usun寞 has這?","Usuwanie has豉",MessageBoxButtons::YesNo,MessageBoxIcon::Question)==::DialogResult::Yes)
				 {
					UsunHaslo(PobierzHaslo());
					BOdblokuj->Visible=false;
				 }
			 }
		 }
private: System::Void BOdblokuj_Click(System::Object^  sender, System::EventArgs^  e) {
				if(String::IsNullOrEmpty(hash))
				{
					BOdblokuj->Visible=false;
					BOdblokuj->Text="Zablokuj";
					OdblokujInterfejs();
				}else
				{
					if(!odblokowane)
					{
						if(!SprawdzHaslo(PobierzHaslo()))
						{
							BOdblokuj->Text="Odblokuj";
							ZablokujInterfejs();
						}
						else
						{
							BOdblokuj->Text="Zablokuj";
							OdblokujInterfejs();
						}
					}else
					{
						BOdblokuj->Text="Odblokuj";
						ZablokujInterfejs();
					}
				}
		 }
};
}
