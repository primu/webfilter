#pragma once

namespace rppf {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OknoHasla2
	/// </summary>
	public ref class OknoHasla2 : public System::Windows::Forms::Form
	{
	public:
		OknoHasla2(void)
		{
			InitializeComponent();
			haslo=String::Empty;
			nowe=String::Empty;
			//
			//TODO: Add the constructor code here
			//
		}
		String^ ZHaslo()
		{
			return haslo;
		}
		String^ ZNowe()
		{
			return nowe;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OknoHasla2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MaskedTextBox^  MTBObecne;

	private: System::Windows::Forms::MaskedTextBox^  MTBNowe;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::MaskedTextBox^  MTBPonownie;
	private: System::Windows::Forms::Button^  BOk;
	private: System::Windows::Forms::Button^  BAnuluj;


	private:
		/// <summary>
		/// Required designer variable.
		String^ haslo;
		String^ nowe;
		void nacisniecieKlawisza()
		{
			if(String::IsNullOrEmpty(MTBObecne->Text))
			 {
				 MessageBox::Show("Obecne has³o jest puste!");
			 }
			 else
			 {
				 if(String::IsNullOrEmpty(MTBNowe->Text) || String::IsNullOrEmpty(MTBPonownie->Text))
				 {
					 MessageBox::Show("Nowe has³o nie mo¿e byæ puste!");
				 }else
				 {
					 if(MTBNowe->Text!=MTBPonownie->Text)
					 {
						 MessageBox::Show("Has³a ró¿ni¹ siê!");
					 }else
					 {
						 haslo=MTBObecne->Text;
						 nowe=MTBNowe->Text;
						 this->Hide();
					 }
				 }
			 }
		}
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->MTBObecne = (gcnew System::Windows::Forms::MaskedTextBox());
			this->MTBNowe = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->MTBPonownie = (gcnew System::Windows::Forms::MaskedTextBox());
			this->BOk = (gcnew System::Windows::Forms::Button());
			this->BAnuluj = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(130, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"WprowadŸ obecne has³o:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 79);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"WprowadŸ nowe has³o:";
			// 
			// MTBObecne
			// 
			this->MTBObecne->Location = System::Drawing::Point(16, 30);
			this->MTBObecne->Name = L"MTBObecne";
			this->MTBObecne->Size = System::Drawing::Size(223, 20);
			this->MTBObecne->TabIndex = 1;
			this->MTBObecne->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OknoHasla2::MTBObecne_KeyDown);
			// 
			// MTBNowe
			// 
			this->MTBNowe->Location = System::Drawing::Point(16, 95);
			this->MTBNowe->Name = L"MTBNowe";
			this->MTBNowe->Size = System::Drawing::Size(223, 20);
			this->MTBNowe->TabIndex = 2;
			this->MTBNowe->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OknoHasla2::MTBNowe_KeyDown);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 121);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(169, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"WprowadŸ nowe has³o ponownie:";
			// 
			// MTBPonownie
			// 
			this->MTBPonownie->Location = System::Drawing::Point(16, 137);
			this->MTBPonownie->Name = L"MTBPonownie";
			this->MTBPonownie->Size = System::Drawing::Size(223, 20);
			this->MTBPonownie->TabIndex = 3;
			this->MTBPonownie->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OknoHasla2::MTBPonownie_KeyDown);
			// 
			// BOk
			// 
			this->BOk->Location = System::Drawing::Point(15, 163);
			this->BOk->Name = L"BOk";
			this->BOk->Size = System::Drawing::Size(106, 35);
			this->BOk->TabIndex = 4;
			this->BOk->Text = L"OK";
			this->BOk->UseVisualStyleBackColor = true;
			this->BOk->Click += gcnew System::EventHandler(this, &OknoHasla2::BOk_Click);
			// 
			// BAnuluj
			// 
			this->BAnuluj->Location = System::Drawing::Point(133, 163);
			this->BAnuluj->Name = L"BAnuluj";
			this->BAnuluj->Size = System::Drawing::Size(106, 35);
			this->BAnuluj->TabIndex = 5;
			this->BAnuluj->Text = L"Anuluj";
			this->BAnuluj->UseVisualStyleBackColor = true;
			this->BAnuluj->Click += gcnew System::EventHandler(this, &OknoHasla2::BAnuluj_Click);
			// 
			// OknoHasla2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(251, 204);
			this->ControlBox = false;
			this->Controls->Add(this->BAnuluj);
			this->Controls->Add(this->BOk);
			this->Controls->Add(this->MTBPonownie);
			this->Controls->Add(this->MTBNowe);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->MTBObecne);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"OknoHasla2";
			this->Text = L"Zmiana has³a";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BAnuluj_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Hide();
			 }
private: System::Void BOk_Click(System::Object^  sender, System::EventArgs^  e) {
			 nacisniecieKlawisza();
			 /*if(String::IsNullOrEmpty(MTBObecne->Text))
			 {
				 MessageBox::Show("Obecne has³o jest puste!");
			 }
			 else
			 {
				 if(String::IsNullOrEmpty(MTBNowe->Text) || String::IsNullOrEmpty(MTBPonownie->Text))
				 {
					 MessageBox::Show("Nowe has³o nie mo¿e byæ puste!");
				 }else
				 {
					 if(MTBNowe->Text!=MTBPonownie->Text)
					 {
						 MessageBox::Show("Has³a ró¿ni¹ siê!");
					 }else
					 {
						 haslo=MTBObecne->Text;
						 nowe=MTBNowe->Text;
						 this->Hide();
					 }
				 }
			 }*/
		 }
private: System::Void MTBObecne_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode==Keys::Enter)
			 {
				 nacisniecieKlawisza();
			 }
		 }
private: System::Void MTBNowe_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode==Keys::Enter)
			 {
				nacisniecieKlawisza();
			 }
		 }
private: System::Void MTBPonownie_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode==Keys::Enter)
			 {
				nacisniecieKlawisza();
			 }
		 }
};
}
