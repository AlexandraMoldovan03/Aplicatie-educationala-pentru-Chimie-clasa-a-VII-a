#pragma once
#pragma execution_character_set("utf-8")
namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	ref class CardPair
	{
	public:
		String^ text;
		String^ group;
		CardPair(String^ t, String^ g) : text(t), group(g) {}
	};

	public ref class Level2Joc : public System::Windows::Forms::Form
	{
	public:
		Level2Joc(void)
		{
			InitializeComponent();
			StartGame();
		}

	private:
		List<Button^>^ cards;
		List<CardPair^>^ pairs;
		Button^ firstCard = nullptr;
		Button^ secondCard = nullptr;
		Timer^ flipBackTimer;
		Random^ rand;
		Label^ titlu;
		Label^ instructiuni;


	private:
		void InitializeComponent() {
			titlu = gcnew Label();
			titlu->Text = L"🎮 Joc de potrivire: Materie. Corp. Substanță";
			titlu->Font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
			titlu->ForeColor = Color::DarkSlateBlue;
			titlu->BackColor = Color::Lavender;
			titlu->Height = 80;
			titlu->Dock = DockStyle::Top;
			titlu->TextAlign = ContentAlignment::MiddleCenter;
			titlu->AutoSize = false;
			this->Controls->Add(titlu);


			instructiuni = gcnew Label();
			instructiuni->Text =
				L"📘 Instrucțiuni:\n"
				L"- Apasă pe câte două carduri pentru a le întoarce.\n"
				L"- Găsește perechile formate dintr-un obiect (corp) și starea de agregare (solid, lichid, gazos).\n"
				L"- Exemple: Gheață - solid, Apă - lichid, Heliu - gazos.\n"
				L"- La potrivire completă apare un mesaj de felicitare!";
			instructiuni->Font = gcnew Drawing::Font("Segoe UI", 11);
			instructiuni->ForeColor = Color::DarkSlateGray;
			instructiuni->BackColor = Color::LightCyan;
			instructiuni->Padding = System::Windows::Forms::Padding(10);
			instructiuni->Size = Drawing::Size(1000, 120);
			instructiuni->Location = Point(20, titlu->Bottom + 10); // AICI E IMPORTANT!
			this->Controls->Add(instructiuni);


			flipBackTimer = gcnew Timer();
			flipBackTimer->Interval = 1000;
			flipBackTimer->Tick += gcnew EventHandler(this, &Level2Joc::FlipBack);

			rand = gcnew Random();
		}

		void StartGame()
		{
			pairs = gcnew List<CardPair^>();
			pairs->Add(gcnew CardPair("Gheata", "solid"));
			pairs->Add(gcnew CardPair("Apa", "lichid"));
			pairs->Add(gcnew CardPair("Heliu", "gazos"));
			pairs->Add(gcnew CardPair("Sare", "solid"));
			pairs->Add(gcnew CardPair("Mercur", "lichid"));
			pairs->Add(gcnew CardPair("Oxigen", "gazos"));

			List<String^>^ content = gcnew List<String^>();
			for each(CardPair ^ p in pairs) {
				content->Add(p->text);
				content->Add(p->group);
			}

			// Amestecare
			for (int i = 0; i < content->Count; i++) {
				int j = rand->Next(i, content->Count);
				String^ tmp = content[i];
				content[i] = content[j];
				content[j] = tmp;
			}

			// Creare carduri
			cards = gcnew List<Button^>();
			for (int i = 0; i < content->Count; i++)
			{
				Button^ card = gcnew Button();
				card->Size = Drawing::Size(120, 80);
				card->BackColor = Color::White;
				card->ForeColor = Color::Black;
				card->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
				card->Text = "?";
				card->Tag = content[i];
				card->Location = Point(80 + (i % 4) * 160, 250 + (i / 4) * 100);
				card->Click += gcnew EventHandler(this, &Level2Joc::OnCardClick);
				this->Controls->Add(card);
				cards->Add(card);
			}


			Button^ btnRestart = gcnew Button();
			btnRestart->Text = L"Repornește jocul";
			btnRestart->Location = Point(700, 570);
			btnRestart->Size = Drawing::Size(160, 40);
			btnRestart->Click += gcnew EventHandler(this, &Level2Joc::RestartGame);
			this->Controls->Add(btnRestart);

		}

		void OnCardClick(Object^ sender, EventArgs^ e)
		{
			Button^ clicked = safe_cast<Button^>(sender);
			if (clicked->Text != "?") return;
			clicked->Text = safe_cast<String^>(clicked->Tag);

			if (firstCard == nullptr) {
				firstCard = clicked;
			}
			else if (secondCard == nullptr && clicked != firstCard) {
				secondCard = clicked;
				CheckMatch();
			}
		}

		void CheckMatch()
		{
			String^ a = safe_cast<String^>(firstCard->Tag);
			String^ b = safe_cast<String^>(secondCard->Tag);

			if (IsPair(a, b)) {
				firstCard = nullptr;
				secondCard = nullptr;
				CheckWin();
			}
			else {
				flipBackTimer->Start();
			}
		}

		bool IsPair(String^ a, String^ b)
		{
			for each(CardPair ^ p in pairs) {
				if ((p->text == a && p->group == b) || (p->text == b && p->group == a)) {
					return true;
				}
			}
			return false;
		}

		void FlipBack(Object^ sender, EventArgs^ e)
		{
			flipBackTimer->Stop();
			firstCard->Text = "?";
			secondCard->Text = "?";
			firstCard = nullptr;
			secondCard = nullptr;
		}

		void CheckWin()
		{
			for each(Button ^ card in cards) {
				if (card->Text == "?") return;
			}
			MessageBox::Show("Felicitări! Ai potrivit toate perechile!", "Bravo");
		}

		void RestartGame(Object^ sender, EventArgs^ e)
		{
			for each(Button ^ b in cards)
				this->Controls->Remove(b);
			cards->Clear();
			StartGame();
		}

	};
}
