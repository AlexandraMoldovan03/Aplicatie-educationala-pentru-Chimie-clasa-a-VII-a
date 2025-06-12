#include "MainForm.h"
//#include <msclr/marshal.h>
//
//using namespace msclr::interop;
//using namespace LicentaChimie;
//
//System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
//	this->panelButoane->Left = (this->ClientSize.Width - this->panelButoane->Width) / 2;
//	this->panelButoane->Top = (this->ClientSize.Height - this->panelButoane->Height) / 2;
//}
//
//System::Void MainForm::buttonTeorie_Click(System::Object^ sender, System::EventArgs^ e) {
//	TeorieMenuForm^ teorieMenu = gcnew TeorieMenuForm(username);
//	teorieMenu->ShowDialog();
//}
//
//System::Void MainForm::buttonPeriodicTable_Click(System::Object^ sender, System::EventArgs^ e) {
//	PeriodicTableForm^ periodicTable = gcnew PeriodicTableForm();
//	periodicTable->ShowDialog();
//}
//
//System::Void MainForm::buttonResurseSuplimentare_Click(System::Object^ sender, System::EventArgs^ e) {
//	this->Hide();
//	ResurseSuplimentareMenu^ resurseSuplimentareMenu = gcnew ResurseSuplimentareMenu(username);
//	resurseSuplimentareMenu->ShowDialog();
//	this->Show();
//}
//
//System::Void MainForm::buttonTeste_Click(System::Object^ sender, System::EventArgs^ e) {
//	TestMenu^ testMenu = gcnew TestMenu(username);
//	testMenu->ShowDialog();
//}
//
//System::Void MainForm::buttonExercitii_Click(System::Object^ sender, System::EventArgs^ e) {
//	ExercitiiMenuForm^ exercitiiMenuForm = gcnew ExercitiiMenuForm(username);
//	exercitiiMenuForm->ShowDialog();
//}
//
//System::Void MainForm::MainForm_FormClosing(System::Object^ sender, FormClosingEventArgs^ e) {
//	DateTime endTime = DateTime::Now;
//	TimeSpan durata = endTime - startTime;
//	int secunde = (int)durata.TotalSeconds;
//
//	try {
//		// Conversii .NET -> std::string
//		std::string userStr = marshal_as<std::string>(username);
//		std::string startStr = marshal_as<std::string>(startTime.ToString("yyyy-MM-dd HH:mm:ss"));
//		std::string endStr = marshal_as<std::string>(endTime.ToString("yyyy-MM-dd HH:mm:ss"));
//
//		// Conectare MariaDB
//		sql::Driver* driver = sql::mariadb::get_driver_instance();
//		sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
//		sql::Properties properties({ {"user", "root"}, {"password", ""} });
//		std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
//
//		// Interogare INSERT
//		std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
//			"INSERT INTO sesiuni_invare (username, start_time, end_time, durata_secunde) VALUES (?, ?, ?, ?)"));
//
//		stmt->setString(1, userStr);
//		stmt->setString(2, startStr);
//		stmt->setString(3, endStr);
//		stmt->setInt(4, secunde);
//		stmt->execute();
//	}
//	catch (sql::SQLException& ex) {
//		MessageBox::Show("Eroare la salvarea timpului: " + gcnew String(ex.what()));
//	}
//}
