#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaVolumForm1 : public Form
	{
	public:
		ProblemaVolumForm1()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblMol;
		Label^ lblCm;
		TextBox^ txtMol;
		TextBox^ txtCm;
		Button^ btnRezolva;
		RichTextBox^ richRezolvare;

		void InitializeComponent(void)
		{
			this->Text = L"Problemă - Determinarea volumului soluției";
			this->Size = Drawing::Size(850, 600);
			this->BackColor = Color::White;
			this->WindowState = FormWindowState::Maximized;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Calculul volumului soluției (V), cunoscând numărul de moli și concentrația molară (Cm).\n\nFormula este: V = n / Cm";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->Size = Drawing::Size(750, 70);
			this->Controls->Add(lblTitlu);

			lblMol = gcnew Label();
			lblMol->Text = L"Număr de moli (mol):";
			lblMol->Location = Point(30, 110);
			lblMol->AutoSize = true;
			this->Controls->Add(lblMol);

			txtMol = gcnew TextBox();
			txtMol->Location = Point(250, 105);
			this->Controls->Add(txtMol);

			lblCm = gcnew Label();
			lblCm->Text = L"Concentrație molară (mol/L):";
			lblCm->Location = Point(30, 150);
			lblCm->AutoSize = true;
			this->Controls->Add(lblCm);

			txtCm = gcnew TextBox();
			txtCm->Location = Point(250, 145);
			this->Controls->Add(txtCm);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolvă";
			btnRezolva->Location = Point(30, 200);
			btnRezolva->BackColor = Color::LightBlue;
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaVolumForm1::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 260);
			richRezolvare->Size = Drawing::Size(770, 280);
			richRezolvare->ReadOnly = true;
			richRezolvare->Font = gcnew Drawing::Font("Consolas", 11);
			richRezolvare->BackColor = Color::LightYellow;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double n, Cm;
			if (Double::TryParse(txtMol->Text, n) && Double::TryParse(txtCm->Text, Cm) && Cm > 0)
			{
				double V = n / Cm;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"PASUL 1: Ce cunoaștem:\n");
				richRezolvare->AppendText(" - Număr de moli n = " + n.ToString("F2") + " mol\n");
				richRezolvare->AppendText(" - Concentrație molară Cm = " + Cm.ToString("F2") + " mol/L\n\n");

				richRezolvare->AppendText(L"PASUL 2: Formula utilizată:\n");
				richRezolvare->AppendText(" V = n / Cm\n\n");

				richRezolvare->AppendText(L"PASUL 3: Aplicăm valorile:\n");
				richRezolvare->AppendText(" V = " + n.ToString("F2") + " / " + Cm.ToString("F2") + " = " + V.ToString("F2") + " L\n\n");

				richRezolvare->AppendText(L"Rezultat final:\n");
				richRezolvare->AppendText(" Volumul soluției este: " + V.ToString("F2") + " L\n");
			}
			else
			{
				MessageBox::Show("Introduceți valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
