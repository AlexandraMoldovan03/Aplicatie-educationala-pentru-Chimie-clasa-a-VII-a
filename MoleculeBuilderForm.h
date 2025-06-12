#pragma once
#include <ctime>
#include <cstdlib>
#include <map>
#include <math.h>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Media;

	ref class AtomInfo {
	public:
		String^ simbol;
		Point pozitieInitiala;

		AtomInfo(String^ s, Point p) {
			simbol = s;
			pozitieInitiala = p;
		}
	};

	public ref class MoleculeBuilderForm : public Form {
	private:
		List<PictureBox^>^ atomIcons;
		Panel^ workspace;
		Label^ labelResult;
		Label^ labelScore;
		Label^ labelTarget;
		int scor = 0;
		String^ moleculaCeruta;
		Random^ rnd = gcnew Random();
		List<Tuple<Control^, Control^>^>^ legaturi;

	public:
		MoleculeBuilderForm() {
			InitializeComponent();
			GenerareMoleculaCeruta();
		}

	private:
		void InitializeComponent() {
			this->Text = L"Construiește Molecula";
			this->Size = Drawing::Size(1000, 700);
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::Honeydew;

			atomIcons = gcnew List<PictureBox^>();
			legaturi = gcnew List<Tuple<Control^, Control^>^>();
			array<String^>^ elements = { "H", "O", "C", "N" };
			array<Color>^ colors = { Color::White, Color::OrangeRed, Color::Gray, Color::SkyBlue };

			for (int i = 0; i < elements->Length; i++) {
				PictureBox^ atom = gcnew PictureBox();
				atom->BackColor = colors[i];
				atom->Tag = gcnew AtomInfo(elements[i], Point(0, 0)); // Inițializare corectă
				atom->Font = gcnew Drawing::Font("Arial", 14, FontStyle::Bold);
				atom->Size = Drawing::Size(50, 50);
				atom->Location = Point(30 + i * 60, 30);
				atom->BorderStyle = BorderStyle::FixedSingle;
				atom->Paint += gcnew PaintEventHandler(this, &MoleculeBuilderForm::atom_Paint);
				atom->MouseDown += gcnew MouseEventHandler(this, &MoleculeBuilderForm::atom_MouseDown);
				this->Controls->Add(atom);
				atomIcons->Add(atom);
			}

			workspace = gcnew Panel();
			workspace->Location = Point(30, 100);
			workspace->Size = Drawing::Size(900, 500);
			workspace->BackColor = Color::LightBlue;
			workspace->AllowDrop = true;
			workspace->DragEnter += gcnew DragEventHandler(this, &MoleculeBuilderForm::workspace_DragEnter);
			workspace->DragDrop += gcnew DragEventHandler(this, &MoleculeBuilderForm::workspace_DragDrop);
			workspace->Paint += gcnew PaintEventHandler(this, &MoleculeBuilderForm::workspace_Paint);
			this->Controls->Add(workspace);

			labelResult = gcnew Label();
			labelResult->Location = Point(30, 620);
			labelResult->AutoSize = true;
			labelResult->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
			this->Controls->Add(labelResult);

			labelScore = gcnew Label();
			labelScore->Location = Point(800, 30);
			labelScore->Text = "Scor: 0";
			labelScore->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			labelScore->AutoSize = true;
			this->Controls->Add(labelScore);

			labelTarget = gcnew Label();
			labelTarget->Location = Point(400, 30);
			labelTarget->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			labelTarget->AutoSize = true;
			this->Controls->Add(labelTarget);
		}

		void GenerareMoleculaCeruta() {
			array<String^>^ optiuni = { "H2O", "O2", "H2", "CO2", "N2" };
			moleculaCeruta = optiuni[rnd->Next(optiuni->Length)];
			labelTarget->Text = "Construiește: " + moleculaCeruta;
		}

		void atom_Paint(Object^ sender, PaintEventArgs^ e) {
			PictureBox^ atom = safe_cast<PictureBox^>(sender);
			AtomInfo^ info = dynamic_cast<AtomInfo^>(atom->Tag);
			if (info != nullptr) {
				TextFormatFlags flags = TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter;
				TextRenderer::DrawText(e->Graphics, info->simbol, atom->Font, atom->ClientRectangle, Color::Black, flags);
			}
		}

		void atom_MouseDown(Object^ sender, MouseEventArgs^ e) {
			PictureBox^ atom = safe_cast<PictureBox^>(sender);
			AtomInfo^ info = dynamic_cast<AtomInfo^>(atom->Tag);
			if (info != nullptr)
				atom->DoDragDrop(info->simbol, DragDropEffects::Copy);
		}

		void workspace_DragEnter(Object^ sender, DragEventArgs^ e) {
			if (e->Data->GetDataPresent(DataFormats::Text))
				e->Effect = DragDropEffects::Copy;
		}

		void workspace_DragDrop(Object^ sender, DragEventArgs^ e) {
			String^ element = (String^)e->Data->GetData(DataFormats::Text);
			Point dropPoint = workspace->PointToClient(Point(e->X, e->Y));

			PictureBox^ newAtom = gcnew PictureBox();
			newAtom->BackColor = Color::LightYellow;
			newAtom->Font = gcnew Drawing::Font("Arial", 14, FontStyle::Bold);
			newAtom->Tag = gcnew AtomInfo(element, dropPoint);
			newAtom->Size = Drawing::Size(50, 50);
			newAtom->Location = dropPoint;
			newAtom->BorderStyle = BorderStyle::FixedSingle;
			newAtom->Paint += gcnew PaintEventHandler(this, &MoleculeBuilderForm::atom_Paint);
			newAtom->MouseDown += gcnew MouseEventHandler(this, &MoleculeBuilderForm::atom_Move_MouseDown);
			newAtom->MouseMove += gcnew MouseEventHandler(this, &MoleculeBuilderForm::atom_Move_MouseMove);
			newAtom->Click += gcnew EventHandler(this, &MoleculeBuilderForm::atom_Click);
			workspace->Controls->Add(newAtom);

			for each(Control ^ c in workspace->Controls) {
				if (c != newAtom && Distance(c->Location, newAtom->Location) < 60)
					legaturi->Add(gcnew Tuple<Control^, Control^>(c, newAtom));
			}

			UpdateMoleculeName();
			workspace->Invalidate();
		}

		void atom_Click(Object^ sender, EventArgs^ e) {
			PictureBox^ atom = safe_cast<PictureBox^>(sender);
			if (MessageBox::Show("Dorești să ștergi acest atom?", "Confirmare", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
				workspace->Controls->Remove(atom);
				delete atom;
				UpdateMoleculeName();
				workspace->Invalidate();
			}
		}

		void atom_Move_MouseDown(Object^ sender, MouseEventArgs^ e) {
			// Nu e necesar nimic aici pentru acest tip de drag logic
		}

		void atom_Move_MouseMove(Object^ sender, MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				PictureBox^ atom = safe_cast<PictureBox^>(sender);
				atom->Left += e->X - 25;
				atom->Top += e->Y - 25;
				workspace->Invalidate();
				UpdateMoleculeName();
			}
		}

		void workspace_Paint(Object^ sender, PaintEventArgs^ e) {
			Pen^ pen = gcnew Pen(Color::Black, 2);
			for each(auto pair in legaturi) {
				Point a = Point(pair->Item1->Left + 25, pair->Item1->Top + 25);
				Point b = Point(pair->Item2->Left + 25, pair->Item2->Top + 25);
				e->Graphics->DrawLine(pen, a, b);
			}
		}

		void UpdateMoleculeName() {
			Dictionary<String^, int>^ counts = gcnew Dictionary<String^, int>();
			for each(Control ^ c in workspace->Controls) {
				AtomInfo^ info = dynamic_cast<AtomInfo^>(c->Tag);
				if (info != nullptr) {
					String^ elem = info->simbol;
					if (!counts->ContainsKey(elem)) counts[elem] = 0;
					counts[elem]++;
				}
			}

			String^ formula = "";
			List<String^>^ keys = gcnew List<String^>(counts->Keys);
			keys->Sort();
			for each(String ^ k in keys) {
				formula += k;
				if (counts[k] > 1) formula += counts[k].ToString();
			}

			String^ result = "Moleculă necunoscută";
			if (formula == "H2O") result = "Apă";
			else if (formula == "O2") result = "Oxigen molecular";
			else if (formula == "H2") result = "Hidrogen molecular";
			else if (formula == "CO2") result = "Dioxid de carbon";
			else if (formula == "N2") result = "Azot molecular";

			labelResult->Text = "Molecula formată: " + result + " (" + formula + ")";

			if (formula == moleculaCeruta) {
				SoundPlayer^ player = gcnew SoundPlayer("success.wav");
				try { player->Play(); }
				catch (...) {}
				scor++;
				labelScore->Text = "Scor: " + scor.ToString();
				GenerareMoleculaCeruta();
			}
		}

		int Distance(Point a, Point b) {
			int dx = a.X - b.X;
			int dy = a.Y - b.Y;
			return (int)Math::Sqrt(dx * dx + dy * dy);
		}
	};
}
