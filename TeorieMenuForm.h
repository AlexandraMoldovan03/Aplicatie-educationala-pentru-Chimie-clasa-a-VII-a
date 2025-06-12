#pragma once
#include "ReactionSolver.h"
#include "JocTeorieForm.h"
#include "ConcentratieMenuForm.h"
#include "JocStructuraAtomForm.h"


namespace LicentaChimie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//
	/// Clasa TeorieMenuForm pentru afișarea meniului de teorie
	//
	public ref class TeorieMenuForm : public System::Windows::Forms::Form
	{
	private:
		String^ username; // Stocăm username-ul utilizatorului

	public:
		// Constructor cu parametru (pentru a primi username-ul)
		TeorieMenuForm(String^ user)
		{
			InitializeComponent();
			this->username = user;
		}

		// Constructor implicit
		TeorieMenuForm(void)
		{
			InitializeComponent();
		}

	private:
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Label^ titlu1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
		   System::Windows::Forms::Button^ button4;
		   PictureBox^ pictureBox2;


		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {

			  
			   this->BackColor = Color::FromArgb(255, 255, 250, 205); // Lemon Chiffon

			   /*this->BackgroundImage = Image::FromFile("fundal_teorie.png");
			   this->BackgroundImageLayout = ImageLayout::Stretch;*/


			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->titlu1 = (gcnew System::Windows::Forms::Label());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // button1
			   // 
			   this->button1->Font = (gcnew System::Drawing::Font(L"Georgia", 14, System::Drawing::FontStyle::Bold));
			   this->button1->Location = System::Drawing::Point(703, 141);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(300, 100);
			   this->button1->TabIndex = 1;
			   this->button1->Text = L"Echilibrare ecuații";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &TeorieMenuForm::button1_Click);
			   // 
			   // titlu1
			   // 
			   this->titlu1->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			   this->titlu1->ForeColor = Color::Black;
			  // this->titlu1->BackColor = Color::FromArgb(150, 70, 130, 180); // fundal semitransparent peste titlu

			   this->titlu1->AutoSize = true;
			   //this->titlu1->Font = gcnew Drawing::Font("Segoe UI", 26, FontStyle::Bold | FontStyle::Italic);
			   //this->titlu1->ForeColor = Color::DarkMagenta;
			   this->titlu1->Location = System::Drawing::Point(288, 9);
			   this->titlu1->Name = L"titlu1";
			   this->titlu1->Size = System::Drawing::Size(1023, 72);
			   this->titlu1->TabIndex = 0;
			   this->titlu1->Text = L"Haide să înțelegem împreună!";
			   this->titlu1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;



			   // 
			   // button2
			   // 
			   this->button2->Font = (gcnew System::Drawing::Font(L"Georgia", 14, System::Drawing::FontStyle::Bold));
			   this->button2->Location = System::Drawing::Point(703, 311);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(300, 100);
			   this->button2->TabIndex = 2;
			   this->button2->Text = L"Invățăm prin joc!";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &TeorieMenuForm::button2_Click);
			   // 
			   // button3
			   // 
			   this->button3->Font = (gcnew System::Drawing::Font(L"Georgia", 14, System::Drawing::FontStyle::Bold));
			   this->button3->Location = System::Drawing::Point(703, 496);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(300, 100);
			   this->button3->TabIndex = 3;
			   this->button3->Text = L"Concentrații";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &TeorieMenuForm::button3_Click);
			    
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->button4->Font = (gcnew System::Drawing::Font(L"Georgia", 14, System::Drawing::FontStyle::Bold));
			   this->button4->Location = System::Drawing::Point(703, 661);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(300, 100);
			   this->button4->TabIndex = 4;
			   this->button4->Text = L"Joc Structura Atomului";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &TeorieMenuForm::button4_Click);
			   this->Controls->Add(this->button4);

			   // 
			   // TeorieMenuForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(36, 61);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoScroll = true;
			   this->AutoSize = true;
			   this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   //this->BackgroundImage = Image::FromFile("fundal_teorie.png"); 
			   //this->BackgroundImageLayout = ImageLayout::Stretch;
			   this->ClientSize = System::Drawing::Size(2499, 762);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->titlu1);
			   this->Controls->Add(this->button1);
			   this->Font = (gcnew System::Drawing::Font(L"Georgia", 19.875F, System::Drawing::FontStyle::Bold));
			   this->Name = L"TeorieMenuForm";
			   this->Text = L"TeorieMenuForm";
			   this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			   this->Load += gcnew System::EventHandler(this, &TeorieMenuForm::TeorieMenuForm_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();


			   pictureBox2 = gcnew PictureBox();
			   pictureBox2->Image = Image::FromFile("moli.png");
			   pictureBox2->Size = Drawing::Size(200, 200);
			   pictureBox2->Location = Point(80, 120);
			   pictureBox2->SizeMode = PictureBoxSizeMode::Zoom;
			   this->Controls->Add(pictureBox2);
			  

		   }
#pragma endregion

	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			ReactionSolver^ reactionSolver = gcnew ReactionSolver();
			reactionSolver->ShowDialog();
		}

		System::Void TeorieMenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
			// Centrare titlu
			this->titlu1->Location = System::Drawing::Point(
				(this->ClientSize.Width - this->titlu1->Width) / 2,
				this->ClientSize.Height / 12
			);

			// Vector cu butoane
			array<Button^>^ butoane = { button2, button3, button4, button1 };

			int buttonWidth = 320;
			int buttonHeight = 80;
			int spacing = 25;
			int startY = (this->titlu1->Bottom + 50);

			for (int i = 0; i < butoane->Length; i++) {
				butoane[i]->Size = System::Drawing::Size(buttonWidth, buttonHeight);

				// Fundal albastru pastel + stil
				butoane[i]->BackColor = Color::FromArgb(220, 235, 245);  // albastru pastel deschis
				butoane[i]->ForeColor = Color::MidnightBlue;

				butoane[i]->FlatStyle = FlatStyle::Flat;
				butoane[i]->FlatAppearance->BorderSize = 2;
				butoane[i]->FlatAppearance->BorderColor = Color::SteelBlue;

				butoane[i]->Font = gcnew Drawing::Font("Segoe UI Semibold", 12, FontStyle::Regular);

				butoane[i]->Location = System::Drawing::Point(
					(this->ClientSize.Width - buttonWidth) / 2,
					startY + i * (buttonHeight + spacing)
				);

				this->Controls->Add(butoane[i]);

				butoane[i]->MouseEnter += gcnew EventHandler(this, &TeorieMenuForm::OnHover);
				butoane[i]->MouseLeave += gcnew EventHandler(this, &TeorieMenuForm::OnLeave);
			}
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			LicentaChimie::JocTeorieForm^ jocTeorieForm = gcnew LicentaChimie::JocTeorieForm();
			this->Hide();
			jocTeorieForm->ShowDialog();
			this->Show();
		}
		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			ConcentratieMenuForm^ concForm = gcnew ConcentratieMenuForm();
			this->Hide();
			concForm->ShowDialog();
			this->Show();
		}


		System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
			JocStructuraAtomForm^ atomForm = gcnew JocStructuraAtomForm();
			this->Hide();
			atomForm->ShowDialog();
			this->Show();
		}

		System::Void OnHover(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = dynamic_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(245, 255, 255); // alb-albastru deschis
			btn->ForeColor = Color::DarkSlateBlue;
		}

		System::Void OnLeave(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = dynamic_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(220, 235, 245); // revin la pastel
			btn->ForeColor = Color::MidnightBlue;
		}



	};
}
