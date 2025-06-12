#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MasaSolutieiForm : public Form
	{
	public:
		MasaSolutieiForm()
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
			this->Text = L"Problem? - Determinarea masei solu?iei";
			this->Size = Drawing::Size(800, 600);
			this->BackColor = Color::White;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Calculeaz? masa solu?iei (g) ?tiind concentra?ia procentual? ?i masa substan?ei";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
			lblTitlu->Location = Point(30, 30);
			lblTitlu->Size = Drawing::Size(700, 60);
			this->Controls->Add(lblTitlu);

			lblMasaSubstantei = gcnew Label();
			lblMasaSubstantei->Text = L"Masa substan?ei (g):";
			lblMasaSubstantei->Location = Point(30, 100);
			lblMasaSubstantei->AutoSize = true;
			this->Controls->Add(lblMasaSubstantei);

			txtMasaSubstantei = gcnew TextBox();
			txtMasaSubstantei->Location = Point(300, 100);
			this->Controls->Add(txtMasaSubstantei);

			lblConcentratie = gcnew Label();
			lblConcentratie->Text = L"Concentra?ia procentual? (c%):";
			lblConcentratie->Location = Point(30, 140);
			lblConcentratie->AutoSize = true;
			this->Controls->Add(lblConcentratie);

			txtConcentratie = gcnew TextBox();
			txtConcentratie->Location = Point(300, 140);
			this->Controls->Add(txtConcentratie);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolv?";
			btnRezolva->Location = Point(30, 190);
			btnRezolva->Click += gcnew EventHandler(this, &MasaSolutieiForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 240);
			richRezolvare->Size = Drawing::Size(700, 300);
			richRezolvare->ReadOnly = true;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double masaSubstanta, concentratie;
			if (Double::TryParse(txtMasaSubstantei->Text, masaSubstanta) &&
				Double::TryParse(txtConcentratie->Text, concentratie) && concentratie > 0)
			{
				double masaSolutie = masaSubstanta * 100 / concentratie;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"Formul?: c% = (m_subst / m_sol) * 100\n");
				richRezolvare->AppendText(L"Reformulare: m_sol = m_subst * 100 / c%\n\n");
				richRezolvare->AppendText("m_sol = " + masaSubstanta.ToString("F2") + " * 100 / " + concentratie.ToString("F2") + "\n");
				richRezolvare->AppendText("m_sol = " + masaSolutie.ToString("F2") + " g\n");
			}
			else
			{
				MessageBox::Show("Introduce?i valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
