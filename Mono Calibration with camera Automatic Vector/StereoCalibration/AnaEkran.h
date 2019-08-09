#pragma once

#include "fonksiyonlar.h"
using namespace System::IO;

LPCTSTR giris;
LPCTSTR cikis;
int width;
int height;
long size1;
BYTE* buffer;

int calibX, calibY, calibZ = 0;
int calibCount = 0;

float* dunya;
float* imge;
float* projeksiyon = new float[12];
float* maksimumDeger = new float[1];

int p1x, p1y, p2x, p2y, p3x, p3y;
float w1x, w1y, w2x, w2y, w3x, w3y;

double mesafe;
int alan;
int tahtaBoyutu = 0;
int kalibrasyonEsik = 0;
vector <int> vecXY;
vector <int> vecManual;
vector <int> vecTiklanan;
namespace StereoCalibration {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AnaEkran
	/// </summary>
	public ref class AnaEkran : public System::Windows::Forms::Form
	{
	public:
		AnaEkran(void)
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
		~AnaEkran()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;


	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private: System::Windows::Forms::RadioButton^  radioButton1;



	private: System::Windows::Forms::Label^  label1;













	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button2;




	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::ToolStripMenuItem^  onlineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openCameraToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  offlineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  uploadImageToolStripMenuItem;
	private: System::Windows::Forms::Label^  label12;




	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label13;

	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::ToolStripMenuItem^  autoCalibrateToolStripMenuItem;
	private: System::Windows::Forms::Button^  button4;








	private: System::Windows::Forms::RichTextBox^  richTextBox4;
	private: System::Windows::Forms::RichTextBox^  richTextBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label9;

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ImageList^  ımageList1;
	private: System::Windows::Forms::Button^  button1;
	private: System::ComponentModel::IContainer^  components;
















	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AnaEkran::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->onlineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openCameraToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->offlineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->uploadImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->autoCalibrateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->ımageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->richTextBox4 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(254, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(360, 505);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AnaEkran::pictureBox1_MouseClick);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &AnaEkran::pictureBox1_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::White;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->onlineToolStripMenuItem,
					this->offlineToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(618, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// onlineToolStripMenuItem
			// 
			this->onlineToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openCameraToolStripMenuItem });
			this->onlineToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"onlineToolStripMenuItem.Image")));
			this->onlineToolStripMenuItem->Name = L"onlineToolStripMenuItem";
			this->onlineToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->onlineToolStripMenuItem->Text = L"Çevrimiçi";
			// 
			// openCameraToolStripMenuItem
			// 
			this->openCameraToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"openCameraToolStripMenuItem.Image")));
			this->openCameraToolStripMenuItem->Name = L"openCameraToolStripMenuItem";
			this->openCameraToolStripMenuItem->Size = System::Drawing::Size(138, 22);
			this->openCameraToolStripMenuItem->Text = L"Kamerayı aç";
			this->openCameraToolStripMenuItem->Click += gcnew System::EventHandler(this, &AnaEkran::openCameraToolStripMenuItem_Click);
			// 
			// offlineToolStripMenuItem
			// 
			this->offlineToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->uploadImageToolStripMenuItem,
					this->autoCalibrateToolStripMenuItem
			});
			this->offlineToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"offlineToolStripMenuItem.Image")));
			this->offlineToolStripMenuItem->Name = L"offlineToolStripMenuItem";
			this->offlineToolStripMenuItem->Size = System::Drawing::Size(91, 20);
			this->offlineToolStripMenuItem->Text = L"Çevrimdışı";
			// 
			// uploadImageToolStripMenuItem
			// 
			this->uploadImageToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"uploadImageToolStripMenuItem.Image")));
			this->uploadImageToolStripMenuItem->Name = L"uploadImageToolStripMenuItem";
			this->uploadImageToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->uploadImageToolStripMenuItem->Text = L"Görüntü yükle";
			this->uploadImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &AnaEkran::uploadImageToolStripMenuItem_Click);
			// 
			// autoCalibrateToolStripMenuItem
			// 
			this->autoCalibrateToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"autoCalibrateToolStripMenuItem.Image")));
			this->autoCalibrateToolStripMenuItem->Name = L"autoCalibrateToolStripMenuItem";
			this->autoCalibrateToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->autoCalibrateToolStripMenuItem->Text = L"Kalibrasyon noktalarını bul";
			this->autoCalibrateToolStripMenuItem->Click += gcnew System::EventHandler(this, &AnaEkran::autoCalibrateToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// radioButton1
			// 
			this->radioButton1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->radioButton1->ImageKey = L"manual.png";
			this->radioButton1->ImageList = this->ımageList1;
			this->radioButton1->Location = System::Drawing::Point(79, 186);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(112, 37);
			this->radioButton1->TabIndex = 3;
			this->radioButton1->Text = L"           Manuel Kalibrason";
			this->radioButton1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// ımageList1
			// 
			this->ımageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"ımageList1.ImageStream")));
			this->ımageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->ımageList1->Images->SetKeyName(0, L"calculateGeo.png");
			this->ımageList1->Images->SetKeyName(1, L"reset1.png");
			this->ımageList1->Images->SetKeyName(2, L"calibrate1.png");
			this->ımageList1->Images->SetKeyName(3, L"manual.png");
			this->ımageList1->Images->SetKeyName(4, L"distance.png");
			this->ımageList1->Images->SetKeyName(5, L"curve.png");
			this->ımageList1->Images->SetKeyName(6, L"area.png");
			this->ımageList1->Images->SetKeyName(7, L"result.png");
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label1->Location = System::Drawing::Point(4, 5);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(157, 15);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Kalibrasyon noktalarinin sayisi : ";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label12->Location = System::Drawing::Point(6, 43);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(141, 15);
			this->label12->TabIndex = 11;
			this->label12->Text = L"Kalibrasyon tahtası boyutu : ";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(185, 41);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(51, 20);
			this->numericUpDown1->TabIndex = 10;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label10->Location = System::Drawing::Point(3, 448);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(86, 15);
			this->label10->TabIndex = 16;
			this->label10->Text = L"Ölçüm sonucu : ";
			// 
			// button2
			// 
			this->button2->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button2->ImageKey = L"calculateGeo.png";
			this->button2->ImageList = this->ımageList1;
			this->button2->Location = System::Drawing::Point(3, 466);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(110, 36);
			this->button2->TabIndex = 15;
			this->button2->Text = L"HESAPLA";
			this->button2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &AnaEkran::button2_Click_1);
			// 
			// button4
			// 
			this->button4->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button4->ImageKey = L"reset1.png";
			this->button4->ImageList = this->ımageList1;
			this->button4->Location = System::Drawing::Point(128, 466);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(108, 36);
			this->button4->TabIndex = 17;
			this->button4->Text = L"TEMİZLE";
			this->button4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &AnaEkran::button4_Click);
			// 
			// radioButton6
			// 
			this->radioButton6->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->radioButton6->ImageKey = L"curve.png";
			this->radioButton6->ImageList = this->ımageList1;
			this->radioButton6->Location = System::Drawing::Point(3, 362);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(168, 38);
			this->radioButton6->TabIndex = 1;
			this->radioButton6->Text = L"Eğrinin uzunluğunu bul";
			this->radioButton6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->radioButton5->ImageKey = L"distance.png";
			this->radioButton5->ImageList = this->ımageList1;
			this->radioButton5->Location = System::Drawing::Point(3, 325);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(156, 31);
			this->radioButton5->TabIndex = 0;
			this->radioButton5->Text = L"        İki nokta arasındaki mesafeyi bul";
			this->radioButton5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton7
			// 
			this->radioButton7->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->radioButton7->ImageKey = L"area.png";
			this->radioButton7->ImageList = this->ımageList1;
			this->radioButton7->Location = System::Drawing::Point(3, 406);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(211, 41);
			this->radioButton7->TabIndex = 2;
			this->radioButton7->Text = L"Çevrelenmiş nesnenin alanını bul";
			this->radioButton7->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(3, 202);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(70, 45);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::White;
			this->label13->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label13->Cursor = System::Windows::Forms::Cursors::Help;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::DimGray;
			this->label13->ImageKey = L"(none)";
			this->label13->Location = System::Drawing::Point(6, 61);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(230, 112);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Lütfen kalibrasyon nokta sayısı eşik değeri ve kalibrasyon tahtası boyutunu belir"
				L"ledikten sonra çevrimiçi veya çevrimdışı bir işlem seçiniz";
			// 
			// richTextBox4
			// 
			this->richTextBox4->Location = System::Drawing::Point(97, 274);
			this->richTextBox4->Name = L"richTextBox4";
			this->richTextBox4->Size = System::Drawing::Size(139, 45);
			this->richTextBox4->TabIndex = 21;
			this->richTextBox4->Text = L"";
			// 
			// richTextBox3
			// 
			this->richTextBox3->Location = System::Drawing::Point(3, 274);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->Size = System::Drawing::Size(88, 45);
			this->richTextBox3->TabIndex = 20;
			this->richTextBox3->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(0, 258);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Görüntü noktaları";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(97, 258);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(117, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Gerçek dünya noktaları";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(0, 186);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(73, 13);
			this->label9->TabIndex = 26;
			this->label9->Text = L"M/K Noktaları";
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->numericUpDown2);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label13);
			this->panel1->Controls->Add(this->label12);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->richTextBox1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->richTextBox3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->richTextBox4);
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->radioButton5);
			this->panel1->Controls->Add(this->radioButton1);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->radioButton6);
			this->panel1->Controls->Add(this->radioButton7);
			this->panel1->Location = System::Drawing::Point(12, 27);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(240, 505);
			this->panel1->TabIndex = 27;
			// 
			// button1
			// 
			this->button1->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button1->ImageKey = L"calibrate1.png";
			this->button1->ImageList = this->ımageList1;
			this->button1->Location = System::Drawing::Point(79, 219);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 36);
			this->button1->TabIndex = 29;
			this->button1->Tag = L"";
			this->button1->Text = L"KALİBRE ET";
			this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AnaEkran::button1_Click);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(185, 22);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(51, 20);
			this->numericUpDown2->TabIndex = 28;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label4->Location = System::Drawing::Point(5, 24);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(184, 15);
			this->label4->TabIndex = 27;
			this->label4->Text = L"Kalibrasyon nokta sayısı eşik değeri : ";
			// 
			// AnaEkran
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
			this->AutoSize = true;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(618, 537);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"AnaEkran";
			this->Text = L"2D MONO KALİBRASYON";
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	Pen^ pen = gcnew Pen(Color::Blue, 2);

		if (radioButton1->Checked) {
			label13->Text = "Şimdi görüntü üzerinde kalibrasyon noktalarını seçebilirsiniz.";
			calibCount++;
			label1->Text = "Kalibrasyon noktalarinin sayisi : " + calibCount;
			vecManual.push_back(e->X);
			vecManual.push_back(e->Y);
			richTextBox1->AppendText(e->X.ToString() + "-" + e->Y.ToString() + "\n");
			richTextBox1->ScrollToCaret();
		}

		if (radioButton5->Checked) { // distance b/w 2 coord			
			//richTextBox1->AppendText(e->X.ToString() + "\t" + e->Y.ToString() + "\n");
			vecTiklanan.push_back(e->X);
			vecTiklanan.push_back(e->Y);
			richTextBox3->AppendText(e->X.ToString() + "-" + e->Y.ToString() + "\n");
			richTextBox3->ScrollToCaret();
			float* test1 = new float[2]; // seçilmiş x ve y noktalarını atayacağımız geçici dizi oluşturuluyor(sadece x ve y olduğu için boyutu 2).
			test1[0] = e->X;
			test1[1] = e->Y;
			float* gercekDunya = new float[3]; //ImarEt fonksiyonundan geri dönecek olan gerçek dünya dizisi oluşturuluyor.
			ImarEt(1, test1, projeksiyon, gercekDunya); // projeksiyon matrisi sonucunda hesaplanan gercekDunya değişkeni dolduruluyor
			richTextBox4->AppendText(gercekDunya[0] + " - " + gercekDunya[1] + "\n");
			richTextBox4->ScrollToCaret();
			vecXY.push_back(gercekDunya[0]);
			vecXY.push_back(gercekDunya[1]);

			delete[] test1;
			delete[] gercekDunya;

			switch (e->Button)
			{
			case System::Windows::Forms::MouseButtons::Right:
				pictureBox1->CreateGraphics()->DrawLine(pen, vecTiklanan[0], vecTiklanan[1], vecTiklanan[2], vecTiklanan[3]);
				vecTiklanan.clear();
				break;
			}

		}
		else if (radioButton6->Checked) {
		
			//richTextBox1->AppendText(e->X.ToString() + "\t" + e->Y.ToString() + "\n");
			richTextBox3->AppendText(e->X.ToString() + "-" + e->Y.ToString() + "\n");
			richTextBox3->ScrollToCaret();
			vecTiklanan.push_back(e->X);
			vecTiklanan.push_back(e->Y);
			float* test1 = new float[2]; // seçilmiş x ve y noktalarını atayacağımız geçici dizi oluşturuluyor(sadece x ve y olduğu için boyutu 2).
			test1[0] = e->X;
			test1[1] = e->Y;
			float* gercekDunya = new float[3]; //ImarEt fonksiyonundan geri dönecek olan gerçek dünya dizisi oluşturuluyor.
			ImarEt(1, test1, projeksiyon, gercekDunya); // projeksiyon matrisi sonucunda hesaplanan gercekDunya değişkeni dolduruluyor
			
			richTextBox4->AppendText(gercekDunya[0] + " - " + gercekDunya[1] + "\n");
			richTextBox4->ScrollToCaret();
			vecXY.push_back(gercekDunya[0]);
			vecXY.push_back(gercekDunya[1]);

			delete[] test1;
			delete[] gercekDunya;

			switch (e->Button)
			{
			case System::Windows::Forms::MouseButtons::Right:
				for (int i = 0; i < (vecTiklanan.size() / 2) - 1; i++) {
					pictureBox1->CreateGraphics()->DrawLine(pen, vecTiklanan[2 * i], vecTiklanan[2 * i + 1], vecTiklanan[2 * i + 2], vecTiklanan[2 * i + 3]);
				}
				vecTiklanan.clear();
				break;
			}


		}
		else if (radioButton7->Checked) {
			
			richTextBox3->AppendText(e->X.ToString() + "-" + e->Y.ToString() + "\n");
			richTextBox3->ScrollToCaret();
			vecTiklanan.push_back(e->X);
			vecTiklanan.push_back(e->Y);
			float* test1 = new float[2]; // seçilmiş x ve y noktalarını atayacağımız geçici dizi oluşturuluyor(sadece x ve y olduğu için boyutu 2).
			test1[0] = e->X;
			test1[1] = e->Y;
			float* gercekDunya = new float[3]; //ImarEt fonksiyonundan geri dönecek olan gerçek dünya dizisi oluşturuluyor.
			ImarEt(1, test1, projeksiyon, gercekDunya); // projeksiyon matrisi sonucunda hesaplanan gercekDunya değişkeni dolduruluyor

			richTextBox4->AppendText(gercekDunya[0] + " - " + gercekDunya[1] + "\n");
			richTextBox4->ScrollToCaret();
			vecXY.push_back(gercekDunya[0]);
			vecXY.push_back(gercekDunya[1]);

			delete[] test1;
			delete[] gercekDunya;

			switch (e->Button)
			{
			case System::Windows::Forms::MouseButtons::Right:
				for (int i = 0; i < (vecTiklanan.size() / 2) - 1; i++) {
					pictureBox1->CreateGraphics()->DrawLine(pen, vecTiklanan[2 * i], vecTiklanan[2 * i + 1], vecTiklanan[2 * i + 2], vecTiklanan[2 * i + 3]);
				}
				int vecSize = vecTiklanan.size();
				pictureBox1->CreateGraphics()->DrawLine(pen, vecTiklanan[0], vecTiklanan[1], vecTiklanan[vecTiklanan.size() - 2], vecTiklanan[vecTiklanan.size() - 1]);
				vecTiklanan.clear();
				break;
			}
		}

	}
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
	if (radioButton5->Checked) {
		mesafe = sqrt(pow((vecXY[0] - vecXY[2]), 2) + pow((vecXY[1] - vecXY[3]), 2));
		label10->Text = "Ölçüm sonucu : " + mesafe.ToString() + " mm";
		vecXY.clear();
	}
	else if(radioButton6 ->Checked)
	{
		mesafe = 0;

		for (int i = 0; i < (vecXY.size()/2) - 1; i++) {
			mesafe += sqrt(pow(vecXY[2 * i + 2] - vecXY[2 * i], 2) + pow(vecXY[2 * i + 3] - vecXY[2 * i + 1], 2));
		}

		label10->Text = "Ölçüm sonucu : " + mesafe.ToString() + " mm";
		vecXY.clear();
	}
	else if (radioButton7->Checked)
	{
		//for (int i = 0; i < (vecXY.size() / 2) - 1; i++) {
		//	mesafe += sqrt(pow(vecXY[2 * i + 2] - vecXY[2 * i], 2) + pow(vecXY[2 * i + 3] - vecXY[2 * i + 1], 2));
		//}
		//mesafe += sqrt(pow(vecXY[vecXY.size()-2] - vecXY[0], 2) + pow(vecXY[vecXY.size() - 1] - vecXY[1], 2));

		//mesafe /= (vecXY.size() / 2);
		//int kenarSayisi = (vecXY.size() / 2);
		//alan = 0.25 * kenarSayisi * pow(mesafe,2) * abs(1/tan(180/kenarSayisi));
		alan = alanBul();
		label10->Text = "Ölçüm sonucu : " + alan.ToString() + " mm^2";
		vecXY.clear();
	}
}

