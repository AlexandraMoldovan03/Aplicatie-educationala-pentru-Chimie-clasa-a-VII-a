#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaConcentratieMolaraForm: public Form
	{
	public:
		ProblemaConcentratieMolaraForm()
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
			this->Text = L"Problemă - Concentrație Molară (Cm)";
			this->Size = Drawing::Size(900, 600);
			this->BackColor = Color::White;
			this->WindowState = FormWindowState::Maximized;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Exercițiu: Calculul concentrației molare";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->AutoSize = true;
			this->Controls->Add(lblTitlu);

			lblCerinta = gcnew Label();
			lblCerinta->Text = L"Se dizolvă n moli de substanță într-un anumit volum de soluție. Introduceți valorile pentru a calcula concentrația molară(mol / L).";
				lblCerinta->Font = gcnew Drawing::Font("Segoe UI", 11);
			lblCerinta->Location = Point(30, 70);
			lblCerinta->Size = Drawing::Size(800, 60);
			this->Controls->Add(lblCerinta);

			lblMol = gcnew Label();
			lblMol->Text = L"Număr de moli (mol):";
			lblMol->Location = Point(30, 150);
			lblMol->AutoSize = true;
			lblMol->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblMol);

			txtMol = gcnew TextBox();
			txtMol->Location = Point(250, 145);
			txtMol->Width = 100;
			this->Controls->Add(txtMol);

			lblVolum = gcnew Label();
			lblVolum->Text = L"Volum soluție (L):";
			lblVolum->Location = Point(30, 190);
			lblVolum->AutoSize = true;
			lblVolum->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblVolum);

			txtVolum = gcnew TextBox();
			txtVolum->Location = Point(250, 185);
			txtVolum->Width = 100;
			this->Controls->Add(txtVolum);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolvă";
			btnRezolva->Location = Point(30, 240);
			btnRezolva->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			btnRezolva->BackColor = Color::LightBlue;
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaConcentratieMolaraForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 300);
			richRezolvare->Size = Drawing::Size(800, 200);
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

				// PASUL 1: Ce cunoaștem
				richRezolvare->AppendText(L"PASUL 1: Ce cunoaștem:\n");
				richRezolvare->AppendText(" - Numărul de moli (n) = " + moli.ToString("F2") + " moli\n");
				richRezolvare->AppendText(" - Volumul soluției (V) = " + volum.ToString("F2") + " litri\n\n");

				// PASUL 2: Scriem formula
				richRezolvare->AppendText(L"PASUL 2: Formula concentrației molare este:\n");
				richRezolvare->AppendText(L"         Cm = n / V\n");
				richRezolvare->AppendText("         (unde Cm este concentrația molară, n numărul de moli și V volumul în litri)\n\n");

				// PASUL 3: Aplicăm formula
				richRezolvare->AppendText(L"PASUL 3: Aplicăm formula cu valorile date:\n");
				richRezolvare->AppendText("         Cm = " + moli.ToString("F2") + " / " + volum.ToString("F2") + "\n");

				// PASUL 4: Rezultatul
				richRezolvare->AppendText("\nPASUL 4: Rezultatul final:\n");
				richRezolvare->AppendText("         Cm = " + cm.ToString("F2") + " mol/L\n");
			}
			else
			{
				MessageBox::Show("Introduceți valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

	};
}
