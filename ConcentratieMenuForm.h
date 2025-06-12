#pragma once
#include "ProblemaProcentualaForm.h"
#include "ProblemaConcentratieMolaraForm.h"
#include "ProblemaMasaSubstanteiForm.h"
#include "ProblemaMasaSolutieiForm.h"
#include "ProblemaVolumForm1.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ConcentratieMenuForm : public Form {
	public:
		ConcentratieMenuForm(void) {
			InitializeComponent();
		}

	private:
		Label^ titlu;
		array<Button^>^ butoane;

		void InitializeComponent(void) {
			this->Text = L"🌈 Concentrații – Meniu Probleme";
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(240, 250, 255); // albastru pastelat deschis
			this->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);

			// Titlu
			titlu = gcnew Label();
			titlu->Text = L"📘 Alege tipul de problemă de chimie:";
			titlu->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			titlu->ForeColor = Color::DarkSlateBlue;
			titlu->AutoSize = true;
			this->Controls->Add(titlu);

			// Butoane cu emoji
			butoane = gcnew array<Button^>(5);

			butoane[0] = CreateButton(L"💧 Concentrație Procentuală", Color::LightSkyBlue, gcnew EventHandler(this, &ConcentratieMenuForm::btnProcentuala_Click));
			butoane[1] = CreateButton(L"⚗️ Concentrație Molară", Color::LightGreen, gcnew EventHandler(this, &ConcentratieMenuForm::btnMolara_Click));
			butoane[2] = CreateButton(L"⚖️ Determină masa substanței", Color::LightCoral, gcnew EventHandler(this, &ConcentratieMenuForm::btnMasaSubstantei_Click));
			butoane[3] = CreateButton(L"🧪 Determină masa soluției", Color::LightGoldenrodYellow, gcnew EventHandler(this, &ConcentratieMenuForm::btnMasaSolutie_Click));
			butoane[4] = CreateButton(L"📦 Determină volumul soluției", Color::Thistle, gcnew EventHandler(this, &ConcentratieMenuForm::btnVolum_Click));

			this->Load += gcnew EventHandler(this, &ConcentratieMenuForm::OnLoad);
		}

		Button^ CreateButton(String^ text, Color bgColor, EventHandler^ handler) {
			Button^ btn = gcnew Button();
			btn->Text = text;
			btn->Size = Drawing::Size(450, 60);
			btn->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
			btn->BackColor = bgColor;
			btn->ForeColor = Color::DarkSlateGray;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->Click += handler;
			this->Controls->Add(btn);
			return btn;
		}

		void OnLoad(Object^ sender, EventArgs^ e) {
			// Centrare titlu
			titlu->Location = Point(
				(this->ClientSize.Width - titlu->Width) / 2,
				this->ClientSize.Height / 8
			);

			// Centrare butoane
			int totalHeight = butoane->Length * (60 + 20) - 20;
			int startY = (this->ClientSize.Height - totalHeight) / 2;

			for (int i = 0; i < butoane->Length; i++) {
				butoane[i]->Location = Point(
					(this->ClientSize.Width - butoane[i]->Width) / 2,
					startY + i * (60 + 20)
				);
			}
		}

		// Handlers
		void btnProcentuala_Click(Object^ sender, EventArgs^ e) {
			ProblemaProcentualaForm^ f = gcnew ProblemaProcentualaForm();
			this->Hide(); f->ShowDialog(); this->Show();
		}

		void btnMolara_Click(Object^ sender, EventArgs^ e) {
			ProblemaConcentratieMolaraForm^ f = gcnew ProblemaConcentratieMolaraForm();
			this->Hide(); f->ShowDialog(); this->Show();
		}

		void btnMasaSubstantei_Click(Object^ sender, EventArgs^ e) {
			ProblemaMasaSubstanteiForm^ f = gcnew ProblemaMasaSubstanteiForm();
			this->Hide(); f->ShowDialog(); this->Show();
		}

		void btnMasaSolutie_Click(Object^ sender, EventArgs^ e) {
			ProblemaMasaSolutieiForm^ f = gcnew ProblemaMasaSolutieiForm();
			this->Hide(); f->ShowDialog(); this->Show();
		}

		void btnVolum_Click(Object^ sender, EventArgs^ e) {
			ProblemaVolumForm1^ f = gcnew ProblemaVolumForm1();
			this->Hide(); f->ShowDialog(); this->Show();
		}
	};
}
