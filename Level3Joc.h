#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	ref class AmestecItem {
	public:
		String^ amestec;
		String^ metodaCorecta;
		AmestecItem(String^ a, String^ m) : amestec(a), metodaCorecta(m) {}
	};

	public ref class Level3Joc : public System::Windows::Forms::Form {
	public:
		Level3Joc(void) {
			InitializeComponent();
			IncarcaAmestecuri();
		}

	private:
		Label^ lblTitlu;
		Button^ btnRoteste;
		Label^ lblAmestec;
		Button^ btn1;
		Button^ btn2;
		Button^ btn3;
		Button^ btn4;
		Label^ lblRezultat;
		List<AmestecItem^>^ amestecuri;
		AmestecItem^ curent;
		Random^ rnd;
		void InitializeComponent() {
			this->Text = L"🎡 Separarea Amestecurilor";
			this->ClientSize = Drawing::Size(800, 600);
			this->BackColor = Color::FromArgb(230, 245, 255); // pastel bleu
			this->Font = gcnew Drawing::Font("Comic Sans MS", 10, FontStyle::Bold);

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"🎲 Apasă pe roată pentru a extrage un amestec!";
			lblTitlu->Font = gcnew Drawing::Font("Comic Sans MS", 16, FontStyle::Bold);
			lblTitlu->ForeColor = Color::MediumVioletRed;
			lblTitlu->Location = Point(50, 30);
			lblTitlu->Size = Drawing::Size(700, 40);
			this->Controls->Add(lblTitlu);

			btnRoteste = gcnew Button();
			btnRoteste->Text = L"🔄 Rotește roata!";
			btnRoteste->Font = gcnew Drawing::Font("Comic Sans MS", 12);
			btnRoteste->Size = Drawing::Size(220, 60);
			btnRoteste->Location = Point(280, 90);
			btnRoteste->BackColor = Color::MistyRose;
			btnRoteste->FlatStyle = FlatStyle::Flat;
			btnRoteste->FlatAppearance->BorderSize = 0;
			btnRoteste->Click += gcnew EventHandler(this, &Level3Joc::RotesteRoata);
			this->Controls->Add(btnRoteste);

			lblAmestec = gcnew Label();
			lblAmestec->Font = gcnew Drawing::Font("Comic Sans MS", 12);
			lblAmestec->Location = Point(100, 170);
			lblAmestec->Size = Drawing::Size(600, 40);
			lblAmestec->ForeColor = Color::DarkSlateBlue;
			this->Controls->Add(lblAmestec);

			// Butoane de răspuns
			btn1 = CreeazaButonRaspuns("", Point(100, 240), Color::Lavender);
			btn2 = CreeazaButonRaspuns("", Point(400, 240), Color::Honeydew);
			btn3 = CreeazaButonRaspuns("", Point(100, 320), Color::LemonChiffon);
			btn4 = CreeazaButonRaspuns("", Point(400, 320), Color::LightPink);

			lblRezultat = gcnew Label();
			lblRezultat->Font = gcnew Drawing::Font("Comic Sans MS", 12, FontStyle::Bold);
			lblRezultat->Location = Point(100, 420);
			lblRezultat->Size = Drawing::Size(600, 40);
			lblRezultat->TextAlign = ContentAlignment::MiddleCenter;
			this->Controls->Add(lblRezultat);

			rnd = gcnew Random();
		}


		Button^ CreeazaButonRaspuns(String^ text, Point loc, Color bg) {
			Button^ b = gcnew Button();
			b->Text = text;
			b->Font = gcnew Drawing::Font("Comic Sans MS", 11, FontStyle::Bold);
			b->Size = Drawing::Size(250, 60);
			b->Location = loc;
			b->BackColor = bg;
			b->ForeColor = Color::Black;
			b->FlatStyle = FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 0;
			b->Click += gcnew EventHandler(this, &Level3Joc::VerificaRaspuns);
			this->Controls->Add(b);
			return b;
		}


		void IncarcaAmestecuri() {
			amestecuri = gcnew List<AmestecItem^>();
			amestecuri->Add(gcnew AmestecItem("apă + nisip", "filtrare"));
			amestecuri->Add(gcnew AmestecItem("apă + ulei", "decantare"));
			amestecuri->Add(gcnew AmestecItem("apă + sare", "evaporare"));
			amestecuri->Add(gcnew AmestecItem("alcool + apă", "distilare"));
			amestecuri->Add(gcnew AmestecItem("pilitură fier + nisip", "magnetizare"));
		}

		void RotesteRoata(Object^ sender, EventArgs^ e) {
			int index = rnd->Next(amestecuri->Count);
			curent = amestecuri[index];
			lblAmestec->Text = "Amestec extras: " + curent->amestec;
			lblRezultat->Text = "";

			List<String^>^ optiuni = gcnew List<String^>();
			optiuni->Add("filtrare");
			optiuni->Add("decantare");
			optiuni->Add("evaporare");
			optiuni->Add("distilare");
			optiuni->Add("magnetizare");
			optiuni->Add("cristalizare");

			while (optiuni->Count > 4) optiuni->RemoveAt(rnd->Next(optiuni->Count));
			if (!optiuni->Contains(curent->metodaCorecta)) optiuni[rnd->Next(4)] = curent->metodaCorecta;
			
			// Amestecare manuală (înlocuiește linia cu OrderBy)
			for (int i = 0; i < optiuni->Count; i++) {
				int j = rnd->Next(i, optiuni->Count);
				String^ temp = optiuni[i];
				optiuni[i] = optiuni[j];
				optiuni[j] = temp;
			}
		

			btn1->Text = optiuni[0];
			btn2->Text = optiuni[1];
			btn3->Text = optiuni[2];
			btn4->Text = optiuni[3];
		}

		void VerificaRaspuns(Object^ sender, EventArgs^ e) {
			Button^ b = safe_cast<Button^>(sender);
			if (b->Text == curent->metodaCorecta) {
				lblRezultat->Text = "Corect! Bravo!";
				lblRezultat->ForeColor = Color::Green;
			}
			else {
				lblRezultat->Text = "Greșit! Corect era: " + curent->metodaCorecta;
				lblRezultat->ForeColor = Color::Red;
			}
		}
	};
}
