#include "RegisterForm.h"
#include "LoginForm.h"#include "RegisterForm.h"
#include "LoginForm.h"

[STAThread]
void Main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    LicentaChimie::RegisterForm registerForm;
    registerForm.ShowDialog();

    LicentaChimie::LoginForm loginForm;
    loginForm.ShowDialog();
}


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Deschide formularul Register
    LicentaChimie::RegisterForm registerForm;
    registerForm.ShowDialog();

    // Deschide formularul Login
    LicentaChimie::LoginForm loginForm;
    loginForm.ShowDialog();
}