private: System::Void openCameraToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	label13->Text = "KALİBRASYON TAHTASINI kameraya gosterin. Eger kalibrasyon nokta sayisindan memnun iseniz bosluk tusuna basin(Ayrica belirlediginiz esik degerini gectiginiz an otomatik sonlancaktir).";
	tahtaBoyutu = (int)numericUpDown1->Value;
	kalibrasyonEsik = (int)numericUpDown2->Value;
	calibCount = goruntuYukle(tahtaBoyutu, maksimumDeger, 0,kalibrasyonEsik); // 0 kamera secimini gosteriyor
	pictureBox1->Image = Image::FromFile("sonuc.bmp");
	pictureBox1->Size = System::Drawing::Size(640, 480);
	label1->Text = "Kalibrasyon noktalarinin sayisi : " + calibCount;
	label13->Text = "Manuel Kalibrasyon secenegi secili iken daha fazla kalibrasyon noktasi secebilirsiniz (Secmek istemiyoraniz direkt KALİBRE ET butonuna tiklayiniz).";


}
private: System::Void uploadImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		pictureBox1->ImageLocation = openFileDialog1->FileName;
		CString str;
		str = openFileDialog1->FileName;
		giris = (LPCTSTR)str;
		buffer = LoadBMP(width, height, size1, giris);
		CString cikti = Application::StartupPath + "/goruntu.bmp";
		LPCTSTR output = (LPCTSTR)cikti;
		SaveBMP(buffer, width, height, size1, output);
		label13->Text = "Cevrimdisi secenegi altindaki Kalibre noktlarini bul secenegine tiklayin (Öncesinde ve sonrasinda manuel olarak kalibrasyon noktasi secebilirsiniz)";
		maksimumDeger[0] = (int)numericUpDown1->Value;
		pictureBox1->Size = System::Drawing::Size(width, height);
		this->Size = System::Drawing::Size(pictureBox1->Width + panel1->Width+30, 555);
	
	}
}

