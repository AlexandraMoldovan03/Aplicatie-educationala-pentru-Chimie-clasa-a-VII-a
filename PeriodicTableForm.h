#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace LicentaChimie {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class PeriodicTableForm : public Form {
	public:
		PeriodicTableForm() {
			InitializeComponent();
			DefineElementColors();
			LoadElementData();
			InitializePeriodicTable();
		}

	protected:
		~PeriodicTableForm() {
			if (components) delete components;
		}

	private:
		TableLayoutPanel^ tableLayoutPanel;
		Dictionary<String^, String^>^ elementData;
		Dictionary<String^, Color>^ elementColors;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void) {
			this->SuspendLayout();
			this->ClientSize = Drawing::Size(1200, 800);
			this->Text = L"Tabelul Periodic";
			this->WindowState = FormWindowState::Maximized;
			this->Load += gcnew EventHandler(this, &PeriodicTableForm::PeriodicTableForm_Load);

			// Etichetă titlu
			Label^ titluLabel = gcnew Label();
			titluLabel->Text = L"Tabelul Periodic al Elementelor";
			titluLabel->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			titluLabel->ForeColor = Color::MidnightBlue;
			titluLabel->TextAlign = ContentAlignment::MiddleCenter;
			titluLabel->Dock = DockStyle::Top;
			titluLabel->Padding = System::Windows::Forms::Padding(0, 30, 0, 20);
			titluLabel->AutoSize = true;

			// Panel principal care conține titlul + tabelul
			Panel^ mainPanel = gcnew Panel();
			mainPanel->Dock = DockStyle::Fill;
			mainPanel->AutoScroll = true;
			mainPanel->BackColor = Color::White;

	
			this->tableLayoutPanel = gcnew TableLayoutPanel();
			this->tableLayoutPanel->ColumnCount = 18;
			this->tableLayoutPanel->RowCount = 10;
			this->tableLayoutPanel->AutoSize = true;
			this->tableLayoutPanel->CellBorderStyle = TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel->Margin = System::Windows::Forms::Padding(20);
			this->tableLayoutPanel->Padding = System::Windows::Forms::Padding(10);
			this->tableLayoutPanel->Dock = DockStyle::Top;

			mainPanel->Controls->Add(tableLayoutPanel);
			mainPanel->Controls->Add(titluLabel);
			this->Controls->Add(mainPanel);

			this->ResumeLayout(false);
		}

		void LoadElementData() {
			elementData = gcnew Dictionary<String^, String^>();
			try {
				String^ filePath = Path::Combine(Application::StartupPath, "elemente.txt");
				if (!File::Exists(filePath)) {
					MessageBox::Show("Fișierul elemente.txt nu a fost găsit!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
				StreamReader^ sr = gcnew StreamReader(filePath);
				String^ line;
				while ((line = sr->ReadLine()) != nullptr) {
					array<String^>^ parts = line->Split('|');
					if (parts->Length >= 5) {
						String^ symbol = parts[0]->Trim();
						String^ name = parts[1]->Trim();
						String^ atomicNumber = parts[2]->Trim();
						String^ atomicMass = parts[3]->Trim();
						String^ description = parts[4]->Trim();
						String^ info = "Nume: " + name + "\nNumăr atomic: " + atomicNumber +
							"\nMasa atomică: " + atomicMass + "\nDescriere: " + description;
						elementData[symbol] = info;
					}
				}
				sr->Close();
			}
			catch (Exception^ e) {
				MessageBox::Show("Eroare la citirea fișierului elemente.txt\n" + e->Message,
					"Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void DefineElementColors() {
			elementColors = gcnew Dictionary<String^, Color>();

			array<String^>^ alcaline = { "Li", "Na", "K", "Rb", "Cs", "Fr" };
			for each(String ^ elem in alcaline) elementColors[elem] = Color::Pink;

			array<String^>^ alcalino = { "Be", "Mg", "Ca", "Sr", "Ba", "Ra" };
			for each(String ^ elem in alcalino) elementColors[elem] = Color::Orange;

			array<String^>^ tranzitie = { "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Y",
				"Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Rf",
				"Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn" };
			for each(String ^ elem in tranzitie) elementColors[elem] = Color::LightGray;

			array<String^>^ metaloizi = { "B", "Si", "Ge", "As", "Sb", "Te", "Po" };
			for each(String ^ elem in metaloizi) elementColors[elem] = Color::LightGreen;

			array<String^>^ halogeni = { "F", "Cl", "Br", "I", "At", "Ts" };
			for each(String ^ elem in halogeni) elementColors[elem] = Color::Plum;

			array<String^>^ gaze = { "He", "Ne", "Ar", "Kr", "Xe", "Rn", "Og" };
			for each(String ^ elem in gaze) elementColors[elem] = Color::LightBlue;

			array<String^>^ lantanide = { "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu" };
			for each(String ^ elem in lantanide) elementColors[elem] = Color::Khaki;

			array<String^>^ actinide = { "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr" };
			for each(String ^ elem in actinide) elementColors[elem] = Color::Gold;
		}

		void InitializePeriodicTable() {
			array<String^, 2>^ elements = gcnew array<String^, 2>(10, 18) {
				{ "H", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "He" },
				{ "Li", "Be", "", "", "", "", "", "", "", "", "", "", "B", "C", "N", "O", "F", "Ne" },
				{ "Na", "Mg", "", "", "", "", "", "", "", "", "", "", "Al", "Si", "P", "S", "Cl", "Ar" },
				{ "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr" },
				{ "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe" },
				{ "Cs", "Ba", "La", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn" },
				{ "Fr", "Ra", "Ac", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og" },
				{ "", "", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "", "" },
				{ "", "", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "", "" }
			};

			for (int row = 0; row < 10; row++) {
				for (int col = 0; col < 18; col++) {
					String^ element = elements[row, col];
					if (!String::IsNullOrEmpty(element)) {
						Button^ btn = gcnew Button();
						btn->Text = element;
						btn->Size = Drawing::Size(50, 50);
						btn->BackColor = elementColors->ContainsKey(element) ? elementColors[element] : Color::LightGray;
						btn->Click += gcnew EventHandler(this, &PeriodicTableForm::OnElementClick);
						this->tableLayoutPanel->Controls->Add(btn, col, row);
					}
					else {
						Label^ lbl = gcnew Label();
						lbl->Size = Drawing::Size(50, 50);
						this->tableLayoutPanel->Controls->Add(lbl, col, row);
					}
				}
			}
		}

		void OnElementClick(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			String^ symbol = btn->Text;
			if (elementData->ContainsKey(symbol)) {
				MessageBox::Show(elementData[symbol], "Informații despre " + symbol,
					MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Nu există informații pentru elementul: " + symbol,
					"Eroare", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}

	private: System::Void PeriodicTableForm_Load(System::Object^ sender, System::EventArgs^ e) {}
	};
}
