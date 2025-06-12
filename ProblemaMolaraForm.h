#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ConcentratieMolaraForm : public Form
	{
	public:
		ConcentratieMolaraForm()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblCerinta;
		Label^ lblMol;
		Label^ lblVolum;
		TextBox^ txtMol;
		TextBox^ txtVolum;
		Button^ btnRezolva;
		RichTextBox^ richRezolvare;

		void InitializeComponent(void)
		{
			this->Text = L"Problem? - Concentra?ie Molar? (Cm)";
			this->Size = Drawing::Size(900, 600);
			this->BackColor = Color::White;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Exerci?iu: Calculul concentra?iei molare";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->AutoSize = true;
			this->Controls->Add(lblTitlu);

			lblCerinta = gcnew Label();
			lblCerinta->Text = L"Se dizolv? un anumit num?r de moli de substan?? într-un anumit volum de solu?ie.\nConcentra?ia molar? exprim? câ?i moli de substan?? sunt dizolva?i într-un litru de solu?ie.\nFormula folosit? este: Cm = n / V";
			lblCerinta->Font = gcnew Drawing::Font("Segoe UI", 11);
			lblCerinta->Location = Point(30, 70);
			lblCerinta->Size = Drawing::Size(800, 80);
			this->Controls->Add(lblCerinta);

			lblMol = gcnew Label();
			lblMol->Text = L"Num?r de moli (mol):";
			lblMol->Location = Point(30, 160);
			lblMol->AutoSize = true;
			lblMol->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblMol);

			txtMol = gcnew TextBox();
			txtMol->Location = Point(250, 155);
			txtMol->Width = 100;
			this->Controls->Add(txtMol);

			lblVolum = gcnew Label();
			lblVolum->Text = L"Volum solu?ie (L):";
			lblVolum->Location = Point(30, 200);
			lblVolum->AutoSize = true;
			lblVolum->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblVolum);

			txtVolum = gcnew TextBox();
			txtVolum->Location = Point(250, 195);
			txtVolum->Width = 100;
			this->Controls->Add(txtVolum);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolv?";
			btnRezolva->Location = Point(30, 250);
			btnRezolva->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			btnRezolva->BackColor = Color::LightBlue;
			btnRezolva->Click += gcnew EventHandler(this, &ConcentratieMolaraForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 310);
			richRezolvare->Size = Drawing::Size(800, 220);
			richRezolvare->ReadOnly = true;
			richRezolvare->Font = gcnew Drawing::Font("Consolas", 11);
			richRezolvare->BackColor = Color::LightYellow;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double moli, volum;
			if (Double::TryParse(txtMol->Text, moli) && Double::TryParse(txtVolum->Text, volum) && volum > 0)
			{
				double cm = moli / volum;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"PASUL 1: Re?inem formula concentra?iei molare:\n");
				richRezolvare->AppendText(L"         Cm = n / V\n\n");
				richRezolvare->AppendText(L"PASUL 2: Identific?m datele din problem?:\n");
				richRezolvare->AppendText("         n = " + moli.ToString("F2") + " mol\n");
				richRezolvare->AppendText("         V = " + volum.ToString("F2") + " L\n\n");
				richRezolvare->AppendText(L"PASUL 3: Aplic?m formula:\n");
				richRezolvare->AppendText("         Cm = " + moli.ToString("F2") + " / " + volum.ToString("F2") + "\n\n");
				richRezolvare->AppendText(L"Rezultatul final:\n");
				richRezolvare->AppendText("         Cm = " + cm.ToString("F2") + " mol/L\n");
			}
			else
			{
				MessageBox::Show("Introduce?i valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}