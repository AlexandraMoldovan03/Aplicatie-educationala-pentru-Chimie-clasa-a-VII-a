#pragma once
#include "Test1Form.h"
#include "Test2Form.h"
#include "CatalogForm.h"
#pragma execution_character_set("utf-8")

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::ComponentModel;

	public ref class TestMenu : public Form
	{
	private:
		String^ username;
		Label^ labelTitlu;
		array<Button^>^ butoane;

	public:
		TestMenu(String^ user) {
			username = user;
			InitializeComponent();
		}

	protected:
		~TestMenu() {
			if (components) {
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void) {
			this->Text = L"TestMenu";
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(219, 240, 250); // bleu pastel
			this->Font = gcnew Drawing::Font("Comic Sans MS", 12, FontStyle::Bold);

			// Etichetă titlu
			labelTitlu = gcnew Label();
			labelTitlu->Text = L"🧪 Teste pentru Fixarea Cunoștințelor";
			labelTitlu->Font = gcnew Drawing::Font("Segoe UI", 28, FontStyle::Bold);
			labelTitlu->ForeColor = Color::MediumSlateBlue;
			labelTitlu->AutoSize = true;
			this->Controls->Add(labelTitlu);

			// Inițializare butoane
			butoane = gcnew array<Button^>(3);

			butoane[0] = CreeazaButon("📘 Test 1", gcnew EventHandler(this, &TestMenu::button1_Click));
			butoane[1] = CreeazaButon("📗 Test 2", gcnew EventHandler(this, &TestMenu::button2_Click));
			butoane[2] = CreeazaButon("📊 Catalog Note", gcnew EventHandler(this, &TestMenu::button3_Click));

			for each(Button ^ b in butoane) {
				this->Controls->Add(b);
			}

			this->Load += gcnew EventHandler(this, &TestMenu::TestMenu_Load);
		}

		Button^ CreeazaButon(String^ text, EventHandler^ handler) {
			Button^ btn = gcnew Button();
			btn->Text = text;
			btn->Size = Drawing::Size(300, 80);
			btn->BackColor = Color::FromArgb(255, 255, 224); // galben pal
			btn->ForeColor = Color::DarkSlateBlue;
			btn->Font = gcnew Drawing::Font("Comic Sans MS", 16, FontStyle::Bold);
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 2;
			btn->FlatAppearance->BorderColor = Color::SlateBlue;
			btn->Click += handler;
			btn->MouseEnter += gcnew EventHandler(this, &TestMenu::OnHover);
			btn->MouseLeave += gcnew EventHandler(this, &TestMenu::OnLeave);
			return btn;
		}

	private:
		System::Void TestMenu_Load(System::Object^ sender, System::EventArgs^ e) {
			// Centrare titlu
			labelTitlu->Location = Point(
				(this->ClientSize.Width - labelTitlu->Width) / 2,
				this->ClientSize.Height / 8
			);

			// Poziționare butoane
			int startY = labelTitlu->Bottom + 60;
			int spacing = 40;

			for (int i = 0; i < butoane->Length; i++) {
				butoane[i]->Location = Point(
					(this->ClientSize.Width - butoane[i]->Width) / 2,
					startY + i * (butoane[i]->Height + spacing)
				);
			}
		}

		System::Void OnHover(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::LightSkyBlue;
		}

		System::Void OnLeave(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(255, 255, 224);
		}

		// Click handlers
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			Test1Form^ test1 = gcnew Test1Form(username);
			this->Hide(); test1->ShowDialog(); this->Show();
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			Test2Form^ test2 = gcnew Test2Form(username);
			this->Hide(); test2->ShowDialog(); this->Show();
		}

		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			CatalogForm^ catalog = gcnew CatalogForm(username);
			this->Hide(); catalog->ShowDialog(); this->Show();
		}
	};
}
