// PDFReaderForm.h
#pragma once

namespace LicentaChimie {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class PDFReaderForm : public System::Windows::Forms::Form
    {
    public:
        PDFReaderForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~PDFReaderForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::WebBrowser^ webBrowserPDF;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->webBrowserPDF = (gcnew System::Windows::Forms::WebBrowser());
            this->SuspendLayout();
            // 
            // webBrowserPDF
            // 
            this->webBrowserPDF->Dock = System::Windows::Forms::DockStyle::Fill;
            this->webBrowserPDF->MinimumSize = System::Drawing::Size(24, 20);
            this->webBrowserPDF->Name = L"webBrowserPDF";
            this->webBrowserPDF->TabIndex = 0;
            // 
            // PDFReaderForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1140, 700);
            this->Controls->Add(this->webBrowserPDF);
            this->Name = L"PDFReaderForm";
            this->Text = L"Cititor PDF - Chimie";
            this->Load += gcnew System::EventHandler(this, &PDFReaderForm::PDFReaderForm_Load);
            this->ResumeLayout(false);
        }
#pragma endregion

    private: System::Void PDFReaderForm_Load(System::Object^ sender, System::EventArgs^ e) {
        String^ pdfPath = Application::StartupPath + "\\Manual-Chimie-cl-7.pdf";

        if (System::IO::File::Exists(pdfPath)) {
            System::Diagnostics::Process::Start(pdfPath);
            this->Close();
        }
        else {
            MessageBox::Show("Fișierul PDF nu a fost găsit în folderul aplicației:\n" + pdfPath,
                "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }



    };
}
