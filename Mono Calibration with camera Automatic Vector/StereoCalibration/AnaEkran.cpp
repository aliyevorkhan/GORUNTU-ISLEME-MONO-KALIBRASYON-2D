#include "AnaEkran.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	StereoCalibration::AnaEkran form;
	Application::Run(%form);
}