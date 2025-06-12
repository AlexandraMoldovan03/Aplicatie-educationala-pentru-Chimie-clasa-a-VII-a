#pragma once
#pragma execution_character_set("utf-8")

#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>
#include <ctime>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Test2Form : public Form {
	private:
		String^ username;
		Label^ labelTitle;
		Button^ buttonSubmit;
		array<Label^>^ questionLabels;
		array<CheckBox^, 2>^ answerCheckBoxes;
		array<int>^ correctAnswers;
		Panel^ scrollPanel;
		System::ComponentModel::Container^ components;

	public:
		Test2Form(String^ user) {
			username = user;
			InitializeComponent();
		}

	protected:
		~Test2Form() {
			if (components) delete components;
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->SuspendLayout();
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(230, 240, 255);

			scrollPanel = gcnew Panel();
			scrollPanel->AutoScroll = true;
			scrollPanel->Dock = DockStyle::Fill;
			scrollPanel->Padding = System::Windows::Forms::Padding(30);

			labelTitle = gcnew Label();
			labelTitle->Text = L"Test de Chimie - Partea 2";
			labelTitle->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			labelTitle->ForeColor = Color::MidnightBlue;
			labelTitle->Dock = DockStyle::Top;
			labelTitle->Height = 70;
			labelTitle->TextAlign = ContentAlignment::MiddleCenter;

			array<String^>^ questions = {
				L"1. Care este simbolul chimic al hidrogenului?",
				L"2. Ce stare de agregare are aurul la temperatura camerei?",
				L"3. Ce element chimic are simbolul 'Na'?",
				L"4. Care este formula chimică a dioxidului de carbon?",
				L"5. Ce gaz este esențial pentru respirație?"
			};

			array<array<String^>^>^ answers = {
				gcnew array<String^> { L"H", L"Hy", L"He", L"Ho" },
				gcnew array<String^> { L"Solid", L"Lichid", L"Gazos", L"Plasmă" },
				gcnew array<String^> { L"Azot", L"Natriu", L"Neon", L"Fosfor" },
				gcnew array<String^> { L"CO2", L"O2", L"H2O", L"CH4" },
				gcnew array<String^> { L"Oxigen", L"Azot", L"Hidrogen", L"Argon" }
			};

			questionLabels = gcnew array<Label^>(5);
			answerCheckBoxes = gcnew array<CheckBox^, 2>(5, 4);
			correctAnswers = gcnew array<int>{ 0, 0, 1, 0, 0 };

			int yOffset = 100;

			for (int i = 0; i < 5; i++) {
				questionLabels[i] = gcnew Label();
				questionLabels[i]->Text = questions[i];
				questionLabels[i]->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
				questionLabels[i]->Size = Drawing::Size(600, 30);
				questionLabels[i]->Location = Point(20, yOffset);
				scrollPanel->Controls->Add(questionLabels[i]);

				for (int j = 0; j < 4; j++) {
					answerCheckBoxes[i, j] = gcnew CheckBox();
					answerCheckBoxes[i, j]->Text = answers[i][j];
					answerCheckBoxes[i, j]->Font = gcnew Drawing::Font("Arial", 10);
					answerCheckBoxes[i, j]->Size = Drawing::Size(300, 25);
					answerCheckBoxes[i, j]->Location = Point(40, yOffset + 30 + j * 30);
					answerCheckBoxes[i, j]->CheckedChanged += gcnew EventHandler(this, &Test2Form::answerCheckBox_CheckedChanged);

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
			buttonSubmit->Click += gcnew EventHandler(this, &Test2Form::CheckAnswers);
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
				stmt->setString(4, "Test2");
				stmt->executeUpdate();
			}
			catch (sql::SQLException& e) {
				MessageBox::Show("Eroare: " + gcnew String(e.what()), "Eroare BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			MessageBox::Show("Ai obținut nota: " + grade.ToString(), "Rezultat Test", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	};
}
