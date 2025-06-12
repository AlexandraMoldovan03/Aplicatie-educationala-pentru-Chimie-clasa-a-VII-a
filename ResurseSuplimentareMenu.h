#pragma once
#include "PDFReaderForm.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ResurseSuplimentareMenu : public Form
	{
	private:
		String^ username;
		Label^ label1;
		Button^ button1;
		System::ComponentModel::Container^ components;

	public:
		ResurseSuplimentareMenu(String^ user) {
			username = user;
			InitializeComponent();
		}

		ResurseSuplimentareMenu() {
			InitializeComponent();
		}

	protected:
		~ResurseSuplimentareMenu() {
			if (components) delete components;
		}

	private:
		void InitializeComponent(void) {
			this->SuspendLayout();

			// === Setări fereastră ===
			this->AutoScaleDimensions = System::Drawing::SizeF(36, 61);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->BackColor = System::Drawing::Color::FromArgb(219, 231, 243);
			this->ClientSize = System::Drawing::Size(1600, 900);
			this->Text = L"Meniu Resurse Suplimentare";
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular);
			this->Load += gcnew System::EventHandler(this, &ResurseSuplimentareMenu::ResurseSuplimentareMenu_Load);

			// === Etichetă titlu ===
			label1 = gcnew Label();
			label1->Text = L"Toată teoria de care ai nevoie!";
			label1->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			label1->ForeColor = Color::MidnightBlue;
			label1->AutoSize = true;
			label1->TextAlign = ContentAlignment::MiddleCenter;

			// === Buton ===
			button1 = gcnew Button();
			button1->Text = L"Manual Chimie – Clasa a 7-a";
			button1->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
			button1->Size = Drawing::Size(350, 80);
			button1->BackColor = Color::LavenderBlush;
			button1->FlatStyle = FlatStyle::Flat;
			button1->FlatAppearance->BorderSize = 2;
			button1->FlatAppearance->BorderColor = Color::MediumVioletRed;
			button1->ForeColor = Color::DarkSlateBlue;
			button1->Click += gcnew EventHandler(this, &ResurseSuplimentareMenu::button1_Click);

			// Adăugare controale
			this->Controls->Add(label1);
			this->Controls->Add(button1);

			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private:
		System::Void ResurseSuplimentareMenu_Load(System::Object^ sender, System::EventArgs^ e) {
			// Centrează eticheta în partea de sus
			label1->Location = Point(
				(ClientSize.Width - label1->Width) / 2,
				ClientSize.Height / 6
			);

			// Centrează butonul
			button1->Location = Point(
				(ClientSize.Width - button1->Width) / 2,
				(ClientSize.Height - button1->Height) / 2
			);
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			PDFReaderForm^ pdfReaderForm = gcnew PDFReaderForm();
			pdfReaderForm->ShowDialog();
		}
	};
}
