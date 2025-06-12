#pragma once

#include "PeriodicTableForm.h"

namespace LicentaChimie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class DialogForm : public System::Windows::Forms::Form
	{
	public:
		DialogForm(String^ elementSymbol)
		{
			InitializeComponent();
			LoadElementDetails(elementSymbol);
		}

	protected:
		~DialogForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ elementDetailsLabel;

		   // Afișează detaliile elementului
		   void LoadElementDetails(String^ elementSymbol)
		   {
			   String^ details = "";

			   // Exemplu de informații - înlocuiește cu date reale
			   if (elementSymbol == "H") details = "Hidrogen\nNr. Atomic: 1\nMasa atomică: 1.008";
			   else if (elementSymbol == "He") details = "Heliu\nNr. Atomic: 2\nMasa atomică: 4.0026";
			   else if (elementSymbol == "Li") details = "Litiu\nNr. Atomic: 3\nMasa atomică: 6.94";
			   // Adaugă detalii pentru celelalte elemente...

			   this->elementDetailsLabel->Text = details;
		   }

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->elementDetailsLabel = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // elementDetailsLabel
			   // 
			   this->elementDetailsLabel->AutoSize = true;
			   this->elementDetailsLabel->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 12));
			   this->elementDetailsLabel->Location = System::Drawing::Point(10, 10);
			   this->elementDetailsLabel->Name = L"elementDetailsLabel";
			   this->elementDetailsLabel->Size = System::Drawing::Size(200, 100);
			   // 
			   // DialogForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->ClientSize = System::Drawing::Size(400, 200);
			   this->Controls->Add(this->elementDetailsLabel);
			   this->Name = L"DialogForm";
			   this->Text = L"Detalii Element";
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion
	};
}
