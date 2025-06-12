#pragma once

namespace LicentaChimie {

	using namespace System;
	using namespace System::Windows::Forms;

	public ref class JocForm : public Form
	{
	public:
		JocForm()
		{
			InitializeComponent();
			InitQuestions(); // trebuie apelat aici pentru ini?ializare
			LoadQuestion();
		}

	private:
		Label^ questionLabel;
		Button^ btnA;
		Button^ btnB;
		Button^ btnC;
		Label^ feedbackLabel;
		int currentQuestion = 0;
		int score = 0;

		array<String^>^ questions;
		array<array<String^>^>^ answers;
		array<int>^ correctIndex;

		void InitQuestions()
		{
			questions = gcnew array<String^> {
				"Care este simbolul chimic al oxigenului?",
					"Ce tip de legtur? este în molecula de ap??",
					"Câ?i protoni are un atom de carbon?"
			};

			answers = gcnew array<array<String^>^>(3);
			answers[0] = gcnew array<String^>{"O", "Ox", "Og"};
			answers[1] = gcnew array<String^>{"Covalent?", "Ionic?", "Metalic?"};
			answers[2] = gcnew array<String^>{"6", "8", "12"};

			correctIndex = gcnew array<int>{ 0, 0, 1 }; // r?spunsurile corecte (0 = primul, 1 = al doilea, etc.)
		}

		void InitializeComponent()
		{
			this->Text = "Moli te întreab?!";
			this->Width = 500;
			this->Height = 300;

			questionLabel = gcnew Label();
			questionLabel->Top = 30;
			questionLabel->Left = 30;
			questionLabel->Width = 400;
			this->Controls->Add(questionLabel);

			btnA = gcnew Button();
			btnA->Top = 80;
			btnA->Left = 30;
			btnA->Click += gcnew EventHandler(this, &JocForm::Answer_Click);
			this->Controls->Add(btnA);

			btnB = gcnew Button();
			btnB->Top = 120;
			btnB->Left = 30;
			btnB->Click += gcnew EventHandler(this, &JocForm::Answer_Click);
			this->Controls->Add(btnB);

			btnC = gcnew Button();
			btnC->Top = 160;
			btnC->Left = 30;
			btnC->Click += gcnew EventHandler(this, &JocForm::Answer_Click);
			this->Controls->Add(btnC);

			feedbackLabel = gcnew Label();
			feedbackLabel->Top = 210;
			feedbackLabel->Left = 30;
			feedbackLabel->Width = 400;
			this->Controls->Add(feedbackLabel);
		}

		void LoadQuestion()
		{
			if (currentQuestion < questions->Length)
			{
				questionLabel->Text = questions[currentQuestion];
				btnA->Text = "A. " + answers[currentQuestion][0];
				btnB->Text = "B. " + answers[currentQuestion][1];
				btnC->Text = "C. " + answers[currentQuestion][2];
				feedbackLabel->Text = "";
			}
			else
			{
				questionLabel->Text = "Bravo! Ai terminat quiz-ul!";
				btnA->Visible = false;
				btnB->Visible = false;
				btnC->Visible = false;
				feedbackLabel->Text = "Scorul t?u final: " + score;
			}
		}

		void Answer_Click(Object^ sender, EventArgs^ e)
		{
			Button^ clicked = safe_cast<Button^>(sender);
			int answerIndex = clicked == btnA ? 0 : clicked == btnB ? 1 : 2;

			if (answerIndex == correctIndex[currentQuestion])
			{
				feedbackLabel->Text = "? Corect! Bravo, spune Moli!";
				score++;
			}
			else
			{
				feedbackLabel->Text = "? Hmm... Moli zice c? mai trebuie exersat!";
			}

			currentQuestion++;
			System::Threading::Tasks::Task::Delay(1000)->ContinueWith(gcnew System::Action<System::Threading::Tasks::Task^>(
				this, &JocForm::NextQuestion), System::Threading::Tasks::TaskScheduler::FromCurrentSynchronizationContext());
		}

		void NextQuestion(System::Threading::Tasks::Task^)
		{
			LoadQuestion();
		}
	};
}
