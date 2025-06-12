#pragma once
#include "Level1Joc2.h"

namespace ChimiaGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Level1CeEsteChimia : public System::Windows::Forms::Form
	{
	public:
		Level1CeEsteChimia(void)
		{
			InitializeComponent();
		}

	protected:
		~Level1CeEsteChimia()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		PictureBox^ pictureBerzelius;
		PictureBox^ picturePalnie;
		PictureBox^ pictureFundPlat;
		PictureBox^ pictureErlenmeyer;
		PictureBox^ pictureEprubeta;
		PictureBox^ pictureWurtz;
		PictureBox^ pictureMoli;
		Label^ labelInfo;
		Button^ btnNext;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Text = L"Laboratorul de chimie";
			this->Size = System::Drawing::Size(1000, 700);
			this->BackColor = System::Drawing::Color::FromArgb(235, 245, 255);
			this->Font = gcnew System::Drawing::Font("Segoe UI", 10);
			//this->BackgroundImage = Image::FromFile("pestera.png");
			//this->BackgroundImageLayout = ImageLayout::Stretch;

			this->WindowState = FormWindowState::Maximized;
			//this->FormBorderStyle = FormBorderStyle::None;




			pictureMoli = gcnew PictureBox();
			pictureMoli->Image = Image::FromFile("moli.png");
			pictureMoli->Location = Point(850, 500);
			pictureMoli->Size = Drawing::Size(100, 100);
			pictureMoli->SizeMode = PictureBoxSizeMode::StretchImage;
			this->Controls->Add(pictureMoli);

			labelInfo = gcnew Label();
			labelInfo->Size = Drawing::Size(800, 60);
			labelInfo->Location = Point((this->ClientSize.Width - 800) / 2, 520);
			labelInfo->ForeColor = Color::White;
			labelInfo->BackColor = Color::FromArgb(80, 0, 0, 0);
			labelInfo->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			labelInfo->TextAlign = ContentAlignment::MiddleCenter;
			labelInfo->Text = L"Apasă pe o ustensilă pentru explicație.";
			this->Controls->Add(labelInfo);

			int x = 50;
			array<System::Windows::Forms::PictureBox^>^ ustensile = gcnew array<PictureBox^>(6);
			array<String^>^ imagini = { "paharBerzelius.png", "palnieDeFiltrare.jpeg", "paharCuFundPlat.png", "paharErlenmeyer.jpeg", "eprubeta.png", "balonWurtz.png" };
			array<EventHandler^>^ handlers = {
				gcnew EventHandler(this, &Level1CeEsteChimia::OnBerzeliusClick),
				gcnew EventHandler(this, &Level1CeEsteChimia::OnPalnieClick),
				gcnew EventHandler(this, &Level1CeEsteChimia::OnFundPlatClick),
				gcnew EventHandler(this, &Level1CeEsteChimia::OnErlenmeyerClick),
				gcnew EventHandler(this, &Level1CeEsteChimia::OnEprubetaClick),
				gcnew EventHandler(this, &Level1CeEsteChimia::OnWurtzClick)
			};

			for (int i = 0; i < ustensile->Length; i++) {
				ustensile[i] = gcnew PictureBox();
				ustensile[i]->Image = Image::FromFile(imagini[i]);
				ustensile[i]->Location = Point(x, 50);
				ustensile[i]->Size = Drawing::Size(100, 100);
				ustensile[i]->SizeMode = PictureBoxSizeMode::StretchImage;
				ustensile[i]->Cursor = Cursors::Hand;
				ustensile[i]->Click += handlers[i];
				this->Controls->Add(ustensile[i]);
				x += 150;
			}

			btnNext = gcnew Button();
			btnNext->Text = L"Continuă →";
			btnNext->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			btnNext->Size = Drawing::Size(160, 50);
			btnNext->Location = Point(this->ClientSize.Width - 190, this->ClientSize.Height - 80); // colț dreapta jos
			btnNext->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;
			btnNext->BackColor = Color::FromArgb(200, 220, 240); // pastel albastru
			btnNext->ForeColor = Color::MidnightBlue;
			btnNext->FlatStyle = FlatStyle::Flat;
			btnNext->FlatAppearance->BorderSize = 0;
			btnNext->Cursor = Cursors::Hand;
			btnNext->Click += gcnew EventHandler(this, &Level1CeEsteChimia::OnNextClick);
			this->Controls->Add(btnNext);

		}
#pragma endregion

	private:
		System::Void OnBerzeliusClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Paharul Berzelius este folosit pentru amestecarea și încălzirea substanțelor.";
		}
		System::Void OnPalnieClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Pâlnia de filtrare este utilizată pentru separarea amestecurilor.";
		}
		System::Void OnFundPlatClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Balonul cu fund plat este folosit pentru reacții care necesită încălzire uniformă.";
		}
		System::Void OnErlenmeyerClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Paharul Erlenmeyer este folosit pentru reacții și încălzire în laborator.";
		}
		System::Void OnEprubetaClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Eprubeta este un vas de reacție mic pentru experimente simple.";
		}
		System::Void OnWurtzClick(System::Object^ sender, System::EventArgs^ e) {
			labelInfo->Text = L"Balonul Wurtz este folosit pentru reacții ce implică distilare.";
		}
		System::Void OnNextClick(System::Object^ sender, System::EventArgs^ e) {
			ChimiaGame::Level1Joc2^ joc2Form = gcnew ChimiaGame::Level1Joc2();
			this->Hide();
			joc2Form->ShowDialog();
			this->Show();
		}
	};
}
