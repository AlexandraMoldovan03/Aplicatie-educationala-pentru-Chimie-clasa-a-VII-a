#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaMasaSolutieiForm : public Form
	{
	public:
		ProblemaMasaSolutieiForm()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblMasaSubstantei;
		Label^ lblConcentratie;
		TextBox^ txtMasaSubstantei;
		TextBox^ txtConcentratie;
		Button^ btnRezolva;
		RichTextBox^ richRezolvare;

		void InitializeComponent(void)
		{
			this->Text = L"Problemă - Determinarea masei soluției";
			this->Size = Drawing::Size(800, 600);
			this->BackColor = Color::White;
			this->WindowState = FormWindowState::Maximized;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Calculează masa soluției (g) știind concentrația procentuală și masa substanței.\n\nConcentrația procentuală (c%) exprimă cât la sută dintr-o soluție este reprezentată de substanța dizolvată.\nPentru a afla masa soluției totale, aplicăm formula inversă: m_sol = m_subst * 100 / c%.";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->Size = Drawing::Size(720, 100);
			this->Controls->Add(lblTitlu);

			lblMasaSubstantei = gcnew Label();
			lblMasaSubstantei->Text = L"Masa substanței (g):";
			lblMasaSubstantei->Location = Point(30, 130);
			lblMasaSubstantei->AutoSize = true;
			this->Controls->Add(lblMasaSubstantei);

			txtMasaSubstantei = gcnew TextBox();
			txtMasaSubstantei->Location = Point(300, 130);
			this->Controls->Add(txtMasaSubstantei);

			lblConcentratie = gcnew Label();
			lblConcentratie->Text = L"Concentrația procentuală (c%):";
			lblConcentratie->Location = Point(30, 170);
			lblConcentratie->AutoSize = true;
			this->Controls->Add(lblConcentratie);

			txtConcentratie = gcnew TextBox();
			txtConcentratie->Location = Point(300, 170);
			this->Controls->Add(txtConcentratie);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolvă";
			btnRezolva->Location = Point(30, 220);
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaMasaSolutieiForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 270);
			richRezolvare->Size = Drawing::Size(720, 280);
			richRezolvare->ReadOnly = true;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double masaSubstanta, concentratie;
			if (Double::TryParse(txtMasaSubstantei->Text, masaSubstanta) &&
				Double::TryParse(txtConcentratie->Text, concentratie) && concentratie > 0)
			{
				double fractie = masaSubstanta / concentratie;
				double masaSolutie = fractie * 100;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"PASUL 1: Scriem formula concentrației procentuale:\n");
				richRezolvare->AppendText(L"       c% = (masa substanței / masa soluției) * 100\n\n");
				richRezolvare->AppendText(L"PASUL 2: Reformulăm pentru a afla masa soluției:\n");
				richRezolvare->AppendText(L"       masa soluției = masa substanței * 100 / c%\n\n");
				richRezolvare->AppendText("Calcul pas cu pas:\n");
				richRezolvare->AppendText("       1. masa substanței = " + masaSubstanta.ToString("F2") + " g\n");
				richRezolvare->AppendText("       2. c% = " + concentratie.ToString("F2") + " %\n");
				richRezolvare->AppendText("       3. fractie = " + masaSubstanta.ToString("F2") + " / " + concentratie.ToString("F2") + " = " + fractie.ToString("F4") + "\n");
				richRezolvare->AppendText("       4. masa soluției = fractie * 100 = " + masaSolutie.ToString("F2") + " g\n\n");
				richRezolvare->AppendText("Rezultat final:\n");
				richRezolvare->AppendText("       masa soluției = " + masaSolutie.ToString("F2") + " g\n");
			}
			else
			{
				MessageBox::Show("Introduceți valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
