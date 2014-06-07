#pragma once

namespace rppf {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OknoStronyZ
	/// </summary>
	public ref class OknoStronyZ : public System::Windows::Forms::Form
	{
	public:
		OknoStronyZ(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OknoStronyZ()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  RTBKod;
	private: System::Windows::Forms::Button^  BZapisz;
	private: System::Windows::Forms::Button^  BAnuluj;
	protected: 

	protected: 



	private:
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
			this->RTBKod = (gcnew System::Windows::Forms::RichTextBox());
			this->BZapisz = (gcnew System::Windows::Forms::Button());
			this->BAnuluj = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// RTBKod
			// 
			this->RTBKod->Location = System::Drawing::Point(12, 12);
			this->RTBKod->Name = L"RTBKod";
			this->RTBKod->Size = System::Drawing::Size(478, 351);
			this->RTBKod->TabIndex = 0;
			this->RTBKod->Text = L"";
			// 
			// BZapisz
			// 
			this->BZapisz->Location = System::Drawing::Point(13, 370);
			this->BZapisz->Name = L"BZapisz";
			this->BZapisz->Size = System::Drawing::Size(120, 30);
			this->BZapisz->TabIndex = 1;
			this->BZapisz->Text = L"Zapisz";
			this->BZapisz->UseVisualStyleBackColor = true;
			// 
			// BAnuluj
			// 
			this->BAnuluj->Location = System::Drawing::Point(370, 370);
			this->BAnuluj->Name = L"BAnuluj";
			this->BAnuluj->Size = System::Drawing::Size(120, 30);
			this->BAnuluj->TabIndex = 2;
			this->BAnuluj->Text = L"Anuluj";
			this->BAnuluj->UseVisualStyleBackColor = true;
			// 
			// OknoStronyZ
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(502, 412);
			this->Controls->Add(this->BAnuluj);
			this->Controls->Add(this->BZapisz);
			this->Controls->Add(this->RTBKod);
			this->Name = L"OknoStronyZ";
			this->Text = L"Strona zastêpcza";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
