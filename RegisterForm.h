#pragma once

#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>
#include "LoginForm.h"

namespace LicentaChimie {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RegisterForm : public System::Windows::Forms::Form
    {
    public:
        RegisterForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~RegisterForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::Button^ btnRegister;
        System::Windows::Forms::Label^ labelTitle;
        System::Windows::Forms::Label^ labelUsername;
        System::Windows::Forms::Label^ labelPassword;
        System::Windows::Forms::Label^ labelEmail;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RegisterForm::typeid));
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            this->labelUsername = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->labelPassword = (gcnew System::Windows::Forms::Label());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->labelEmail = (gcnew System::Windows::Forms::Label());
            this->txtEmail = (gcnew System::Windows::Forms::TextBox());
            this->btnRegister = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // labelTitle
            // 
            this->labelTitle->Dock = System::Windows::Forms::DockStyle::Top;
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 20, System::Drawing::FontStyle::Bold));
            this->labelTitle->Location = System::Drawing::Point(0, 0);
            this->labelTitle->Name = L"labelTitle";
            this->labelTitle->Size = System::Drawing::Size(1555, 60);
            this->labelTitle->TabIndex = 0;
            this->labelTitle->Text = L"Înregistrare cont nou";
            this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // labelUsername
            // 
            this->labelUsername->Font = (gcnew System::Drawing::Font(L"Arial", 12));
            this->labelUsername->Location = System::Drawing::Point(498, 194);
            this->labelUsername->Name = L"labelUsername";
            this->labelUsername->Size = System::Drawing::Size(100, 23);
            this->labelUsername->TabIndex = 1;
            this->labelUsername->Text = L"Nume utilizator:";
            // 
            // txtUsername
            // 
            this->txtUsername->Location = System::Drawing::Point(495, 237);
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(300, 31);
            this->txtUsername->TabIndex = 2;
            // 
            // labelPassword
            // 
            this->labelPassword->Font = (gcnew System::Drawing::Font(L"Arial", 12));
            this->labelPassword->Location = System::Drawing::Point(498, 305);
            this->labelPassword->Name = L"labelPassword";
            this->labelPassword->Size = System::Drawing::Size(100, 23);
            this->labelPassword->TabIndex = 3;
            this->labelPassword->Text = L"Parolă:";
            // 
            // txtPassword
            // 
            this->txtPassword->Location = System::Drawing::Point(495, 342);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->Size = System::Drawing::Size(300, 31);
            this->txtPassword->TabIndex = 4;
            this->txtPassword->UseSystemPasswordChar = true;
            // 
            // labelEmail
            // 
            this->labelEmail->Font = (gcnew System::Drawing::Font(L"Arial", 12));
            this->labelEmail->Location = System::Drawing::Point(498, 395);
            this->labelEmail->Name = L"labelEmail";
            this->labelEmail->Size = System::Drawing::Size(100, 23);
            this->labelEmail->TabIndex = 5;
            this->labelEmail->Text = L"Email:";
            // 
            // txtEmail
            // 
            this->txtEmail->Location = System::Drawing::Point(495, 439);
            this->txtEmail->Name = L"txtEmail";
            this->txtEmail->Size = System::Drawing::Size(300, 31);
            this->txtEmail->TabIndex = 6;
            // 
            // btnRegister
            // 
            this->btnRegister->BackColor = System::Drawing::Color::LightGreen;
            this->btnRegister->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
            this->btnRegister->Location = System::Drawing::Point(568, 564);
            this->btnRegister->Name = L"btnRegister";
            this->btnRegister->Size = System::Drawing::Size(200, 50);
            this->btnRegister->TabIndex = 7;
            this->btnRegister->Text = L"Înregistrează-te";
            this->btnRegister->UseVisualStyleBackColor = false;
            this->btnRegister->Click += gcnew System::EventHandler(this, &RegisterForm::btnRegister_Click);
            // 
            // RegisterForm
            // 
            this->BackColor = System::Drawing::Color::White;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
            this->ClientSize = System::Drawing::Size(1555, 1199);
            this->Controls->Add(this->labelTitle);
            this->Controls->Add(this->labelUsername);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->labelPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->labelEmail);
            this->Controls->Add(this->txtEmail);
            this->Controls->Add(this->btnRegister);
            this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Name = L"RegisterForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Înregistrare";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->Load += gcnew System::EventHandler(this, &RegisterForm::RegisterForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ username = txtUsername->Text;
        String^ password = txtPassword->Text;
        String^ email = txtEmail->Text;

        if (String::IsNullOrWhiteSpace(username) || String::IsNullOrWhiteSpace(password) || String::IsNullOrWhiteSpace(email)) {
            MessageBox::Show("Introduceți toate datele necesare.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        try {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
            sql::Properties properties({ {"user", "root"}, {"password", ""} });
            std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

            std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
                "INSERT INTO users (username, password, email) VALUES (?, ?, ?)"));
            stmt->setString(1, msclr::interop::marshal_as<std::string>(username));
            stmt->setString(2, msclr::interop::marshal_as<std::string>(password));
            stmt->setString(3, msclr::interop::marshal_as<std::string>(email));
            stmt->execute();

            MessageBox::Show("Utilizator înregistrat cu succes!", "Succes", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Închide RegisterForm și deschide LoginForm
            this->Close();
            LicentaChimie::LoginForm^ loginForm = gcnew LicentaChimie::LoginForm();
            loginForm->ShowDialog();
        }
        catch (sql::SQLException& e) {
            MessageBox::Show("Eroare: " + gcnew String(e.what()), "Eroare BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    private: System::Void RegisterForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
