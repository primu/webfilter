// rppf.cpp : main project file.


#include "stdafx.h"
#include "filtr.h"
#include "OknoGlowne.h"
#include "ConsoleTextWriter.h"
//#include <thread>
using namespace System::IO;
using namespace System;
using namespace System::Windows::Forms;
using namespace rppf;

int main(array<System::String ^> ^args)
{
	//TextWriter
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);	

	Application::Run(gcnew OknoGlowne());

	Environment::Exit(0);
}
