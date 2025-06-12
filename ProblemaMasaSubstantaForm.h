#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ProblemaMasaSubstantaForm : public Form
	{
	public:
		ProblemaMasaSubstantaForm()
		{
			InitializeComponent();
		}

	private:
		Label^ lblTitlu;
		Label^ lblDescriere;
		Label^ lblCm;
		Label^ lblV;
		Label^ lblM;
		TextBox^ txtCm;
		TextBox^ txtV;
		TextBox^ txtM;
		Button^ btnRezolva;
		RichTextBox^ richRezolvare;

		void InitializeComponent(void)
		{
			this->Text = L"Determinarea masei substan?ei";
			this->Size = Drawing::Size(800, 600);
			this->BackColor = Color::White;

			lblTitlu = gcnew Label();
			lblTitlu->Text = L"Calculeaz? masa substan?ei (m)";
			lblTitlu->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
			lblTitlu->Location = Point(30, 20);
			lblTitlu->AutoSize = true;
			this->Controls->Add(lblTitlu);

			lblDescriere = gcnew Label();
			lblDescriere->Text = L"Folosind concentra?ia molar? (Cm), volumul solu?iei (V) ?i masa molar? (M), calculeaz? masa substan?ei dizolvate.";
			lblDescriere->Location = Point(30, 60);
			lblDescriere->Size = Drawing::Size(720, 40);
			this->Controls->Add(lblDescriere);

			lblCm = gcnew Label();
			lblCm->Text = L"Cm (mol/L):";
			lblCm->Location = Point(30, 120);
			lblCm->AutoSize = true;
			this->Controls->Add(lblCm);

			txtCm = gcnew TextBox();
			txtCm->Location = Point(150, 120);
			this->Controls->Add(txtCm);

			lblV = gcnew Label();
			lblV->Text = L"V (L):";
			lblV->Location = Point(30, 160);
			lblV->AutoSize = true;
			this->Controls->Add(lblV);

			txtV = gcnew TextBox();
			txtV->Location = Point(150, 160);
			this->Controls->Add(txtV);

			lblM = gcnew Label();
			lblM->Text = L"M (g/mol):";
			lblM->Location = Point(30, 200);
			lblM->AutoSize = true;
			this->Controls->Add(lblM);

			txtM = gcnew TextBox();
			txtM->Location = Point(150, 200);
			this->Controls->Add(txtM);

			btnRezolva = gcnew Button();
			btnRezolva->Text = L"Rezolv?";
			btnRezolva->Location = Point(30, 250);
			btnRezolva->Click += gcnew EventHandler(this, &ProblemaMasaSubstantaForm::btnRezolva_Click);
			this->Controls->Add(btnRezolva);

			richRezolvare = gcnew RichTextBox();
			richRezolvare->Location = Point(30, 300);
			richRezolvare->Size = Drawing::Size(720, 220);
			richRezolvare->ReadOnly = true;
			this->Controls->Add(richRezolvare);
		}

		void btnRezolva_Click(Object^ sender, EventArgs^ e)
		{
			double Cm, V, M;
			if (Double::TryParse(txtCm->Text, Cm) &&
				Double::TryParse(txtV->Text, V) &&
				Double::TryParse(txtM->Text, M))
			{
				double masa = Cm * V * M;
				richRezolvare->Clear();
				richRezolvare->AppendText(L"Formul?: m = Cm × V × M\n");
				richRezolvare->AppendText("m = " + Cm.ToString("F2") + " × " + V.ToString("F2") + " × " + M.ToString("F2") + "\n");
				richRezolvare->AppendText("m = " + masa.ToString("F2") + " g\n");
			}
			else
			{
				MessageBox::Show("Introduce?i valori numerice valide.", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
