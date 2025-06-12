#pragma once
#include "PeriodicTableForm.h"
#include "TestMenu.h"
#include "TeorieMenuForm.h"
#include "ResurseSuplimentareMenu.h"
#include "ExercitiiMenuForm.h"
#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include "DashboardForm.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		String^ username;
		DateTime startTime;

	public:
		MainForm(String^ user)
		{
			username = user;
			startTime = DateTime::Now;
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::Button^ buttonTeorie;
		System::Windows::Forms::Button^ buttonExercitii;
		System::Windows::Forms::Button^ buttonTeste;
		System::Windows::Forms::Button^ buttonTabelulPeriodic;
		System::Windows::Forms::Button^ buttonResurseSuplimentare;
		System::Windows::Forms::Panel^ panelButoane;
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Button^ buttonDashboard;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->labelTitle = gcnew System::Windows::Forms::Label();
			this->labelTitle->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold | FontStyle::Italic);
			this->labelTitle->ForeColor = Color::DarkMagenta;
			this->labelTitle->Text = L"Chimie pentru clasa a 7-a";
			this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelTitle->Dock = System::Windows::Forms::DockStyle::Top;
			this->labelTitle->Height = 80;

			this->panelButoane = gcnew System::Windows::Forms::Panel();
			this->panelButoane->Size = System::Drawing::Size(300, 400);
			this->panelButoane->Location = System::Drawing::Point(250, 100);
			this->panelButoane->BackColor = System::Drawing::Color::Transparent;

			this->buttonTeorie = gcnew System::Windows::Forms::Button();
			this->buttonExercitii = gcnew System::Windows::Forms::Button();
			this->buttonTeste = gcnew System::Windows::Forms::Button();
			this->buttonTabelulPeriodic = gcnew System::Windows::Forms::Button();
			this->buttonResurseSuplimentare = gcnew System::Windows::Forms::Button();
			this->buttonDashboard = gcnew System::Windows::Forms::Button();
			this->buttonDashboard->Click += gcnew System::EventHandler(this, &MainForm::buttonDashboard_Click);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Load);




			array<System::Windows::Forms::Button^>^ buttons = {
				buttonTeorie, buttonExercitii, buttonTeste, buttonTabelulPeriodic, buttonResurseSuplimentare, buttonDashboard
			};
			array<String^>^ texts = {
	L"📘 Teorie", L"🧠 Exerciții", L"📝 Teste", L"🔬 Tabelul Periodic", L"📚 Resurse", L"📊 Dashboard"
			};


			for (int i = 0; i < buttons->Length; i++) {
				buttons[i]->Text = texts[i];
				buttons[i]->BackColor = Color::FromArgb(255, 255, 224); // Galben pal
				buttons[i]->ForeColor = Color::DarkSlateBlue;
				buttons[i]->FlatStyle = FlatStyle::Flat;
				buttons[i]->FlatAppearance->BorderSize = 2;
				buttons[i]->FlatAppearance->BorderColor = Color::SlateBlue;
				buttons[i]->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
				buttons[i]->Size = Drawing::Size(250, 50);
				buttons[i]->Location = Drawing::Point(25, 10 + i * 60);

				// Adaugă efecte de hover
				buttons[i]->MouseEnter += gcnew EventHandler(this, &MainForm::OnHover);
				buttons[i]->MouseLeave += gcnew EventHandler(this, &MainForm::OnLeave);

				this->panelButoane->Controls->Add(buttons[i]);
			}

			this->buttonTabelulPeriodic->Click += gcnew System::EventHandler(this, &MainForm::buttonPeriodicTable_Click);
			this->buttonResurseSuplimentare->Click += gcnew System::EventHandler(this, &MainForm::buttonResurseSuplimentare_Click);
			this->buttonExercitii->Click += gcnew System::EventHandler(this, &MainForm::buttonExercitii_Click);
			this->buttonTeste->Click += gcnew System::EventHandler(this, &MainForm::buttonTeste_Click);
			this->buttonTeorie->Click += gcnew System::EventHandler(this, &MainForm::buttonTeorie_Click);

			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->panelButoane);
			this->Controls->Add(this->labelTitle);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main Form";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->BackgroundImage = Image::FromFile("fundalMainForm2.png");
			this->BackgroundImageLayout = ImageLayout::Stretch;
			this->panelButoane->BackColor = Color::FromArgb(180, Color::White); // alb cu transparenta

			
			this->ResumeLayout(false);
		}
#pragma endregion

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->panelButoane->Left = (this->ClientSize.Width - this->panelButoane->Width) / 2;
		this->panelButoane->Top = (this->ClientSize.Height - this->panelButoane->Height) / 2;
	}

	private: System::Void buttonTeorie_Click(System::Object^ sender, System::EventArgs^ e) {
		TeorieMenuForm^ teorieMenu = gcnew TeorieMenuForm(username);
		teorieMenu->ShowDialog();
	}

	private: System::Void buttonPeriodicTable_Click(System::Object^ sender, System::EventArgs^ e) {
		PeriodicTableForm^ periodicTable = gcnew PeriodicTableForm();
		periodicTable->ShowDialog();
	}

	private: System::Void buttonResurseSuplimentare_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		ResurseSuplimentareMenu^ resurseSuplimentareMenu = gcnew ResurseSuplimentareMenu(username);
		resurseSuplimentareMenu->ShowDialog();
		this->Show();
	}

	private: System::Void buttonTeste_Click(System::Object^ sender, System::EventArgs^ e) {
		TestMenu^ testMenu = gcnew TestMenu(username);
		testMenu->ShowDialog();
	}

	private: System::Void buttonExercitii_Click(System::Object^ sender, System::EventArgs^ e) {
		LicentaChimie::ExercitiiMenuForm^ exercitiiMenuForm = gcnew LicentaChimie::ExercitiiMenuForm(username);
		exercitiiMenuForm->ShowDialog();
	}

	 System::Void OnHover(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		btn->BackColor = Color::LightSkyBlue;
	}

	 System::Void OnLeave(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		btn->BackColor = Color::FromArgb(255, 255, 224); // revine la galben pal
	}


	private: System::Void MainForm_FormClosing(System::Object^ sender, FormClosingEventArgs^ e) {
		DateTime endTime = DateTime::Now;
		TimeSpan durata = endTime - startTime;
		int secunde = (int)durata.TotalSeconds;

		try {
			msclr::interop::marshal_context context;
			std::string userStr = context.marshal_as<std::string>(username);
			std::string startStr = context.marshal_as<std::string>(startTime.ToString("yyyy-MM-dd HH:mm:ss"));
			std::string endStr = context.marshal_as<std::string>(endTime.ToString("yyyy-MM-dd HH:mm:ss"));

			sql::Driver* driver = sql::mariadb::get_driver_instance();
			sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
			sql::Properties properties({ {"user", "root"}, {"password", ""} });
			std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

			std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
				"INSERT INTO sesiuni_invatare (username, start_time, end_time, durata_secunde) VALUES (?, ?, ?, ?)"));

			stmt->setString(1, userStr);
			stmt->setString(2, startStr);
			stmt->setString(3, endStr);
			stmt->setInt(4, secunde);
			stmt->execute();
		}
		catch (sql::SQLException& ex) {
			MessageBox::Show("Eroare la salvarea timpului: " + gcnew String(ex.what()));
		}
	}

	private: System::Void buttonDashboard_Click(System::Object^ sender, System::EventArgs^ e) {
		DashboardForm^ dash = gcnew DashboardForm(username);
		dash->ShowDialog();
	}

	};
}
