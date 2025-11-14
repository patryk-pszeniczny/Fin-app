#pragma once
#include<string>
#include "FinLogic.h"

namespace Szablon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//static HangmanLogic gra; 

	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
		void setFinLogic(FinLogic* finlogic);
		FinLogic* getFinLogic();
	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ start_;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ password_input;
	private: System::Windows::Forms::TextBox^ email_input;
	private: System::Windows::Forms::ToolStripMenuItem^ dataBaseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ usersToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ userLogsToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
	private: System::Windows::Forms::Button^ button1;



	private:
		FinLogic* finlogic;

		void start_Click(System::Object^ sender, System::EventArgs^ e);
		void button1_Click(System::Object^ sender, System::EventArgs^ e);
		void clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		bool emailValidator(const std::string& email);
		bool passwordValidator(const std::string& password);
		void usersToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void userLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->start_ = (gcnew System::Windows::Forms::Button());
			this->email_input = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dataBaseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->usersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->userLogsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->password_input = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// start_
			// 
			this->start_->BackColor = System::Drawing::Color::Lime;
			this->start_->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->start_->FlatAppearance->BorderSize = 0;
			this->start_->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->start_->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->start_->Location = System::Drawing::Point(22, 317);
			this->start_->Name = L"start_";
			this->start_->Size = System::Drawing::Size(365, 75);
			this->start_->TabIndex = 0;
			this->start_->Text = L"ZALOGUJ SIÊ";
			this->start_->UseVisualStyleBackColor = false;
			this->start_->Click += gcnew System::EventHandler(this, &MainForm::start_Click);
			// 
			// email_input
			// 
			this->email_input->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->email_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->email_input->ForeColor = System::Drawing::Color::Beige;
			this->email_input->Location = System::Drawing::Point(22, 127);
			this->email_input->Name = L"email_input";
			this->email_input->Size = System::Drawing::Size(365, 31);
			this->email_input->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(22, 100);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 24);
			this->label1->TabIndex = 4;
			this->label1->Text = L"email:";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->aboutToolStripMenuItem, this->dataBaseToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(399, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->clearToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(101, 22);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(101, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// dataBaseToolStripMenuItem
			// 
			this->dataBaseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->usersToolStripMenuItem,
					this->userLogsToolStripMenuItem
			});
			this->dataBaseToolStripMenuItem->Name = L"dataBaseToolStripMenuItem";
			this->dataBaseToolStripMenuItem->Size = System::Drawing::Size(67, 20);
			this->dataBaseToolStripMenuItem->Text = L"DataBase";
			// 
			// usersToolStripMenuItem
			// 
			this->usersToolStripMenuItem->Name = L"usersToolStripMenuItem";
			this->usersToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->usersToolStripMenuItem->Text = L"Users";
			this->usersToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::usersToolStripMenuItem_Click);
			// 
			// userLogsToolStripMenuItem
			// 
			this->userLogsToolStripMenuItem->Name = L"userLogsToolStripMenuItem";
			this->userLogsToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->userLogsToolStripMenuItem->Text = L"UserLogs";
			this->userLogsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::userLogsToolStripMenuItem_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(18, 190);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 24);
			this->label2->TabIndex = 7;
			this->label2->Text = L"has³o:";
			// 
			// password_input
			// 
			this->password_input->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->password_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->password_input->ForeColor = System::Drawing::Color::Beige;
			this->password_input->Location = System::Drawing::Point(22, 217);
			this->password_input->Name = L"password_input";
			this->password_input->PasswordChar = '*';
			this->password_input->Size = System::Drawing::Size(365, 31);
			this->password_input->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(277, 63);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(399, 417);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->password_input);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->email_input);
			this->Controls->Add(this->start_);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Hangman";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}

};
}

