#pragma once
#include "stdafx.h"
//#include "OknoGlowne.h"

using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System;

ref class ConsoleTextWriter: public TextWriter
{
private:
	delegate void delegat(Char^ tt);
public:
	RichTextBox^ _output;
	ConsoleTextWriter(void);
	
	ConsoleTextWriter(RichTextBox^ output)
	{
		_output=output;
		
	}
	
	virtual void Write(Char value) override
	{
		TextWriter::Write(value);
		delegat^ del = gcnew delegat(this,&ConsoleTextWriter::zmien);
		_output->BeginInvoke(del,value);
		//_output->AppendText(value.ToString());
	}
	void zmien(Char^ t)
	{
		_output->AppendText(t->ToString());
	}
	property System::Text::Encoding^ Encoding {
		virtual System::Text::Encoding^ get() override {return System::Text::Encoding::UTF8;};
	};
	
};

//ref class cos:public ConsoleTextWriter
//{
//	cos(){;};
//	~cos(){;};
//};