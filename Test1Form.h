//#pragma once
//
//#include <mariadb/conncpp.hpp>  // Conexiune la MariaDB
//#include <msclr/marshal_cppstd.h>
//#include <ctime>
//
//namespace LicentaChimie {
//
//	using namespace System;
//	using namespace System::Windows::Forms;
//	using namespace System::Drawing;
//
//	public ref class Test1Form : public System::Windows::Forms::Form
//	{
//	private:
//		String^ username; // Numele utilizatorului
//		int yOffset = 20;
//	public:
//		// Constructor care primește username-ul utilizatorului
//		Test1Form(String^ user)
//		{
//			username = user;
//			InitializeComponent();
//		}
//
//	protected:
//		~Test1Form()
//		{
//			if (components)
//			{
//				delete components;
//			}
//		}
//
//	private:
//		System::Windows::Forms::Label^ labelTitle;
//		System::Windows::Forms::Button^ buttonSubmit;
//		array<System::Windows::Forms::Label^>^ questionLabels;
//		array<System::Windows::Forms::CheckBox^, 2>^ answerCheckBoxes;
//		array<int>^ correctAnswers;
//		System::Windows::Forms::Panel^ scrollPanel;
//
//		System::ComponentModel::Container^ components;
//
//#pragma region Windows Form Designer generated code
//		void InitializeComponent(void)
//		{
//			this->SuspendLayout();
//			this->WindowState = System::Windows::Forms::FormWindowState::Normal;
//
//
//
//			// 🔹 Panou cu scroll
//			this->scrollPanel = gcnew System::Windows::Forms::Panel();
//			this->scrollPanel->AutoScroll = true;
//			this->scrollPanel->Size = System::Drawing::Size(600, 500);
//			this->scrollPanel->Location = System::Drawing::Point(0, 60);
//
//			// 🔹 Titlu Test
//			this->labelTitle = gcnew System::Windows::Forms::Label();
//			this->labelTitle->Font = gcnew System::Drawing::Font(L"Palatino Linotype", 16, System::Drawing::FontStyle::Bold);
//			this->labelTitle->Text = L"Test de Chimie - Clasa a 7-a";
//			this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
//			this->labelTitle->Dock = System::Windows::Forms::DockStyle::Top;
//			this->labelTitle->Height = 60;
//
//			// 🔹 Inițializare întrebări și răspunsuri
//			array<String^>^ questions = {
//				L"1. Care este simbolul chimic al oxigenului?",
//				L"2. Ce stare de agregare are apa la temperatura camerei?",
//				L"3. Cum se numește schimbarea stării de la solid la lichid?",
//				L"4. Care dintre următoarele este un metal alcalin?",
//				L"5. Care este formula chimică a apei?"
//			};
//
//			array<array<String^>^>^ answers = {
//				gcnew array<String^> { L"O", L"Ox", L"Og", L"Om" },
//				gcnew array<String^> { L"Solid", L"Lichid", L"Gazos", L"Plasmă" },
//				gcnew array<String^> { L"Evaporare", L"Condensare", L"Topire", L"Sublimare" },
//				gcnew array<String^> { L"Calciu", L"Litiu", L"Fier", L"Carbon" },
//				gcnew array<String^> { L"H2O", L"O2", L"H2", L"CO2" }
//			};
//
//			this->questionLabels = gcnew array<System::Windows::Forms::Label^>(5);
//			this->answerCheckBoxes = gcnew array<System::Windows::Forms::CheckBox^, 2>(5, 4);
//			this->correctAnswers = gcnew array<int>{ 0, 1, 2, 1, 0 };  // Indexul răspunsului corect
//
//			int yOffset = 20;
//
//			// 🔹 Creare etichete întrebări și checkbox-uri răspunsuri
//			for (int i = 0; i < 5; i++)
//			{
//				// Etichetă întrebare
//				this->questionLabels[i] = gcnew System::Windows::Forms::Label();
//				this->questionLabels[i]->Text = questions[i];
//				this->questionLabels[i]->Font = gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold);
//				this->questionLabels[i]->Size = System::Drawing::Size(500, 30);
//				this->questionLabels[i]->Location = System::Drawing::Point(20, yOffset);
//				this->scrollPanel->Controls->Add(this->questionLabels[i]);
//
//				// Răspunsuri
//				for (int j = 0; j < 4; j++)
//				{
//					this->answerCheckBoxes[i, j] = gcnew System::Windows::Forms::CheckBox();
//					this->answerCheckBoxes[i, j]->Text = answers[i][j];
//					this->answerCheckBoxes[i, j]->Font = gcnew System::Drawing::Font(L"Arial", 10);
//					this->answerCheckBoxes[i, j]->Size = System::Drawing::Size(200, 25);
//					this->answerCheckBoxes[i, j]->Location = System::Drawing::Point(40, yOffset + 30 + (j * 25));
//					this->scrollPanel->Controls->Add(this->answerCheckBoxes[i, j]);
//				}
//
//				yOffset += 130;
//			}
//
//			// 🔹 Buton verificare
//			this->buttonSubmit = gcnew System::Windows::Forms::Button();
//			this->buttonSubmit->Text = L"Verifică răspunsurile";
//			this->buttonSubmit->Size = System::Drawing::Size(200, 50);
//			this->buttonSubmit->Location = System::Drawing::Point(250, yOffset);
//			this->buttonSubmit->Click += gcnew System::EventHandler(this, &Test1Form::CheckAnswers);
//			this->scrollPanel->Controls->Add(this->buttonSubmit);
//
//			this->Controls->Add(this->labelTitle);
//			this->Controls->Add(this->scrollPanel);
//			this->ResumeLayout(false);
//		}
//#pragma endregion
//
//
//	private: System::Void CheckAnswers(System::Object^ sender, System::EventArgs^ e) {
//		int score = 0;
//
//		// Verifică răspunsurile
//		for (int i = 0; i < 5; i++)
//		{
//			if (answerCheckBoxes[i, correctAnswers[i]]->Checked)
//				score++;
//		}
//
//		// Calculează nota de la 1 la 10
//		int grade = (score * 10) / 5;
//		String^ timestamp = DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss");
//
//		// 🔹 Salvare în baza de date
//		try {
//			sql::Driver* driver = sql::mariadb::get_driver_instance();
//			sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
//			sql::Properties properties({ {"user", "root"}, {"password", ""} });
//			std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
//
//			std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
//				"INSERT INTO rezultate_teste (user, nota, data, test) VALUES (?, ?, ?, ?)"));
//			stmt->setString(1, msclr::interop::marshal_as<std::string>(username->ToString()));
//			stmt->setInt(2, grade);
//			stmt->setString(3, msclr::interop::marshal_as<std::string>(timestamp->ToString()));
//			stmt->setString(4, "Test1");
//			stmt->executeUpdate();
//		}
//		catch (sql::SQLException& e) {
//			MessageBox::Show("Eroare: " + gcnew String(e.what()), "Eroare BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		}
//
//		MessageBox::Show(L"Ai obținut nota: " + grade.ToString(), L"Rezultat Test", MessageBoxButtons::OK, MessageBoxIcon::Information);
//	}
//	};
//} 

