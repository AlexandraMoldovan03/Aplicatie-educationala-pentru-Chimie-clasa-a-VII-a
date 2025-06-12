#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CatalogForm : public System::Windows::Forms::Form
	{
	private:
		String^ username;
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::DataGridView^ dataGridViewTest1;
		System::Windows::Forms::DataGridView^ dataGridViewTest2;
		System::Windows::Forms::Button^ buttonRefresh;
		System::Windows::Forms::Label^ labelTest1;
		System::Windows::Forms::Label^ labelTest2;
		System::ComponentModel::Container^ components;

	public:
		CatalogForm(String^ user)
		{
			username = user;
			InitializeComponent();
			LoadGrades();
		}

	protected:
		~CatalogForm()
		{
			if (components) delete components;
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Text = L"Catalog - Notele tale";
			this->Size = System::Drawing::Size(900, 700);
			this->BackColor = Color::FromArgb(240, 248, 255);
			this->Font = gcnew Drawing::Font("Segoe UI", 10);

			labelTitle = gcnew Label();
			labelTitle->Text = "Catalogul notelor la Teste";
			labelTitle->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
			labelTitle->ForeColor = Color::MidnightBlue;
			labelTitle->TextAlign = ContentAlignment::MiddleCenter;
			labelTitle->Dock = DockStyle::Top;
			labelTitle->Height = 60;

			labelTest1 = gcnew Label();
			labelTest1->Text = "Testul 1";
			labelTest1->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
			labelTest1->ForeColor = Color::DarkSlateGray;
			labelTest1->Location = Point(60, 80);
			labelTest1->AutoSize = true;

			dataGridViewTest1 = gcnew DataGridView();
			dataGridViewTest1->Location = Point(60, 120);
			dataGridViewTest1->Size = Drawing::Size(750, 180);
			dataGridViewTest1->ReadOnly = true;
			dataGridViewTest1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dataGridViewTest1->BackgroundColor = Color::WhiteSmoke;

			labelTest2 = gcnew Label();
			labelTest2->Text = "Testul 2";
			labelTest2->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
			labelTest2->ForeColor = Color::DarkSlateGray;
			labelTest2->Location = Point(60, 320);
			labelTest2->AutoSize = true;

			dataGridViewTest2 = gcnew DataGridView();
			dataGridViewTest2->Location = Point(60, 360);
			dataGridViewTest2->Size = Drawing::Size(750, 180);
			dataGridViewTest2->ReadOnly = true;
			dataGridViewTest2->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dataGridViewTest2->BackgroundColor = Color::WhiteSmoke;

			buttonRefresh = gcnew Button();
			buttonRefresh->Text = "Reîncarcă notele";
			buttonRefresh->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			buttonRefresh->Location = Point(350, 560);
			buttonRefresh->Size = Drawing::Size(200, 45);
			buttonRefresh->BackColor = Color::Lavender;
			buttonRefresh->Click += gcnew System::EventHandler(this, &CatalogForm::LoadGrades);

			this->Controls->Add(labelTitle);
			this->Controls->Add(labelTest1);
			this->Controls->Add(dataGridViewTest1);
			this->Controls->Add(labelTest2);
			this->Controls->Add(dataGridViewTest2);
			this->Controls->Add(buttonRefresh);
		}
#pragma endregion

	private: System::Void LoadGrades(System::Object^ sender, System::EventArgs^ e) {
		LoadGrades();
	}

	private: System::Void LoadGrades() {
		try {
			sql::Driver* driver = sql::mariadb::get_driver_instance();
			sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
			sql::Properties properties({ {"user", "root"}, {"password", ""} });
			std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
			std::string userStr = msclr::interop::marshal_as<std::string>(username->ToString());

			// Test 1
			auto stmt1 = conn->prepareStatement("SELECT nota, data FROM rezultate_teste WHERE user = ? AND test = 'Test1' ORDER BY data DESC");
			stmt1->setString(1, userStr);
			auto res1 = stmt1->executeQuery();

			DataTable^ table1 = gcnew DataTable();
			table1->Columns->Add("Nota");
			table1->Columns->Add("Data");

			while (res1->next()) {
				table1->Rows->Add(gcnew String(res1->getString("nota").c_str()), gcnew String(res1->getString("data").c_str()));
			}
			dataGridViewTest1->DataSource = table1;

			// Test 2
			auto stmt2 = conn->prepareStatement("SELECT nota, data FROM rezultate_teste WHERE user = ? AND test = 'Test2' ORDER BY data DESC");
			stmt2->setString(1, userStr);
			auto res2 = stmt2->executeQuery();

			DataTable^ table2 = gcnew DataTable();
			table2->Columns->Add("Nota");
			table2->Columns->Add("Data");

			while (res2->next()) {
				table2->Rows->Add(gcnew String(res2->getString("nota").c_str()), gcnew String(res2->getString("data").c_str()));
			}
			dataGridViewTest2->DataSource = table2;
		}
		catch (sql::SQLException& e) {
			MessageBox::Show("Eroare BD: " + gcnew String(e.what()), "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void CatalogForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}