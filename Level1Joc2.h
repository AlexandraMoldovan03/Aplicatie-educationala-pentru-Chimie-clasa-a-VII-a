#pragma once

namespace ChimiaGame {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Level1Joc2 : public Form
	{
	public:
		Level1Joc2(void)
		{
			InitializeComponent();
		}

	private:
		PictureBox^ eprubeta;
		PictureBox^ becher;
		PictureBox^ erlenmeyer;
		PictureBox^ palnie;
		PictureBox^ zonaReactiv;
		PictureBox^ zonaSeparare;
		PictureBox^ zonaSuport;
		Label^ feedback;
		int scor = 0;

		void InitializeComponent(void)
		{
			this->Text = L"Plasează ustensilele corect!";
			this->WindowState = FormWindowState::Maximized;
			this->BackColor = Color::FromArgb(235, 245, 255); // pastel albastru
			this->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Regular);

			//  Feedback vizual jos 
			feedback = gcnew Label();
			feedback->Text = L"Plasează obiectele în zona potrivită.";
			feedback->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Italic);
			feedback->ForeColor = Color::White;
			feedback->BackColor = Color::MediumSlateBlue;
			feedback->TextAlign = ContentAlignment::MiddleCenter;
			feedback->Size = Drawing::Size(900, 50);
			feedback->Location = Point((ClientSize.Width - feedback->Width) / 2, ClientSize.Height - 80);
			feedback->Anchor = AnchorStyles::Bottom;
			feedback->BorderStyle = BorderStyle::None;
			this->Controls->Add(feedback);

			// Zone categorii
			int spacingX = 200;
			int topY = 100;
			zonaReactiv = CreateZona(Color::LightPink, Point(100, topY), L"Vase de reacție");
			zonaSeparare = CreateZona(Color::LightCyan, Point(100 + spacingX + 180, topY), L"Instrumente de separare");
			zonaSuport = CreateZona(Color::MistyRose, Point(100 + 2 * (spacingX + 180), topY), L"Dispozitive de susținere");

			//  Obiecte în linie orizontală 
			int bottomY = 400;
			int leftStart = 150;
			int objSpacing = 150;

			eprubeta = CreateObiect("eprubeta.png", Point(leftStart + 0 * objSpacing, bottomY), L"Vase de reacție", L"Eprubetă");
			becher = CreateObiect("paharBerzelius.png", Point(leftStart + 1 * objSpacing, bottomY), L"Vase de reacție", L"Pahar Berzelius");
			erlenmeyer = CreateObiect("paharErlenmeyer.jpeg", Point(leftStart + 2 * objSpacing, bottomY), L"Vase de reacție", L"Erlenmeyer");
			palnie = CreateObiect("palnieDeFiltrare.jpeg", Point(leftStart + 3 * objSpacing, bottomY), L"Instrumente de separare", L"Pâlnie de filtrare");
		}



		PictureBox^ CreateZona(Color culoare, Point loc, String^ categorie)
		{
			PictureBox^ zona = gcnew PictureBox();
			zona->BackColor = culoare;
			zona->Location = loc;
			zona->Size = Drawing::Size(180, 180);
			zona->Tag = categorie;
			zona->AllowDrop = true;
			zona->BorderStyle = BorderStyle::Fixed3D;

			// Titlul categoriei (centrare)
			Label^ lbl = gcnew Label();
			lbl->Text = categorie;
			lbl->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
			lbl->AutoSize = true;
			lbl->Location = Point(loc.X + (zona->Width - 200) / 2, loc.Y - 40);
			lbl->Size = Drawing::Size(200, 30);
			lbl->ForeColor = Color::DarkSlateGray;
			lbl->TextAlign = ContentAlignment::MiddleCenter;
			this->Controls->Add(lbl);

			this->Controls->Add(zona);
			return zona;
		}



		// Creeaza un obiect drag-and-drop
		PictureBox^ CreateObiect(String^ imagine, Point loc, String^ categorieCorecta, String^ nume)
		{
			PictureBox^ obj = gcnew PictureBox();
			obj->Image = Image::FromFile(imagine);
			obj->Size = Drawing::Size(100, 100);
			obj->Location = loc;
			obj->SizeMode = PictureBoxSizeMode::Zoom;
			obj->Tag = categorieCorecta + "|" + nume;

			obj->MouseDown += gcnew MouseEventHandler(this, &Level1Joc2::OnMouseDown);
			obj->MouseMove += gcnew MouseEventHandler(this, &Level1Joc2::OnMouseMove);
			obj->MouseUp += gcnew MouseEventHandler(this, &Level1Joc2::OnMouseUp);
			this->Controls->Add(obj);
			return obj;
		}


		// Drag logic
		bool dragging = false;
		Point offset;
		PictureBox^ current;

		void OnMouseDown(Object^ sender, MouseEventArgs^ e) {
			current = safe_cast<PictureBox^>(sender);
			offset = e->Location;
			dragging = true;
			current->BringToFront();
		}

		void OnMouseMove(Object^ sender, MouseEventArgs^ e) {
			if (dragging && current != nullptr) {
				current->Left = e->X + current->Left - offset.X;
				current->Top = e->Y + current->Top - offset.Y;
			}
		}

		void OnMouseUp(Object^ sender, MouseEventArgs^ e) {
			dragging = false;
			CheckPozitie(safe_cast<PictureBox^>(sender));
		}

		void CheckPozitie(PictureBox^ obiect)
		{
			String^ tag = safe_cast<String^>(obiect->Tag);
			array<String^>^ info = tag->Split('|');
			String^ categorieCorecta = info[0]->Trim();
			String^ nume = info[1]->Trim();

			for each(Control ^ ctrl in this->Controls)
			{
				PictureBox^ zona = dynamic_cast<PictureBox^>(ctrl);
				if (zona != nullptr && zona->AllowDrop)
				{
					if (zona->Bounds.IntersectsWith(obiect->Bounds))
					{
						String^ zonaCategorie = safe_cast<String^>(zona->Tag)->Trim();
						if (zonaCategorie == categorieCorecta)
						{
							feedback->Text = nume + " a fost plasat corect în categoria \"" + zonaCategorie + "\"!";
							scor++;
							return;
						}
						else
						{
							feedback->Text = nume + " a fost pus greșit. Categoria corectă era: " + categorieCorecta;
							return;
						}
					}
				}
			}
			feedback->Text = "Obiectul nu este într-o zonă validă.";
		}

	};
}
