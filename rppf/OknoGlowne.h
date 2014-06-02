#pragma once
#include "filtr.h"
#include "NowaStrona.h"
#include "ConsoleTextWriter.h"

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
	private: System::Windows::Forms::Label^  label1;

	private:
		delegate void AktualizujRTB(TextWriter^ ctw);
		void zmien(RichTextBox^ rtb, String^ wartosc)
		{
			rtb->AppendText(wartosc);
		}

		filtr^ silnik;
		bool gui;
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
			this->BZatrzymaj = (gcnew System::Windows::Forms::Button());
			this->BUruchom = (gcnew System::Windows::Forms::Button());
			this->LInfo = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->TPStrony = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->LVStrony = (gcnew System::Windows::Forms::ListView());
			this->CHUrl = (gcnew System::Windows::Forms::ColumnHeader());
			this->BModyfikujStrone = (gcnew System::Windows::Forms::Button());
			this->BUsunStrone = (gcnew System::Windows::Forms::Button());
			this->BDodajStrone = (gcnew System::Windows::Forms::Button());
			this->TPLog = (gcnew System::Windows::Forms::TabPage());
			this->RTBLog = (gcnew System::Windows::Forms::RichTextBox());
			this->TPUstawienia = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1->SuspendLayout();
			this->TPOgolne->SuspendLayout();
			this->TPStrony->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->TPLog->SuspendLayout();
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
			// 
			// TPOgolne
			// 
			this->TPOgolne->Controls->Add(this->BZatrzymaj);
			this->TPOgolne->Controls->Add(this->BUruchom);
			this->TPOgolne->Controls->Add(this->LInfo);
			this->TPOgolne->Controls->Add(this->label1);
			this->TPOgolne->Location = System::Drawing::Point(23, 4);
			this->TPOgolne->Name = L"TPOgolne";
			this->TPOgolne->Padding = System::Windows::Forms::Padding(3);
			this->TPOgolne->Size = System::Drawing::Size(635, 501);
			this->TPOgolne->TabIndex = 0;
			this->TPOgolne->Text = L"Ogolne";
			this->TPOgolne->UseVisualStyleBackColor = true;
			// 
			// BZatrzymaj
			// 
			this->BZatrzymaj->Location = System::Drawing::Point(401, 81);
			this->BZatrzymaj->Name = L"BZatrzymaj";
			this->BZatrzymaj->Size = System::Drawing::Size(104, 29);
			this->BZatrzymaj->TabIndex = 3;
			this->BZatrzymaj->Text = L"Zatrzymaj";
			this->BZatrzymaj->UseVisualStyleBackColor = true;
			this->BZatrzymaj->Click += gcnew System::EventHandler(this, &OknoGlowne::BZatrzymaj_Click);
			// 
			// BUruchom
			// 
			this->BUruchom->Enabled = false;
			this->BUruchom->Location = System::Drawing::Point(279, 81);
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
			this->LInfo->Location = System::Drawing::Point(97, 82);
			this->LInfo->Name = L"LInfo";
			this->LInfo->Size = System::Drawing::Size(123, 24);
			this->LInfo->TabIndex = 1;
			this->LInfo->Text = L"Uruchomiony";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(6, 78);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Silnik:";
			// 
			// TPStrony
			// 
			this->TPStrony->Controls->Add(this->splitContainer1);
			this->TPStrony->Location = System::Drawing::Point(23, 4);
			this->TPStrony->Name = L"TPStrony";
			this->TPStrony->Padding = System::Windows::Forms::Padding(3);
			this->TPStrony->Size = System::Drawing::Size(635, 501);
			this->TPStrony->TabIndex = 1;
			this->TPStrony->Text = L"Strony";
			this->TPStrony->UseVisualStyleBackColor = true;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(3, 3);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->LVStrony);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->BModyfikujStrone);
			this->splitContainer1->Panel2->Controls->Add(this->BUsunStrone);
			this->splitContainer1->Panel2->Controls->Add(this->BDodajStrone);
			this->splitContainer1->Size = System::Drawing::Size(629, 495);
			this->splitContainer1->SplitterDistance = 510;
			this->splitContainer1->TabIndex = 0;
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
			this->LVStrony->Size = System::Drawing::Size(510, 495);
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
			// BModyfikujStrone
			// 
			this->BModyfikujStrone->Location = System::Drawing::Point(5, 43);
			this->BModyfikujStrone->Name = L"BModyfikujStrone";
			this->BModyfikujStrone->Size = System::Drawing::Size(106, 33);
			this->BModyfikujStrone->TabIndex = 1;
			this->BModyfikujStrone->Text = L"Modyfikuj stronê";
			this->BModyfikujStrone->UseVisualStyleBackColor = true;
			this->BModyfikujStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BModyfikujStrone_Click);
			// 
			// BUsunStrone
			// 
			this->BUsunStrone->Location = System::Drawing::Point(5, 111);
			this->BUsunStrone->Name = L"BUsunStrone";
			this->BUsunStrone->Size = System::Drawing::Size(106, 41);
			this->BUsunStrone->TabIndex = 1;
			this->BUsunStrone->Text = L"Usuñ wybranê stronê";
			this->BUsunStrone->UseVisualStyleBackColor = true;
			this->BUsunStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BUsunStrone_Click);
			// 
			// BDodajStrone
			// 
			this->BDodajStrone->Location = System::Drawing::Point(5, 5);
			this->BDodajStrone->Name = L"BDodajStrone";
			this->BDodajStrone->Size = System::Drawing::Size(106, 33);
			this->BDodajStrone->TabIndex = 0;
			this->BDodajStrone->Text = L"Dodaj now¹ stronê";
			this->BDodajStrone->UseVisualStyleBackColor = true;
			this->BDodajStrone->Click += gcnew System::EventHandler(this, &OknoGlowne::BDodajStrone_Click);
			// 
			// TPLog
			// 
			this->TPLog->Controls->Add(this->RTBLog);
			this->TPLog->Location = System::Drawing::Point(23, 4);
			this->TPLog->Name = L"TPLog";
			this->TPLog->Size = System::Drawing::Size(635, 501);
			this->TPLog->TabIndex = 2;
			this->TPLog->Text = L"Log";
			this->TPLog->UseVisualStyleBackColor = true;
			// 
			// RTBLog
			// 
			this->RTBLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RTBLog->Location = System::Drawing::Point(0, 0);
			this->RTBLog->Name = L"RTBLog";
			this->RTBLog->ReadOnly = true;
			this->RTBLog->Size = System::Drawing::Size(635, 501);
			this->RTBLog->TabIndex = 0;
			this->RTBLog->Text = L"";
			// 
			// TPUstawienia
			// 
			this->TPUstawienia->Location = System::Drawing::Point(23, 4);
			this->TPUstawienia->Name = L"TPUstawienia";
			this->TPUstawienia->Padding = System::Windows::Forms::Padding(3);
			this->TPUstawienia->Size = System::Drawing::Size(635, 501);
			this->TPUstawienia->TabIndex = 3;
			this->TPUstawienia->Text = L"Ustawienia";
			this->TPUstawienia->UseVisualStyleBackColor = true;
			// 
			// OknoGlowne
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(662, 509);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"OknoGlowne";
			this->Text = L"Rafa³a i Przemka Program Filtruj¹cy";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &OknoGlowne::OknoGlowne_FormClosed);
			this->Load += gcnew System::EventHandler(this, &OknoGlowne::OknoGlowne_Load);
			this->tabControl1->ResumeLayout(false);
			this->TPOgolne->ResumeLayout(false);
			this->TPOgolne->PerformLayout();
			this->TPStrony->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->TPLog->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void OknoGlowne_Load(System::Object^  sender, System::EventArgs^  e) {
				 TextWriter^ a = gcnew ConsoleTextWriter(RTBLog);
				
				Console::SetOut(a);

				silnik= gcnew filtr();
				silnik->WczytajPlik();
				silnik->FWatek();

				 AktualizujListeStron();

				 if(silnik->FCzyUruchomiony())
				 {
					 LInfo->Text=L"Uruchomiony";
					 LInfo->ForeColor=Color::Green;
					 BUruchom->Enabled=false;
					 BZatrzymaj->Enabled=true;
				 }else
				 {
					 LInfo->Text=L"Wy³¹czony";
					 LInfo->ForeColor=Color::DarkRed;
					 BUruchom->Enabled=true;
					 BZatrzymaj->Enabled=false;
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
					LInfo->Text=L"Wy³¹czony";
					LInfo->ForeColor=Color::DarkRed;
					BUruchom->Enabled=true;
					BZatrzymaj->Enabled=false;
				}
				
		 }
private: System::Void BZatrzymaj_Click(System::Object^  sender, System::EventArgs^  e) {
				silnik->FZatrzymaj();//funkcja czekaj¹ca na w¹tek;
				if(silnik->FCzyUruchomiony())
				 {
					 LInfo->Text=L"Uruchomiony";
					 LInfo->ForeColor=Color::Green;
					 BUruchom->Enabled=false;
					 BZatrzymaj->Enabled=true;
				 }else
				 {
					 LInfo->Text=L"Wy³¹czony";
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
					MessageBox::Show("B³êdny adres lub strona ju¿ na liœcie!");
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
						 MessageBox::Show("B³êdny adres lub strona ju¿ na liœcie!");
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
};
}
