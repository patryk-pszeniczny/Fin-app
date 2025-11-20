#pragma once
#include "FinLogic.h"

namespace Szablon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection; // do DoubleBuffered

	public ref class FinForm : public System::Windows::Forms::Form
	{
	public:
		FinForm(FinLogic* finlogic);
	
	private: System::Windows::Forms::Button^ button_random;
	public:
	private:
		FinLogic* _finlogic;

		void init();
		void RecalculateTotals();
		bool TryParseKwota(System::Object^ val, double% outVal);
		bool TryParseDate(System::Object^ val, System::DateTime% outDate);
		void loadRandomData();
		void InitTypeCombo();
		void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void dataGridView1_CellValidating(System::Object^ sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^ e);
		void dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void dataGridView1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		void UpdateStampFromLabel(double balance);
		bool ValidateKwotaCell(System::String^ text, double% parsed);
		void SetKwotaColor(System::Windows::Forms::DataGridViewRow^ row);
		void dataGridView1_RowsAdded(System::Object^ sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^ e);
		void dataGridView1_RowsRemoved(System::Object^ sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^ e);
		void dataGridView1_Sorted(System::Object^ sender, System::EventArgs^ e);
		void wprowadz_button_Click(System::Object^ sender, System::EventArgs^ e);
		void kwota_textbox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		void type_combobox_KeyDown(System::Object^, System::Windows::Forms::KeyEventArgs^ e);
		void ReapplyCurrentSort(System::Windows::Forms::DataGridViewRow^ preferSelect);
		void button_stamp_Click(System::Object^ sender, System::EventArgs^ e);
		void button_random_Click(System::Object^ sender, System::EventArgs^ e);

	protected:
		~FinForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ data;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ typ;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ kwota;
	private: System::Windows::Forms::DataGridViewButtonColumn^ edit;
	private: System::Windows::Forms::DataGridViewButtonColumn^ rem;
	private: System::Windows::Forms::Label^ wydatki_miesiac;
	private: System::Windows::Forms::Label^ wydatki_razem;
	private: System::Windows::Forms::Label^ wplywy_miesiac;
	private: System::Windows::Forms::Label^ wplywy_razem;
	private: System::Windows::Forms::Label^ stan_konta;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::GroupBox^ groupBox6;
	private: System::Windows::Forms::TextBox^ kwota_textbox;

	private: System::Windows::Forms::GroupBox^ groupBox5;

	private: System::Windows::Forms::Button^ wprowadz_button;
	private: System::Windows::Forms::ComboBox^ type_combobox;
	private: System::Windows::Forms::PictureBox^ pictureBox_stamp;


	private: System::Windows::Forms::GroupBox^ groupBox7;
	private: System::Windows::Forms::Button^ button_stamp;

	private: System::Windows::Forms::GroupBox^ groupBox8;
	private: System::Windows::Forms::TextBox^ textBox_stamp;










	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->data = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->typ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->kwota = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->edit = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->rem = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->wydatki_miesiac = (gcnew System::Windows::Forms::Label());
			this->wydatki_razem = (gcnew System::Windows::Forms::Label());
			this->wplywy_miesiac = (gcnew System::Windows::Forms::Label());
			this->wplywy_razem = (gcnew System::Windows::Forms::Label());
			this->stan_konta = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->wprowadz_button = (gcnew System::Windows::Forms::Button());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->kwota_textbox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->type_combobox = (gcnew System::Windows::Forms::ComboBox());
			this->pictureBox_stamp = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button_stamp = (gcnew System::Windows::Forms::Button());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_stamp = (gcnew System::Windows::Forms::TextBox());
			this->button_random = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_stamp))->BeginInit();
			this->groupBox7->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->data, this->typ,
					this->kwota, this->edit, this->rem
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 95);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(733, 515);
			this->dataGridView1->TabIndex = 0;
			// 
			// data
			// 
			this->data->HeaderText = L"Data";
			this->data->Name = L"data";
			this->data->ReadOnly = true;
			// 
			// typ
			// 
			this->typ->HeaderText = L"Typ";
			this->typ->Name = L"typ";
			this->typ->ReadOnly = true;
			// 
			// kwota
			// 
			this->kwota->HeaderText = L"Kwota";
			this->kwota->Name = L"kwota";
			this->kwota->ReadOnly = true;
			// 
			// edit
			// 
			this->edit->HeaderText = L"Edytuj";
			this->edit->Name = L"edit";
			this->edit->ReadOnly = true;
			// 
			// rem
			// 
			this->rem->HeaderText = L"Usuń";
			this->rem->Name = L"rem";
			this->rem->ReadOnly = true;
			// 
			// wydatki_miesiac
			// 
			this->wydatki_miesiac->AutoSize = true;
			this->wydatki_miesiac->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->wydatki_miesiac->Location = System::Drawing::Point(6, 28);
			this->wydatki_miesiac->Name = L"wydatki_miesiac";
			this->wydatki_miesiac->Size = System::Drawing::Size(51, 20);
			this->wydatki_miesiac->TabIndex = 1;
			this->wydatki_miesiac->Text = L"label1";
			// 
			// wydatki_razem
			// 
			this->wydatki_razem->AutoSize = true;
			this->wydatki_razem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->wydatki_razem->Location = System::Drawing::Point(6, 53);
			this->wydatki_razem->Name = L"wydatki_razem";
			this->wydatki_razem->Size = System::Drawing::Size(51, 20);
			this->wydatki_razem->TabIndex = 2;
			this->wydatki_razem->Text = L"label2";
			// 
			// wplywy_miesiac
			// 
			this->wplywy_miesiac->AutoSize = true;
			this->wplywy_miesiac->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->wplywy_miesiac->Location = System::Drawing::Point(6, 27);
			this->wplywy_miesiac->Name = L"wplywy_miesiac";
			this->wplywy_miesiac->Size = System::Drawing::Size(51, 20);
			this->wplywy_miesiac->TabIndex = 3;
			this->wplywy_miesiac->Text = L"label3";
			// 
			// wplywy_razem
			// 
			this->wplywy_razem->AutoSize = true;
			this->wplywy_razem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->wplywy_razem->Location = System::Drawing::Point(6, 52);
			this->wplywy_razem->Name = L"wplywy_razem";
			this->wplywy_razem->Size = System::Drawing::Size(51, 20);
			this->wplywy_razem->TabIndex = 4;
			this->wplywy_razem->Text = L"label4";
			// 
			// stan_konta
			// 
			this->stan_konta->AutoSize = true;
			this->stan_konta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->stan_konta->Location = System::Drawing::Point(6, 27);
			this->stan_konta->Name = L"stan_konta";
			this->stan_konta->Size = System::Drawing::Size(51, 20);
			this->stan_konta->TabIndex = 5;
			this->stan_konta->Text = L"label5";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->wydatki_miesiac);
			this->groupBox1->Controls->Add(this->wydatki_razem);
			this->groupBox1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(240, 76);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"WYDATKI";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &FinForm::groupBox1_Enter);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->wplywy_miesiac);
			this->groupBox2->Controls->Add(this->wplywy_razem);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->groupBox2->Location = System::Drawing::Point(258, 13);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(240, 76);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"PRZYCHÓD";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->stan_konta);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->groupBox3->Location = System::Drawing::Point(505, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(240, 76);
			this->groupBox3->TabIndex = 8;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"RAZEM";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->wprowadz_button);
			this->groupBox4->Controls->Add(this->groupBox6);
			this->groupBox4->Controls->Add(this->groupBox5);
			this->groupBox4->Location = System::Drawing::Point(13, 617);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(732, 95);
			this->groupBox4->TabIndex = 9;
			this->groupBox4->TabStop = false;
			// 
			// wprowadz_button
			// 
			this->wprowadz_button->BackColor = System::Drawing::Color::Lime;
			this->wprowadz_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->wprowadz_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->wprowadz_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->wprowadz_button->Location = System::Drawing::Point(492, 30);
			this->wprowadz_button->Name = L"wprowadz_button";
			this->wprowadz_button->Size = System::Drawing::Size(234, 52);
			this->wprowadz_button->TabIndex = 2;
			this->wprowadz_button->Text = L"WPROWADŹ";
			this->wprowadz_button->UseVisualStyleBackColor = false;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->kwota_textbox);
			this->groupBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->groupBox6->Location = System::Drawing::Point(332, 19);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(153, 63);
			this->groupBox6->TabIndex = 1;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Kwota";
			// 
			// kwota_textbox
			// 
			this->kwota_textbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->kwota_textbox->Location = System::Drawing::Point(7, 26);
			this->kwota_textbox->Name = L"kwota_textbox";
			this->kwota_textbox->Size = System::Drawing::Size(127, 24);
			this->kwota_textbox->TabIndex = 0;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->type_combobox);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->groupBox5->Location = System::Drawing::Point(6, 19);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(320, 63);
			this->groupBox5->TabIndex = 0;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Typ";
			// 
			// type_combobox
			// 
			this->type_combobox->FormattingEnabled = true;
			this->type_combobox->Location = System::Drawing::Point(6, 26);
			this->type_combobox->Name = L"type_combobox";
			this->type_combobox->Size = System::Drawing::Size(290, 28);
			this->type_combobox->TabIndex = 0;
			// 
			// pictureBox_stamp
			// 
			this->pictureBox_stamp->Location = System::Drawing::Point(773, 95);
			this->pictureBox_stamp->Name = L"pictureBox_stamp";
			this->pictureBox_stamp->Size = System::Drawing::Size(505, 505);
			this->pictureBox_stamp->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_stamp->TabIndex = 10;
			this->pictureBox_stamp->TabStop = false;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->button_stamp);
			this->groupBox7->Controls->Add(this->groupBox8);
			this->groupBox7->Location = System::Drawing::Point(773, 617);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(505, 95);
			this->groupBox7->TabIndex = 11;
			this->groupBox7->TabStop = false;
			// 
			// button_stamp
			// 
			this->button_stamp->BackColor = System::Drawing::Color::Lime;
			this->button_stamp->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_stamp->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_stamp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button_stamp->Location = System::Drawing::Point(265, 30);
			this->button_stamp->Name = L"button_stamp";
			this->button_stamp->Size = System::Drawing::Size(234, 52);
			this->button_stamp->TabIndex = 2;
			this->button_stamp->Text = L"WPROWADŹ";
			this->button_stamp->UseVisualStyleBackColor = false;
			this->button_stamp->Click += gcnew System::EventHandler(this, &FinForm::button_stamp_Click);
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->textBox_stamp);
			this->groupBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->groupBox8->Location = System::Drawing::Point(6, 19);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(231, 63);
			this->groupBox8->TabIndex = 1;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Próg";
			// 
			// textBox_stamp
			// 
			this->textBox_stamp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox_stamp->Location = System::Drawing::Point(7, 26);
			this->textBox_stamp->Name = L"textBox_stamp";
			this->textBox_stamp->Size = System::Drawing::Size(200, 24);
			this->textBox_stamp->TabIndex = 0;
			this->textBox_stamp->Text = L"50";
			// 
			// button_random
			// 
			this->button_random->BackColor = System::Drawing::Color::Lime;
			this->button_random->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_random->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_random->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button_random->Location = System::Drawing::Point(773, 23);
			this->button_random->Name = L"button_random";
			this->button_random->Size = System::Drawing::Size(505, 52);
			this->button_random->TabIndex = 12;
			this->button_random->Text = L"LOAD RANDOM DATA";
			this->button_random->UseVisualStyleBackColor = false;
			this->button_random->Click += gcnew System::EventHandler(this, &FinForm::button_random_Click);
			// 
			// FinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1293, 724);
			this->Controls->Add(this->button_random);
			this->Controls->Add(this->groupBox7);
			this->Controls->Add(this->pictureBox_stamp);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"FinForm";
			this->Text = L"FinForm";
			this->Load += gcnew System::EventHandler(this, &FinForm::FinForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_stamp))->EndInit();
			this->groupBox7->ResumeLayout(false);
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		void ApplyEvents() {
			this->wprowadz_button->Click += gcnew System::EventHandler(this, &FinForm::wprowadz_button_Click);
			this->kwota_textbox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FinForm::kwota_textbox_KeyDown);
		
			this->dataGridView1->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &FinForm::dataGridView1_RowsAdded);
			this->dataGridView1->RowsRemoved += gcnew System::Windows::Forms::DataGridViewRowsRemovedEventHandler(this, &FinForm::dataGridView1_RowsRemoved);
			this->dataGridView1->Sorted += gcnew System::EventHandler(this, &FinForm::dataGridView1_Sorted);

			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &FinForm::dataGridView1_CellContentClick);
			this->dataGridView1->CellValidating += gcnew System::Windows::Forms::DataGridViewCellValidatingEventHandler(this, &FinForm::dataGridView1_CellValidating);
			this->dataGridView1->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &FinForm::dataGridView1_CellEndEdit);
			this->dataGridView1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FinForm::dataGridView1_KeyDown);
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->type_combobox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FinForm::type_combobox_KeyDown);
			this->data->ReadOnly = false;
			this->typ->ReadOnly = false;
			this->kwota->ReadOnly = false;
		}
		void ApplyModernTheme()
		{
			// --- Paleta (light modern) ---
			Color bg = Color::FromArgb(248, 250, 252);  // tło formularza
			Color card = Color::White;                    // tło siatki
			Color gridLines = Color::FromArgb(229, 231, 235);  // linie
			Color headerBg = Color::FromArgb(15, 23, 42);     // granatowy nagłówek
			Color headerFg = Color::White;                    // tekst nagłówka
			Color rowAltBg = Color::FromArgb(247, 249, 252);  // naprzemienne wiersze
			Color rowFg = Color::FromArgb(17, 24, 39);     // tekst wierszy
			Color selBg = Color::FromArgb(59, 130, 246);   // niebieskie zaznaczenie
			Color selFg = Color::White;                    // tekst zaznaczenia

			this->BackColor = bg;

			// --- Podstawy DataGridView ---
			this->dataGridView1->BackgroundColor = card;
			this->dataGridView1->BorderStyle = BorderStyle::None;
			this->dataGridView1->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			this->dataGridView1->GridColor = gridLines;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->RowTemplate->Height = 36;
			this->dataGridView1->EnableHeadersVisualStyles = false;
			this->dataGridView1->ColumnHeadersHeight = 44;

			// --- Styl nagłówków ---
			DataGridViewCellStyle^ hdr = gcnew DataGridViewCellStyle();
			hdr->Alignment = DataGridViewContentAlignment::MiddleLeft;
			hdr->BackColor = headerBg;
			hdr->ForeColor = headerFg;
			hdr->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.5F, FontStyle::Bold);
			hdr->SelectionBackColor = headerBg;
			hdr->SelectionForeColor = headerFg;
			hdr->WrapMode = DataGridViewTriState::False;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = hdr;

			// --- Styl komórek (default) ---
			DataGridViewCellStyle^ cell = gcnew DataGridViewCellStyle();
			cell->BackColor = card;
			cell->ForeColor = rowFg;
			cell->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Regular);
			cell->SelectionBackColor = selBg;
			cell->SelectionForeColor = selFg;
			cell->Padding = System::Windows::Forms::Padding(8, 6, 8, 6);
			this->dataGridView1->DefaultCellStyle = cell;

			// --- Naprzemienne wiersze ---
			DataGridViewCellStyle^ alt = gcnew DataGridViewCellStyle();
			alt->BackColor = rowAltBg;
			alt->ForeColor = rowFg;
			alt->SelectionBackColor = selBg;
			alt->SelectionForeColor = selFg;
			this->dataGridView1->AlternatingRowsDefaultCellStyle = alt;

			// --- Wyrównania / formaty ---
			this->data->HeaderText = L"Data";
			this->data->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
			this->data->MinimumWidth = 140;

			this->typ->HeaderText = L"Typ";
			this->typ->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
			this->typ->MinimumWidth = 160;

			this->kwota->HeaderText = L"Kwota";
			this->kwota->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
			this->kwota->DefaultCellStyle->Format = L"N2"; // format liczbowy 2 miejsca
			this->kwota->MinimumWidth = 140;

			// --- Kolumny akcji (przyciski z ikonami-znakami) ---
			this->edit->HeaderText = L"Edytuj";
			this->edit->Text = L"✎";
			this->edit->UseColumnTextForButtonValue = true;
			this->edit->FlatStyle = FlatStyle::Flat;
			this->edit->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			this->edit->MinimumWidth = 80;
			this->edit->Width = 80;

			this->rem->HeaderText = L"Usuń";
			this->rem->Text = L"🗑";
			this->rem->UseColumnTextForButtonValue = true;
			this->rem->FlatStyle = FlatStyle::Flat;
			this->rem->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			this->rem->MinimumWidth = 80;
			this->rem->Width = 80;

			// --- Podpowiedź: jeżeli chcesz aby kolumna przycisku nie rozciągała się przy Fill ---
			this->edit->AutoSizeMode = DataGridViewAutoSizeColumnMode::None;
			this->rem->AutoSizeMode = DataGridViewAutoSizeColumnMode::None;

			// --- Mniej migotania – DoubleBuffered przez refleksję ---
			PropertyInfo^ pi = DataGridView::typeid->GetProperty(L"DoubleBuffered",
				BindingFlags::NonPublic | BindingFlags::Instance);
			if (pi != nullptr) {
				pi->SetValue(this->dataGridView1, true, nullptr);
			}
		}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void FinForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
