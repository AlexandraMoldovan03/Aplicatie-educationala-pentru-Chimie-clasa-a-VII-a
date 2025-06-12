#pragma once
#pragma execution_character_set("utf-8")
#include "Level1CeEsteChimia.h"
#include "Level2Joc.h"
#include "Level3Joc.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class JocTeorieForm : public System::Windows::Forms::Form {
	public:
		JocTeorieForm(void) {
			InitializeComponent();
		}

	protected:
		~JocTeorieForm() {
			if (components) delete components;
		}

	private:
		Label^ label1;
		Label^ label2;
		Button^ button1;
		Button^ button2;
		Button^ button3;
		PictureBox^ pictureBox1;
		PictureBox^ pictureBox2;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->Text = L"Jocuri de Chimie";
			this->ClientSize = System::Drawing::Size(1280, 800);
			this->BackColor = Color::FromArgb(230, 240, 255);

			// === Titlu ===
			label1 = gcnew Label();
			label1->Text = L"Să învățăm prin joacă!";
			label1->Font = gcnew Drawing::Font("Segoe UI", 26, FontStyle::Bold);
			label1->ForeColor = Color::MediumVioletRed;
			label1->AutoSize = true;
			this->Controls->Add(label1);

			// === Descriere ===
			label2 = gcnew Label();
			label2->Text = L"Explorează chimia prin jocuri interactive! Alege un nivel pentru a începe:";
			label2->Font = gcnew Drawing::Font("Segoe UI", 13, FontStyle::Regular);
			label2->ForeColor = Color::DarkSlateBlue;
			label2->AutoSize = true;
			this->Controls->Add(label2);

			// === Mascotă ===
			pictureBox2 = gcnew PictureBox();
			pictureBox2->Image = Image::FromFile("moli.png");
			pictureBox2->Size = Drawing::Size(200, 200);
			pictureBox2->Location = Point(80, 120);
			pictureBox2->SizeMode = PictureBoxSizeMode::Zoom;
			this->Controls->Add(pictureBox2);

			// === Butoane ===
			array<Button^>^ butoane = gcnew array<Button^>(3);
			array<String^>^ texte = {
				L"Level 1: Ustensile și Recunoaștere",
				L"Level 2: Memory - Stări de agregare",
				L"Level 3: Separarea amestecurilor"
			};
			array<EventHandler^>^ clickEvents = {
				gcnew EventHandler(this, &JocTeorieForm::button1_Click),
				gcnew EventHandler(this, &JocTeorieForm::button2_Click),
				gcnew EventHandler(this, &JocTeorieForm::button3_Click)
			};

			int buttonWidth = 400;
			int buttonHeight = 45;
			int startY = 230;
			int spacing = 70;

			for (int i = 0; i < 3; i++) {
				butoane[i] = gcnew Button();
				butoane[i]->Text = texte[i];
				butoane[i]->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
				butoane[i]->Size = Drawing::Size(buttonWidth, buttonHeight);
				butoane[i]->Location = Point((ClientSize.Width - buttonWidth) / 2, startY + i * spacing);
				butoane[i]->BackColor = Color::MistyRose;
				butoane[i]->FlatStyle = FlatStyle::Flat;
				butoane[i]->FlatAppearance->BorderSize = 2;
				butoane[i]->FlatAppearance->BorderColor = Color::Orchid;
				butoane[i]->ForeColor = Color::DarkSlateBlue;
				butoane[i]->MouseEnter += gcnew EventHandler(this, &JocTeorieForm::OnHover);
				butoane[i]->MouseLeave += gcnew EventHandler(this, &JocTeorieForm::OnLeave);
				butoane[i]->Click += clickEvents[i];
				this->Controls->Add(butoane[i]);
			}

			//  Centrare exactă label1 și label2 
			using namespace Drawing;
			Graphics^ g = this->CreateGraphics();
			SizeF sizeTitle = g->MeasureString(label1->Text, label1->Font);
			SizeF sizeDesc = g->MeasureString(label2->Text, label2->Font);
			label1->Location = Point((ClientSize.Width - (int)sizeTitle.Width) / 2, 40);
			label2->Location = Point((ClientSize.Width - (int)sizeDesc.Width) / 2, 110);
		}
#pragma endregion

	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			ChimiaGame::Level1CeEsteChimia^ level1Form = gcnew ChimiaGame::Level1CeEsteChimia();
			this->Hide(); level1Form->ShowDialog(); this->Show();
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			LicentaChimie::Level2Joc^ level2Form = gcnew LicentaChimie::Level2Joc();
			this->Hide(); level2Form->ShowDialog(); this->Show();
		}

		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			LicentaChimie::Level3Joc^ level3Form = gcnew LicentaChimie::Level3Joc();
			this->Hide(); level3Form->ShowDialog(); this->Show();
		}

		System::Void OnHover(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = dynamic_cast<Button^>(sender);
			btn->BackColor = Color::LightCyan;
		}

		System::Void OnLeave(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = dynamic_cast<Button^>(sender);
			btn->BackColor = Color::MistyRose;
		}
	};
}