#pragma once

#include <mariadb/conncpp.hpp>  // Conexiune la MariaDB
#include <msclr/marshal_cppstd.h>
#include <ctime>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Test1Form : public System::Windows::Forms::Form
	{
	private:
		String^ username;
		int yOffset = 20;

	public:
		Test1Form(String^ user)
		{
			username = user;
			InitializeComponent();
		}

	protected:
		~Test1Form()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::Button^ buttonSubmit;
		array<System::Windows::Forms::Label^>^ questionLabels;
		array<System::Windows::Forms::CheckBox^, 2>^ answerCheckBoxes;
		array<int>^ correctAnswers;
		System::Windows::Forms::Panel^ scrollPanel;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(230, 240, 255);

			scrollPanel = gcnew Panel();
			scrollPanel->AutoScroll = true;
			scrollPanel->Dock = DockStyle::Fill;
			scrollPanel->Padding = System::Windows::Forms::Padding(30);

			labelTitle = gcnew Label();
			labelTitle->Text = L"Test de Chimie - Clasa a 7-a";
			labelTitle->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			labelTitle->ForeColor = Color::MidnightBlue;
			labelTitle->Dock = DockStyle::Top;
			labelTitle->Height = 70;
			labelTitle->TextAlign = ContentAlignment::MiddleCenter;

			array<String^>^ questions = {
				L"1. Care este simbolul chimic al oxigenului?",
				L"2. Ce stare de agregare are apa la temperatura camerei?",
				L"3. Cum se numește schimbarea stării de la solid la lichid?",
				L"4. Care dintre următoarele este un metal alcalin?",
				L"5. Care este formula chimică a apei?"
			};

			array<array<String^>^>^ answers = {
				gcnew array<String^> { L"O", L"Ox", L"Og", L"Om" },
				gcnew array<String^> { L"Solid", L"Lichid", L"Gazos", L"Plasmă" },
				gcnew array<String^> { L"Evaporare", L"Condensare", L"Topire", L"Sublimare" },
				gcnew array<String^> { L"Calciu", L"Litiu", L"Fier", L"Carbon" },
				gcnew array<String^> { L"H2O", L"O2", L"H2", L"CO2" }
			};

			questionLabels = gcnew array<Label^>(5);
			answerCheckBoxes = gcnew array<CheckBox^, 2>(5, 4);
			correctAnswers = gcnew array<int>{ 0, 1, 2, 1, 0 };

			yOffset = 100;

			for (int i = 0; i < 5; i++)
			{
				questionLabels[i] = gcnew Label();
				questionLabels[i]->Text = questions[i];
				questionLabels[i]->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
				questionLabels[i]->Size = Drawing::Size(600, 30);
				questionLabels[i]->Location = Point(20, yOffset);
				scrollPanel->Controls->Add(questionLabels[i]);

				for (int j = 0; j < 4; j++)
				{
					answerCheckBoxes[i, j] = gcnew CheckBox();
					answerCheckBoxes[i, j]->Text = answers[i][j];
					answerCheckBoxes[i, j]->Font = gcnew Drawing::Font("Arial", 10);
					answerCheckBoxes[i, j]->Size = Drawing::Size(300, 25);
					answerCheckBoxes[i, j]->Location = Point(40, yOffset + 30 + j * 30);
					answerCheckBoxes[i, j]->CheckedChanged += gcnew EventHandler(this, &Test1Form::answerCheckBox_CheckedChanged);

					array<int>^ tagArray = gcnew array<int>(2);
					tagArray[0] = i;
					tagArray[1] = j;
					answerCheckBoxes[i, j]->Tag = tagArray;

					scrollPanel->Controls->Add(answerCheckBoxes[i, j]);
				}
				yOffset += 150;
			}

			buttonSubmit = gcnew Button();
			buttonSubmit->Text = L"Verifică răspunsurile";
			buttonSubmit->Size = Drawing::Size(240, 50);
			buttonSubmit->Location = Point(180, yOffset);
			buttonSubmit->BackColor = Color::LightGreen;
			buttonSubmit->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			buttonSubmit->Click += gcnew EventHandler(this, &Test1Form::CheckAnswers);
			scrollPanel->Controls->Add(buttonSubmit);

			this->Controls->Add(labelTitle);
			this->Controls->Add(scrollPanel);
			this->scrollPanel->Dock = DockStyle::Fill;

			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void answerCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			CheckBox^ changedBox = safe_cast<CheckBox^>(sender);
			if (changedBox->Checked) {
				array<int>^ tagArray = safe_cast<array<int>^>(changedBox->Tag);
				int questionIndex = tagArray[0];
				int answerIndex = tagArray[1];
				for (int k = 0; k < 4; k++) {
					if (k != answerIndex) answerCheckBoxes[questionIndex, k]->Checked = false;
				}
			}
		}

		System::Void CheckAnswers(System::Object^ sender, System::EventArgs^ e) {
			int score = 0;
			for (int i = 0; i < 5; i++)
				if (answerCheckBoxes[i, correctAnswers[i]]->Checked) score++;

			int grade = (score * 10) / 5;
			String^ timestamp = DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss");

			try {
				sql::Driver* driver = sql::mariadb::get_driver_instance();
				sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
				sql::Properties properties({ {"user", "root"}, {"password", ""} });
				std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

				std::string userStr = msclr::interop::marshal_as<std::string>(username->ToString());
				std::string timeStr = msclr::interop::marshal_as<std::string>(timestamp->ToString());

				std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
					"INSERT INTO rezultate_teste (user, nota, data, test) VALUES (?, ?, ?, ?)"));
				stmt->setString(1, userStr);
				stmt->setInt(2, grade);
				stmt->setString(3, timeStr);
				stmt->setString(4, "Test1");
				stmt->executeUpdate();
			}
			catch (sql::SQLException& e) {
				MessageBox::Show("Eroare: " + gcnew String(e.what()), "Eroare BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			MessageBox::Show("Ai obținut nota: " + grade.ToString(), "Rezultat Test", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	};
}
