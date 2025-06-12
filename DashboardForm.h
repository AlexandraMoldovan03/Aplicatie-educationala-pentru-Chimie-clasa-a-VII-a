#pragma once
#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>


namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	public ref class DashboardForm : public Form
	{
	private:
		String^ username;

	public:
		DashboardForm(String^ user)
		{
			username = user;
			InitializeComponent();
			LoadUserStats();
		}

	private:
		Label^ labelInfo;
		Chart^ chartProgress;

		void InitializeComponent()
		{
			this->Text = "Dashboard utilizator";
			this->Size = Drawing::Size(800, 500);

			// Eticheta de sus
			labelInfo = gcnew Label();
			labelInfo->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
			labelInfo->Dock = DockStyle::Top;
			labelInfo->Height = 80;
			labelInfo->TextAlign = ContentAlignment::MiddleCenter;
			this->Controls->Add(labelInfo);

			// Inițializare Chart
			chartProgress = gcnew Chart();
			chartProgress->Dock = DockStyle::Fill;

			ChartArea^ area = gcnew ChartArea("MainArea");
			chartProgress->ChartAreas->Add(area);

			Series^ serie = gcnew Series("Note");
			serie->ChartType = SeriesChartType::Line;
			chartProgress->Series->Add(serie);

			// Titlu pe stânga, vertical
			Title^ titlu = gcnew Title("Progresul notelor în timp");
			titlu->Docking = Docking::Left;
			titlu->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			titlu->ForeColor = Color::DarkSlateGray;
			titlu->TextOrientation = TextOrientation::Rotated270;
			chartProgress->Titles->Add(titlu);

			this->Controls->Add(chartProgress);
		}



		void LoadUserStats()
		{
			try {
				msclr::interop::marshal_context context;
				std::string userStr = context.marshal_as<std::string>(username);

				sql::Driver* driver = sql::mariadb::get_driver_instance();
				sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
				sql::Properties props({ {"user", "root"}, {"password", ""} });
				std::unique_ptr<sql::Connection> conn(driver->connect(url, props));

				// Timp total
				auto stmt = conn->prepareStatement("SELECT SUM(durata_secunde) FROM sesiuni_invatare WHERE username = ?");
				stmt->setString(1, userStr);
				auto rs = stmt->executeQuery();
				rs->next();
				int totalSecunde = rs->getInt(1);
				std::unique_ptr<sql::PreparedStatement> stmtZile(conn->prepareStatement(
					"SELECT COUNT(DISTINCT DATE(start_time)) FROM sesiuni_invatare WHERE username = ?"));
				stmtZile->setString(1, userStr);
				std::unique_ptr<sql::ResultSet> rsZile(stmtZile->executeQuery());

				rsZile->next();
				int zile = rsZile->getInt(1);
				// Conversie timp total
				int oreTotale = totalSecunde / 3600;
				int minuteTotale = (totalSecunde % 3600) / 60;
				int secundeTotale = totalSecunde % 60;

				int mediaZilnicaSec = zile > 0 ? totalSecunde / zile : 0;
				int mediaOre = mediaZilnicaSec / 3600;
				int mediaMin = (mediaZilnicaSec % 3600) / 60;
				int mediaSec = mediaZilnicaSec % 60;

				labelInfo->Text =
					"Timp total învățare: " + oreTotale + "h " + minuteTotale + "m " + secundeTotale + "s" + Environment::NewLine +
					"Media zilnică: " + mediaOre + "h " + mediaMin + "m " + mediaSec + "s";

				// Grafic note
				std::unique_ptr<sql::PreparedStatement> stmt2(conn->prepareStatement(
					"SELECT data, nota FROM rezultate_teste WHERE user = ? ORDER BY data"));
				stmt2->setString(1, userStr);

				std::unique_ptr<sql::ResultSet> rs2(stmt2->executeQuery());

				while (rs2->next()) {
					String^ data = gcnew String(rs2->getString("data").c_str());
					int nota = rs2->getInt("nota");
					chartProgress->Series["Note"]->Points->AddXY(data, nota);
				}

			}
			catch (sql::SQLException& e) {
				MessageBox::Show("Eroare MySQL: " + gcnew String(e.what()));
			}
		}
	};
}
