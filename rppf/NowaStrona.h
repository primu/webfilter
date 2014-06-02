#pragma once

namespace rppf {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NowaStrona
	/// </summary>
	public ref class NowaStrona : public System::Windows::Forms::Form
	{
	public:
		NowaStrona(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		NowaStrona(String^ adres)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			this->Text="Modyfikuj stronê";
			this->TBUrl->Text=adres;
		}
		void Wartosc(String^% url){
			url=this->url;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NowaStrona()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BDodaj;
	protected: 
	private: System::Windows::Forms::Button^  BAnuluj;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  TBUrl;

	private:
		/// <summary>
		/// Required designer variable.
		String^ url;
	private: System::Windows::Forms::Label^  label1;
			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->BDodaj = (gcnew System::Windows::Forms::Button());
			this->BAnuluj = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TBUrl = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// BDodaj
			// 
			this->BDodaj->Location = System::Drawing::Point(12, 70);
			this->BDodaj->Name = L"BDodaj";
			this->BDodaj->Size = System::Drawing::Size(103, 33);
			this->BDodaj->TabIndex = 0;
			this->BDodaj->Text = L"Dodaj";
			this->BDodaj->UseVisualStyleBackColor = true;
			this->BDodaj->Click += gcnew System::EventHandler(this, &NowaStrona::BDodaj_Click);
			// 
			// BAnuluj
			// 
			this->BAnuluj->Location = System::Drawing::Point(182, 70);
			this->BAnuluj->Name = L"BAnuluj";
			this->BAnuluj->Size = System::Drawing::Size(103, 33);
			this->BAnuluj->TabIndex = 1;
			this->BAnuluj->Text = L"Anuluj";
			this->BAnuluj->UseVisualStyleBackColor = true;
			this->BAnuluj->Click += gcnew System::EventHandler(this, &NowaStrona::BAnuluj_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(134, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Adres lub s³owo kluczowe:";
			// 
			// TBUrl
			// 
			this->TBUrl->Location = System::Drawing::Point(12, 44);
			this->TBUrl->Name = L"TBUrl";
			this->TBUrl->Size = System::Drawing::Size(273, 20);
			this->TBUrl->TabIndex = 5;
			this->TBUrl->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NowaStrona::TBUrl_KeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(12, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(270, 12);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Np. example.com, *.example.com, exampleKeyword, example.*";
			// 
			// NowaStrona
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(289, 112);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TBUrl);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->BAnuluj);
			this->Controls->Add(this->BDodaj);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"NowaStrona";
			this->Text = L"Nowa strona";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BDodaj_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->url = gcnew String(TBUrl->Text->ToCharArray());
				 this->Hide();
			 }
private: System::Void BAnuluj_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void TBUrl_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode==Keys::Enter)
			 {
				 this->url = gcnew String(TBUrl->Text->ToCharArray());
				 this->Hide();
			 }
		 }
};
}
