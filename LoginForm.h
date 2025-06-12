#pragma once

#include <mariadb/conncpp.hpp>
#include <msclr/marshal_cppstd.h>
#include "MainForm.h"

namespace LicentaChimie {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        LoginForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~LoginForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Button^ btnLogin;

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    

           System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
               this->txtUsername = (gcnew System::Windows::Forms::TextBox());
               this->txtPassword = (gcnew System::Windows::Forms::TextBox());
               this->btnLogin = (gcnew System::Windows::Forms::Button());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->label3 = (gcnew System::Windows::Forms::Label());
               this->SuspendLayout();
               // 
               // txtUsername
               // 
               this->txtUsername->Location = System::Drawing::Point(632, 212);
               this->txtUsername->Name = L"txtUsername";
               this->txtUsername->Size = System::Drawing::Size(200, 31);
               this->txtUsername->TabIndex = 0;
               // 
               // txtPassword
               // 
               this->txtPassword->Location = System::Drawing::Point(632, 293);
               this->txtPassword->Name = L"txtPassword";
               this->txtPassword->Size = System::Drawing::Size(200, 31);
               this->txtPassword->TabIndex = 1;
               this->txtPassword->UseSystemPasswordChar = true;
               // 
               // btnLogin
               // 
               this->btnLogin->BackColor = System::Drawing::Color::DarkSalmon;
               this->btnLogin->Location = System::Drawing::Point(550, 471);
               this->btnLogin->Name = L"btnLogin";
               this->btnLogin->Size = System::Drawing::Size(157, 50);
               this->btnLogin->TabIndex = 2;
               this->btnLogin->Text = L"Login";
               this->btnLogin->UseVisualStyleBackColor = false;
               this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->BackColor = System::Drawing::Color::Transparent;
               this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->label1->Location = System::Drawing::Point(408, 218);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(464, 74);
               this->label1->TabIndex = 3;
               this->label1->Text = L"Nume utilizator";
               // 
               // label2
               // 
               this->label2->AutoSize = true;
               this->label2->BackColor = System::Drawing::Color::Transparent;
               this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->label2->Location = System::Drawing::Point(408, 296);
               this->label2->Name = L"label2";
               this->label2->Size = System::Drawing::Size(220, 74);
               this->label2->TabIndex = 2;
               this->label2->Text = L"Parola";
               // 
               // label3
               // 
               this->label3->AutoSize = true;
               this->label3->BackColor = System::Drawing::Color::Transparent;
               this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->label3->Location = System::Drawing::Point(542, 49);
               this->label3->Name = L"label3";
               this->label3->Size = System::Drawing::Size(812, 166);
               this->label3->TabIndex = 1;
               this->label3->Text = L"Intră în cont";
               // 
               // LoginForm
               // 
               this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
               this->ClientSize = System::Drawing::Size(1201, 717);
               this->Controls->Add(this->label3);
               this->Controls->Add(this->label2);
               this->Controls->Add(this->label1);
               this->Controls->Add(this->btnLogin);
               this->Controls->Add(this->txtPassword);
               this->Controls->Add(this->txtUsername);
               this->Name = L"LoginForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Login";
               this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
               this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load_1);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ username = txtUsername->Text;
        String^ password = txtPassword->Text;

        if (String::IsNullOrWhiteSpace(username) || String::IsNullOrWhiteSpace(password)) {
            MessageBox::Show("Introduceți un nume de utilizator și o parolă valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        try {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            sql::SQLString url("jdbc:mariadb://localhost:3306/chimie_db");
            sql::Properties properties({ {"user", "root"}, {"password", ""} });
            std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

            std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?"));
            stmt->setString(1, msclr::interop::marshal_as<std::string>(username));
            stmt->setString(2, msclr::interop::marshal_as<std::string>(password));
            std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

            if (res->next()) {
                MessageBox::Show("Autentificare reușită!", "Succes", MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Trimite username-ul către MainForm
                this->Hide();
                MainForm^ mainForm = gcnew MainForm(username);
                mainForm->ShowDialog();
                this->Close();
            }
            else {
                MessageBox::Show("Nume de utilizator sau parolă greșite.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (sql::SQLException& e) {
            MessageBox::Show("Eroare: " + gcnew String(e.what()), "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void LoginForm_Load_1(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
