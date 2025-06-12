#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaMasaSubstanteiForm : public Form
	{
	public:
		ProblemaMasaSubstanteiForm()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblCm;
		Label^ lblV;
		RichTextBox^ richRezolvare;
		TextBox^ txtCm;
		TextBox^ txtV;
		Button^ btnRezolva;
		Label^ lblCerin;

		void InitializeComponent(void)
		{
			this->Text = L"Determinarea masei substanței";
			this->Size = Drawing::Size(800, 600);
			this->BackColor = Color::White;
			this->WindowState = FormWindowState::Maximized;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Calculează masa substanței (m)";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->AutoSize = true;
			this->Controls->Add(lblTitlu);

			lblCerin = gcnew Label();
			lblCerin->Text = L"Cerință: Se cunosc concentrația molară (Cm) și volumul soluției (V). \n Calculează masa substanței dizolvate.";
			lblCerin->Location = Point(30, 70);
			lblCerin->Size = Drawing::Size(700, 60);
			this->Controls->Add(lblCerin);

			lblCm = gcnew Label();
			lblCm->Text = L"Concentrația molară (mol/L):";
			lblCm->Location = Point(30, 140);
			lblCm->AutoSize = true;
			this->Controls->Add(lblCm);

			txtCm = gcnew TextBox();
			txtCm->Location = Point(300, 140);
			this->Controls->Add(txtCm);

			lblV = gcnew Label();
			lblV->Text = L"Volumul soluției (L):";
			lblV->Location = Point(30, 180);
			lblV->AutoSize = true;
			this->Controls->Add(lblV);

			txtV = gcnew TextBox();
			txtV->Location = Point(300, 180);
			this->Controls->Add(txtV);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolvă";
			btnRezolva->Location = Point(30, 230);
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaMasaSubstanteiForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 280);
			richRezolvare->Size = Drawing::Size(700, 250);
			richRezolvare->ReadOnly = true;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double Cm, V;
			if (Double::TryParse(txtCm->Text, Cm) && Double::TryParse(txtV->Text, V))
			{
				const double masaMolara = 58.5; // exemplu pentru NaCl
				double n = Cm * V;
				double m = n * masaMolara;

				richRezolvare->Clear();

				// PASUL 1
				richRezolvare->AppendText(L"PASUL 1: Calculăm numărul de moli (n) folosind concentrația molară și volumul.\n");
				richRezolvare->AppendText(L"Formula: n = Cm × V\n");
				richRezolvare->AppendText("Unde:\n");
				richRezolvare->AppendText("  Cm = " + Cm.ToString("F2") + " mol/L (concentrația molară)\n");
				richRezolvare->AppendText("  V = " + V.ToString("F2") + " L (volumul soluției)\n");
				richRezolvare->AppendText("=> n = " + Cm.ToString("F2") + " × " + V.ToString("F2") + " = " + n.ToString("F2") + " mol\n\n");

				// PASUL 2
				richRezolvare->AppendText(L"PASUL 2: Calculăm masa substanței dizolvate folosind numărul de moli și masa molară.\n");
				richRezolvare->AppendText(L"Formula: m = n × M\n");
				richRezolvare->AppendText("Unde:\n");
				richRezolvare->AppendText("  M = " + masaMolara.ToString("F2") + " g/mol (masa molară a NaCl)\n");
				richRezolvare->AppendText("  n = " + n.ToString("F2") + " mol (calculat anterior)\n");
				richRezolvare->AppendText("=> m = " + n.ToString("F2") + " × " + masaMolara.ToString("F2") + " = " + m.ToString("F2") + " g\n\n");

				// CONCLUZIE
				richRezolvare->AppendText(L"Rezultatul final: Ai nevoie de " + m.ToString("F2") + " grame de NaCl pentru a obține această soluție.\n");
			}
			else
			{
				MessageBox::Show("Introduceți valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

	};
}
