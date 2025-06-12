#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaProcentualaForm : public Form
	{
	public:
		ProblemaProcentualaForm()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblCerință;
		Label^ lblMasaSolutiei;
		Label^ lblMasaSubstantei;
		TextBox^ txtMasaSolutiei;
		TextBox^ txtMasaSubstantei;
		Button^ btnRezolva;
		RichTextBox^ richRezolvare;

		void InitializeComponent(void)
		{
			this->Text = L"Problemă - Concentrație Procentuală";
			this->Size = Drawing::Size(900, 600);
			this->BackColor = Color::White;
			this->WindowState = FormWindowState::Maximized;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Exercițiu: Calculul concentrației procentuale";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->AutoSize = true;
			this->Controls->Add(lblTitlu);

			lblCerință = gcnew Label();
			lblCerință->Text = L"Se dizolvă o anumită masă de substanță solidă într-o soluție apoasă.\n"
				L"Introduceți valorile pentru a calcula concentrația procentuală a soluției.";
			lblCerință->Font = gcnew Drawing::Font("Segoe UI", 11);
			lblCerință->Location = Point(30, 70);
			lblCerință->Size = Drawing::Size(800, 60);
			this->Controls->Add(lblCerință);

			lblMasaSolutiei = gcnew Label();
			lblMasaSolutiei->Text = L"Masa soluției (g):";
			lblMasaSolutiei->Location = Point(30, 150);
			lblMasaSolutiei->AutoSize = true;
			lblMasaSolutiei->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblMasaSolutiei);

			txtMasaSolutiei = gcnew TextBox();
			txtMasaSolutiei->Location = Point(250, 145);
			txtMasaSolutiei->Width = 100;
			this->Controls->Add(txtMasaSolutiei);

			lblMasaSubstantei = gcnew Label();
			lblMasaSubstantei->Text = L"Masa substanței dizolvate (g):";
			lblMasaSubstantei->Location = Point(30, 190);
			lblMasaSubstantei->AutoSize = true;
			lblMasaSubstantei->Font = gcnew Drawing::Font("Segoe UI", 10);
			this->Controls->Add(lblMasaSubstantei);

			txtMasaSubstantei = gcnew TextBox();
			txtMasaSubstantei->Location = Point(250, 185);
			txtMasaSubstantei->Width = 100;
			this->Controls->Add(txtMasaSubstantei);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolvă";
			btnRezolva->Location = Point(30, 240);
			btnRezolva->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			btnRezolva->BackColor = Color::LightBlue;
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaProcentualaForm::btnRezolva_Click);
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
			double masaSolutie, masaSubstanta;
			if (Double::TryParse(txtMasaSolutiei->Text, masaSolutie) &&
				Double::TryParse(txtMasaSubstantei->Text, masaSubstanta) && masaSolutie > 0)
			{
				double concentratie = (masaSubstanta / masaSolutie) * 100.0;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"Formulă folosită:\n");
				richRezolvare->AppendText(L"c% = (masa substanței / masa soluției) × 100\n\n");
				richRezolvare->AppendText("Înlocuire:\n");
				richRezolvare->AppendText("c% = (" + masaSubstanta + " / " + masaSolutie + ") × 100\n\n");
				richRezolvare->AppendText("Rezultat final:\n");
				richRezolvare->AppendText("c% = " + concentratie.ToString("F2") + " %\n");
			}
			else
			{
				MessageBox::Show("Introduceți valori numerice valide și diferite de zero.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
