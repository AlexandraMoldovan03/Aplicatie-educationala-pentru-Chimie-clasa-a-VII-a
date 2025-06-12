#pragma once
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <fstream>
#include <msclr/marshal_cppstd.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace LicentaChimie {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class testeGenForm : public System::Windows::Forms::Form
    {
    public:
        testeGenForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~testeGenForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Button^ btnIncarca;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::TextBox^ txtTextExtras;
    private: System::Windows::Forms::Button^ btnGenereazaIntrebari;
    private: System::Windows::Forms::ListBox^ listBoxIntrebari;
    private: System::Windows::Forms::TextBox^ txtRaspuns;
    private: System::Windows::Forms::Button^ btnTrimiteRaspuns;
    private: System::Windows::Forms::Label^ nota;

           System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->btnIncarca = (gcnew System::Windows::Forms::Button());
               this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
               this->txtTextExtras = (gcnew System::Windows::Forms::TextBox());
               this->btnGenereazaIntrebari = (gcnew System::Windows::Forms::Button());
               this->listBoxIntrebari = (gcnew System::Windows::Forms::ListBox());
               this->txtRaspuns = (gcnew System::Windows::Forms::TextBox());
               this->btnTrimiteRaspuns = (gcnew System::Windows::Forms::Button());
               this->nota = (gcnew System::Windows::Forms::Label());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
               this->SuspendLayout();

               this->btnIncarca->Click += gcnew System::EventHandler(this, &testeGenForm::btnIncarca_Click);
               this->btnGenereazaIntrebari->Click += gcnew System::EventHandler(this, &testeGenForm::btnGenereazaIntrebari_Click);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private:
        System::Void btnIncarca_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Imagini|*.jpg;*.png;*.bmp|PDF|*.pdf";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                String^ filePath = openFileDialog->FileName;
                pictureBox1->Image = System::Drawing::Image::FromFile(filePath);

                std::string imagePath = msclr::interop::marshal_as<std::string>(filePath);
                ExtractTextFromImage(imagePath);
            }
        }

        void ExtractTextFromImage(std::string imagePath) {
            tesseract::TessBaseAPI ocr;
            if (ocr.Init(NULL, "eng")) {
                MessageBox::Show("Eroare la inițializarea OCR!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            Pix* image = pixRead(imagePath.c_str());
            ocr.SetImage(image);

            char* extractedText = ocr.GetUTF8Text();
            String^ text = gcnew String(extractedText);

            txtTextExtras->Text = text;

            ocr.End();
            delete[] extractedText;
            pixDestroy(&image);
        }

        std::string SendToGPT(std::string text) {
            CURL* curl = curl_easy_init();
            if (!curl) return "Eroare la inițializarea cURL!";

            std::string apiKey = "API_KEY";  // Înlocuiește cu cheia OpenAI
            std::string url = "https://api.openai.com/v1/completions";
            std::string prompt = "Extrage 3 întrebări importante din acest text:\n" + text;

            json request = {
                {"model", "gpt-4"},
                {"prompt", prompt},
                {"max_tokens", 100}
            };

            std::string jsonStr = request.dump();
            std::string responseStr;

            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) {
                data->append(ptr, size * nmemb);
                return size * nmemb;
                });
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            return responseStr;
        }

    private: System::Void btnGenereazaIntrebari_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string text = msclr::interop::marshal_as<std::string>(txtTextExtras->Text);
        std::string response = SendToGPT(text);

        listBoxIntrebari->Items->Clear();
        listBoxIntrebari->Items->Add(gcnew String(response.c_str()));
    }
    };
}
