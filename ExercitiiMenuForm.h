#pragma once
#include "MoleculeBuilderForm.h"
#include "JocForm.h"
#include "ExercitiuConcentratie1Form.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ExercitiiMenuForm : public System::Windows::Forms::Form
	{
	private:
		String^ username;
		Label^ labelTitlu;
		Button^ btnMolecule;
		Button^ btnConcentratie;

	public:
		ExercitiiMenuForm(String^ user) {
			username = user;
			InitializeComponent();
		}

	protected:
		~ExercitiiMenuForm() {
			if (components)
				delete components;
		}

	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->Text = L"🧪 Exerciții și Jocuri";
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(240, 250, 255); // pastel albastru foarte deschis

			this->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);

			// === Titlu ===
			labelTitlu = gcnew Label();
			labelTitlu->Text = L"📘 Alege un exercițiu sau un joc:";
			labelTitlu->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			labelTitlu->ForeColor = Color::DarkSlateBlue;
			labelTitlu->AutoSize = true;
			this->Controls->Add(labelTitlu);

			// === Buton Molecule ===
			btnMolecule = CreateButton(L"🔬 Jocul Moleculelor", Color::LightGreen, gcnew EventHandler(this, &ExercitiiMenuForm::btnMolecule_Click));

			// === Buton Concentrație ===
			btnConcentratie = CreateButton(L"💧 Exercițiu Concentrație", Color::LightSkyBlue, gcnew EventHandler(this, &ExercitiiMenuForm::btnConcentratie_Click));

			// === OnLoad pentru aranjare ===
			this->Load += gcnew EventHandler(this, &ExercitiiMenuForm::OnLoad);
		}

		Button^ CreateButton(String^ text, Color color, EventHandler^ handler) {
			Button^ btn = gcnew Button();
			btn->Text = text;
			btn->Size = Drawing::Size(400, 70);
			btn->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
			btn->BackColor = color;
			btn->ForeColor = Color::DarkSlateGray;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->Click += handler;
			this->Controls->Add(btn);
			return btn;
		}

		void OnLoad(Object^ sender, EventArgs^ e) {
			// Centrare titlu
			labelTitlu->Location = Point(
				(this->ClientSize.Width - labelTitlu->Width) / 2,
				this->ClientSize.Height / 6
			);

			// Spațiere butoane
			int spacing = 30;
			int totalHeight = 2 * (btnMolecule->Height + spacing) - spacing;
			int startY = (this->ClientSize.Height - totalHeight) / 2;

			btnMolecule->Location = Point(
				(this->ClientSize.Width - btnMolecule->Width) / 2,
				startY
			);

			btnConcentratie->Location = Point(
				(this->ClientSize.Width - btnConcentratie->Width) / 2,
				startY + btnMolecule->Height + spacing
			);
		}

		void btnMolecule_Click(Object^ sender, EventArgs^ e) {
			MoleculeBuilderForm^ moleculeBuilderForm = gcnew MoleculeBuilderForm();
			this->Hide(); moleculeBuilderForm->ShowDialog(); this->Show();
		}

		void btnConcentratie_Click(Object^ sender, EventArgs^ e) {
			ExercitiuConcentratie1Form^ form = gcnew ExercitiuConcentratie1Form();
			this->Hide(); form->ShowDialog(); this->Show();
		}
	};
}
