#pragma once
#include <ctime>
#include <cstdlib>
#include <map>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class JocStructuraAtomForm : public Form {
	private:
		Label^ lblZ;
		TextBox^ txtProtoni;
		TextBox^ txtElectroni;
		TextBox^ txtNeutroni;
		Button^ btnVerifica;
		Button^ btnNou;
		Label^ lblFeedback;
		Label^ lblTeorie;
		Button^ btnAjutor;
		int currentZ;
		Dictionary<int, int>^ neutroniCorecti;

	public:
		JocStructuraAtomForm() {
			InitializeComponent();
			GenereazaZ(nullptr, nullptr);
		}

	private:
		void InitializeComponent() {
			this->Text = L"🧚 Joc: Structura Atomului";
			this->Size = Drawing::Size(720, 640);
			this->BackColor = Color::FromArgb(245, 235, 255);
			this->Font = gcnew Drawing::Font("Segoe UI", 28, FontStyle::Bold);


			lblZ = gcnew Label();
			lblZ->Font = gcnew Drawing::Font("Segoe UI", 28, FontStyle::Bold);
			lblZ->ForeColor = Color::DarkViolet;
			lblZ->Location = Point(30, 30);
			lblZ->Size = Drawing::Size(400, 50);
			this->Controls->Add(lblZ);

			lblTeorie = gcnew Label();
			lblTeorie->Text =
				"🔬 Atomul are protoni, electroni și neutroni.\n"
				"⚛ Z = protoni = electroni | Neutronii ≈ Z (izotopi)\n"
				"🔎 Completează câmpurile și apasă Verifică!";
			lblTeorie->Location = Point(30, 100);
			lblTeorie->Size = Drawing::Size(650, 80);
			lblTeorie->ForeColor = Color::DarkSlateBlue;
			lblTeorie->BackColor = Color::LavenderBlush;
			lblTeorie->Padding = System::Windows::Forms::Padding(10);
			lblTeorie->Font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Regular);
			this->Controls->Add(lblTeorie);

			this->Controls->Add(MakeLabel("🧪 Protoni:", 30, 200));
			txtProtoni = MakeTextbox(180, 200);
			this->Controls->Add(txtProtoni);

			this->Controls->Add(MakeLabel("⚡ Electroni:", 30, 240));
			txtElectroni = MakeTextbox(180, 240);
			this->Controls->Add(txtElectroni);

			this->Controls->Add(MakeLabel("🩱 Neutroni:", 30, 280));
			txtNeutroni = MakeTextbox(180, 280);
			this->Controls->Add(txtNeutroni);

			btnVerifica = MakeButton("✅ Verifică", 30, 350, Color::LightSkyBlue);
			btnVerifica->Click += gcnew EventHandler(this, &JocStructuraAtomForm::Verifica);
			this->Controls->Add(btnVerifica);

			btnNou = MakeButton("🔄 Atom nou", 180, 350, Color::LightGreen);
			btnNou->Click += gcnew EventHandler(this, &JocStructuraAtomForm::GenereazaZ);
			this->Controls->Add(btnNou);

			btnAjutor = MakeButton("❓ Ajutor", 330, 350, Color::LightCoral);
			btnAjutor->Click += gcnew EventHandler(this, &JocStructuraAtomForm::AfiseazaTeorie);
			this->Controls->Add(btnAjutor);

			lblFeedback = gcnew Label();
			lblFeedback->Location = Point(30, 420);
			lblFeedback->Size = Drawing::Size(640, 80);
			lblFeedback->Font = gcnew Drawing::Font("Comic Sans MS", 12);
			lblFeedback->ForeColor = Color::MidnightBlue;
			lblFeedback->BackColor = Color::FromArgb(255, 255, 230);
			lblFeedback->Padding = System::Windows::Forms::Padding(10);
			lblFeedback->BorderStyle = BorderStyle::FixedSingle;
			this->Controls->Add(lblFeedback);

			neutroniCorecti = gcnew Dictionary<int, int>();
			neutroniCorecti[1] = 0;
			neutroniCorecti[2] = 2;
			neutroniCorecti[6] = 6;
			neutroniCorecti[7] = 7;
			neutroniCorecti[8] = 8;
			neutroniCorecti[11] = 12;
			neutroniCorecti[17] = 18;
			neutroniCorecti[19] = 20;
			neutroniCorecti[20] = 20;
		}

		Label^ MakeLabel(String^ text, int x, int y) {
			Label^ lbl = gcnew Label();
			lbl->Text = text;
			lbl->Location = Point(x, y);
			lbl->AutoSize = true;
			lbl->Font = gcnew Drawing::Font("Comic Sans MS", 12);
			lbl->ForeColor = Color::DarkSlateGray;
			return lbl;
		}

		TextBox^ MakeTextbox(int x, int y) {
			TextBox^ box = gcnew TextBox();
			box->Location = Point(x, y);
			box->Size = Drawing::Size(100, 30);
			box->Font = gcnew Drawing::Font("Segoe UI", 11);
			return box;
		}

		Button^ MakeButton(String^ text, int x, int y, Color color) {
			Button^ btn = gcnew Button();
			btn->Text = text;
			btn->Location = Point(x, y);
			btn->Size = Drawing::Size(120, 40);
			btn->BackColor = color;
			btn->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			return btn;
		}

		void GenereazaZ(Object^ sender, EventArgs^ e) {
			Random^ rnd = gcnew Random();
			List<int>^ chei = gcnew List<int>(neutroniCorecti->Keys);
			currentZ = chei[rnd->Next(chei->Count)];
			lblZ->Text = "🔢 Z = " + currentZ.ToString();
			txtProtoni->Text = "";
			txtElectroni->Text = "";
			txtNeutroni->Text = "";
			lblFeedback->Text = "";
		}

		void Verifica(Object^ sender, EventArgs^ e) {
			int p, electr, n;
			if (Int32::TryParse(txtProtoni->Text, p) &&
				Int32::TryParse(txtElectroni->Text, electr) &&
				Int32::TryParse(txtNeutroni->Text, n))
			{
				bool corect = (p == currentZ && electr == currentZ && n == neutroniCorecti[currentZ]);
				if (corect) {
					lblFeedback->Text = "✔ Bravo! Ai construit atomul corect!";
					lblFeedback->ForeColor = Color::Green;
				}
				else {
					lblFeedback->Text = "✖ Hmm, nu e corect. Încearcă din nou!";
					lblFeedback->ForeColor = Color::Crimson;
				}
			}
			else {
				MessageBox::Show("Introduceți valori numerice corecte!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void AfiseazaTeorie(Object^ sender, EventArgs^ e) {
			String^ mesaj =
				"🧠 Teorie:\n\n"
				"- Numărul atomic Z = numărul de protoni = electroni (atom neutru)\n"
				"- Neutronii ≈ Z (variază ușor, izotopi)\n\n"
				"Exemplu pentru Z = " + currentZ.ToString() + ":\n"
				"➔ protoni = " + currentZ.ToString() + "\n"
				"➔ electroni = " + currentZ.ToString() + "\n"
				"➔ neutroni ≈ " + neutroniCorecti[currentZ].ToString();

			MessageBox::Show(mesaj, "Ajutor – Structura Atomului", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	};
}