private: System::Void autoCalibrateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	tahtaBoyutu = (int)numericUpDown1->Value;
	kalibrasyonEsik = (int)numericUpDown2->Value;
	calibCount = goruntuYukle(tahtaBoyutu, maksimumDeger, 1,kalibrasyonEsik);
	pictureBox1->Image = Image::FromFile("sonuc.bmp");
	label1->Text = "Kalibrasyon noktalarinin sayisi : " + calibCount;
	label13->Text = "Manuel Kalibrasyon secenegi secili iken daha fazla kalibrasyon noktasi secebilirsiniz (Secmek istemiyoraniz direkt KALIBRE ET butonuna tiklayiniz).";
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	vecXY.clear();
	richTextBox1->Clear();
	label10->Text = "Ölçüm sonucu : ";
	richTextBox3->Clear();
	richTextBox4->Clear();
	radioButton1->Checked = false;
	radioButton5->Checked = false;
	radioButton6->Checked = false;
	radioButton7->Checked = false;
}


private: System::Void calibrateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (radioButton1->Checked) {
		Pen^ pen = gcnew Pen(Color::Red, 2);
		pictureBox1->CreateGraphics()->DrawEllipse(pen, e->X- 5, e->Y-5, 10, 10);
	}
	else if (radioButton5->Checked || radioButton6->Checked || radioButton7->Checked)
	{
		Pen^ pen = gcnew Pen(Color::Blue, 2);
		pictureBox1->CreateGraphics()->DrawLine(pen, e->X - 4, e->Y - 4, e->X + 4, e->Y + 4);
		pictureBox1->CreateGraphics()->DrawLine(pen, e->X - 4, e->Y + 4, e->X + 4, e->Y - 4);
	}
	
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (radioButton1->Checked) {
		tahtaBoyutu = (int)numericUpDown1->Value;
		for (int i = 0; i < vecManual.size() / 2; i++) {
			vektorImge.push_back(vecManual[i * 2]);
			vektorImge.push_back(vecManual[i * 2 + 1]);
			calibX = vecManual[i * 2] / (maksimumDeger[0] + 0.001) * tahtaBoyutu;
			calibY = vecManual[i * 2 + 1] / (maksimumDeger[0] + 0.001) * tahtaBoyutu;
			vektorDunya.push_back(calibX);
			vektorDunya.push_back(calibY);
			vektorDunya.push_back(calibZ);

		}

	}


	imge = new float[calibCount * 2]; //imge dizisinin boyutu seçilen nokta sayısına göre belirleniyor.(x ve y olduğu için 2'ye çarpılıyor)
	dunya = new float[calibCount * 3];//imge dizisinin boyutu seçilen nokta sayısına göre belirleniyor.(x,y ve z olduğu için 3'e çarpılıyor)

	vektordenDegerleriOku(calibCount, imge, dunya);
	ProjeksiyonMatrisiHesapla(calibCount, dunya, imge, projeksiyon);

	label13->Text = "Kalibrasyon islemi tamamlandi. Simdi olcum islemlerini gerceklestirebilirsiniz.\nGoruntu uzerinden noktalari secerken son noktaya farenin sag tusuyla tiklamayi unutmayin";
	radioButton1->Checked = false;
	richTextBox1->Clear();
	vecManual.clear();

}
};
}
