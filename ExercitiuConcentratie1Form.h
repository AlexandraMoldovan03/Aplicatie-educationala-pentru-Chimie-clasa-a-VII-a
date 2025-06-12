#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ExercitiuConcentratie1Form : public Form
	{
	public:
		ExercitiuConcentratie1Form()
		{
			InitializeComponent();
		}

	private:
		Label^ lblEnunt;
		RichTextBox^ txtRezolvare;
		Button^ btnVerifica;
		Button^ btnArata;
		Label^ lblFeedback;

		void InitializeComponent(void)
		{
			this->Text = L"Formular Exercițiu Ghidat – Concentrație";
			this->Size = Drawing::Size(900, 600);
			this->BackColor = Color::WhiteSmoke;

			lblEnunt = gcnew Label();
			lblEnunt->Text = L"Un elev dizolvă 60g NaCl într-o soluție de 150g. Calculați c%";
			lblEnunt->Location = Point(30, 30);
			lblEnunt->AutoSize = true;
			this->Controls->Add(lblEnunt);

			txtRezolvare = gcnew RichTextBox();
			txtRezolvare->Location = Point(30, 70);
			txtRezolvare->Size = Drawing::Size(700, 250);
			this->Controls->Add(txtRezolvare);

			btnVerifica = gcnew Button();
			btnVerifica->Text = L"Verifică";
			btnVerifica->Location = Point(30, 340);
			btnVerifica->Click += gcnew EventHandler(this, &ExercitiuConcentratie1Form::btnVerifica_Click);
			this->Controls->Add(btnVerifica);

			btnArata = gcnew Button();
			btnArata->Text = L"Arată rezolvarea";
			btnArata->Location = Point(150, 340);
			btnArata->Click += gcnew EventHandler(this, &ExercitiuConcentratie1Form::btnArata_Click);
			this->Controls->Add(btnArata);

			lblFeedback = gcnew Label();
			lblFeedback->Location = Point(30, 400);
			lblFeedback->Size = Drawing::Size(700, 80);
			lblFeedback->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			this->Controls->Add(lblFeedback);
		}

		void btnVerifica_Click(Object^ sender, EventArgs^ e)
		{
			String^ raspuns = txtRezolvare->Text->Replace(" ", "")->ToLower();

			if (raspuns->Contains("60/150") && raspuns->Contains("*100") && (raspuns->Contains("40") || raspuns->Contains("40%")))
			{
				lblFeedback->Text = L"✔ Corect! Ai aplicat formula bine și ai obținut rezultatul corect.";
				lblFeedback->ForeColor = Color::Green;
			}
			else
			{
				lblFeedback->Text = L"✖ Verifică formula, împărțirea sau înmulțirea. Încearcă din nou.";
				lblFeedback->ForeColor = Color::Red;
			}
		}

		void btnArata_Click(Object^ sender, EventArgs^ e)
		{
			txtRezolvare->Text =
				L"PASUL 1: Folosim formula: c% = (m_subst / m_sol) * 100\n"
				L"PASUL 2: Înlocuim valorile: c% = (60 / 150) * 100\n"
				L"PASUL 3: c% = 0.4 * 100 = 40%\n"
				L"Rezultat: Concentrația este 40%";
		}
	};
}
