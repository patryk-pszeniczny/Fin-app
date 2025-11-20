#include "FinForm.h"
#include <regex>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Globalization;
using namespace System::Drawing;

namespace Szablon {

    FinForm::FinForm(FinLogic* finlogic)
    {
        this->_finlogic = finlogic;
        this->init();
    }
    void FinForm::init() {
        InitializeComponent();
        ApplyModernTheme();
        ApplyEvents();
        RecalculateTotals();
        InitTypeCombo();
    }
    void FinForm::dataGridView1_RowsAdded(System::Object^, System::Windows::Forms::DataGridViewRowsAddedEventArgs^)
    {
        this->RecalculateTotals();
    }

    void FinForm::dataGridView1_RowsRemoved(System::Object^, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^)
    {
        this->RecalculateTotals();
    }

    void FinForm::dataGridView1_Sorted(System::Object^, System::EventArgs^)
    {
        this->RecalculateTotals();
    }
    bool TryParseAmountFromLabel(String^ text, double% outVal)
    {
        outVal = 0.0;
 

        if (String::IsNullOrWhiteSpace(text)) return false;


        String^ num = text;

        // próbuj PL i invariant
        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        double tmp;
        if (Double::TryParse(num, NumberStyles::Number | NumberStyles::AllowLeadingSign, pl, tmp)) {
            outVal = tmp; return true;
        }
        if (Double::TryParse(num, NumberStyles::Number | NumberStyles::AllowLeadingSign, CultureInfo::InvariantCulture, tmp)) {
            outVal = tmp; return true;
        }
        return false;
    }
    void FinForm::UpdateStampFromLabel(double balance)
    {
        if (this->pictureBox_stamp == nullptr) return;

        String^ fileName = (balance >= this->_finlogic->getStamp()) ? L"success.jpg" : L"fail.jpg";

        // To daje absolutną ścieżkę z katalogu roboczego (tak jak działało wcześniej)
        String^ fullPath = System::IO::Path::GetFullPath(fileName);

        // jeśli już mamy ten sam obrazek -> nic nie rób
        String^ currentPath = dynamic_cast<String^>(this->pictureBox_stamp->Tag);
        if (currentPath != nullptr &&
            String::Equals(currentPath, fullPath, StringComparison::OrdinalIgnoreCase))
        {
            return;
        }

        if (!System::IO::File::Exists(fullPath)) {
            System::Windows::Forms::MessageBox::Show(
                L"Brak pliku obrazka: " + fullPath +
                L"\nCurrentDirectory: " + System::Environment::CurrentDirectory
            );
            return;
        }

        System::Drawing::Image^ newImg = nullptr;

        try
        {
            array<System::Byte>^ bytes = System::IO::File::ReadAllBytes(fullPath);
            if (bytes == nullptr || bytes->Length == 0) {
                System::Windows::Forms::MessageBox::Show(L"Pusty plik obrazka: " + fullPath);
                return;
            }

            auto ms = gcnew System::IO::MemoryStream(bytes);
            ms->Position = 0;

            auto tmp = System::Drawing::Image::FromStream(ms, true, true);
            newImg = safe_cast<System::Drawing::Image^>(tmp->Clone());

            delete tmp;
            delete ms;
        }
        catch (System::Exception^ ex)
        {
            System::Windows::Forms::MessageBox::Show(
                L"Błąd wczytywania obrazka: " + ex->Message +
                L"\nŚcieżka: " + fullPath
            );
            return;
        }

        // podmień obraz i zwolnij stary dopiero po sukcesie
        auto oldImg = this->pictureBox_stamp->Image;
        this->pictureBox_stamp->Image = newImg;
        this->pictureBox_stamp->Tag = fullPath;
        this->pictureBox_stamp->SizeMode = PictureBoxSizeMode::Zoom;

        if (oldImg != nullptr) delete oldImg;
    }



    bool FinForm::ValidateKwotaCell(System::String^ text, double% parsed)
    {
        String^ t = text ? text->Trim()->Replace(L' ', L'\0') : L"";
        if (String::IsNullOrWhiteSpace(t)) return false;

        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        double val;
        if (Double::TryParse(t, NumberStyles::Number | NumberStyles::AllowLeadingSign, pl, val)) { parsed = val; return true; }
        if (Double::TryParse(t, NumberStyles::Number | NumberStyles::AllowLeadingSign, CultureInfo::InvariantCulture, val)) { parsed = val; return true; }
        return false;
    }

    void FinForm::SetKwotaColor(DataGridViewRow^ row)
    {
        if (row == nullptr) return;
        DataGridViewCell^ c = row->Cells[L"kwota"];
        if (c == nullptr || c->Value == nullptr) return;

        double val = 0.0;
        if (c->Value->GetType() == double::typeid || c->Value->GetType() == Decimal::typeid) {
            val = Convert::ToDouble(c->Value);
        }
        else {
            double parsed;
            if (ValidateKwotaCell(Convert::ToString(c->Value), parsed)) val = parsed;
        }

        Color incomeFg = Color::FromArgb(22, 163, 74);
        Color expenseFg = Color::FromArgb(220, 38, 38);
        c->Style->ForeColor = (val >= 0.0) ? incomeFg : expenseFg;
    }

    void FinForm::loadRandomData()
    {
        if (this->dataGridView1 == nullptr) return;

        this->dataGridView1->Rows->Clear();

        Color incomeFg = Color::FromArgb(22, 163, 74);
        Color expenseFg = Color::FromArgb(220, 38, 38);

        cli::array<String^>^ kategorie = gcnew cli::array<String^>{
            L"Jedzenie", L"Transport", L"Mieszkanie", L"Rachunki", L"Zdrowie",
                L"Rozrywka", L"Zakupy", L"Edukacja", L"Sport", L"Inne"
        };

        Random^ rnd = gcnew Random();

        const int rowsCount = 25;

        for (int i = 0; i < rowsCount; ++i)
        {
            int past = rnd->Next(0, 90);
            DateTime dt = DateTime::Now.AddDays(-past);

            String^ typ = kategorie[rnd->Next(kategorie->Length)];

            bool isIncome = rnd->NextDouble() < 0.35;

            double base = isIncome ? rnd->Next(100, 1200) : rnd->Next(10, 500);
            double cents = rnd->NextDouble();
            double amount = Math::Round(base + cents, 2);
            if (!isIncome) amount = -amount;

            int rowIdx = this->dataGridView1->Rows->Add(
                dt.ToString(L"yyyy-MM-dd"),
                typ,
                amount,
                nullptr,
                nullptr
            );

            DataGridViewRow^ row = this->dataGridView1->Rows[rowIdx];
            DataGridViewCell^ kwCell = row->Cells[L"kwota"];
            kwCell->Style->ForeColor = amount >= 0 ? incomeFg : expenseFg;

            row->Cells[L"data"]->ToolTipText = L"Data operacji";
            row->Cells[L"typ"]->ToolTipText = L"Kategoria";
            row->Cells[L"kwota"]->ToolTipText = isIncome ? L"Wpływ" : L"Wydatek";
        }

        try {
            this->dataGridView1->Sort(this->dataGridView1->Columns[L"data"], System::ComponentModel::ListSortDirection::Descending);
        }
        catch (...) {
        }
        this->ReapplyCurrentSort(nullptr);
    }

    bool FinForm::TryParseKwota(System::Object^ val, double% outVal)
    {
        outVal = 0.0;
        if (val == nullptr) return false;

        if (val->GetType() == double::typeid || val->GetType() == Decimal::typeid || val->GetType() == Single::typeid || val->GetType() == Int32::typeid) {
            try { outVal = Convert::ToDouble(val); return true; }
            catch (...) { return false; }
        }

        String^ s = Convert::ToString(val);
        if (String::IsNullOrWhiteSpace(s)) return false;
        s = s->Trim();

        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        double tmp;
        if (Double::TryParse(s, NumberStyles::Number | NumberStyles::AllowLeadingSign, pl, tmp)) { outVal = tmp; return true; }
        if (Double::TryParse(s, NumberStyles::Number | NumberStyles::AllowLeadingSign, CultureInfo::InvariantCulture, tmp)) { outVal = tmp; return true; }
        return false;
    }

    bool FinForm::TryParseDate(System::Object^ val, DateTime% outDate)
    {
        outDate = DateTime::MinValue;
        if (val == nullptr) return false;

        if (val->GetType() == DateTime::typeid) { outDate = *safe_cast<DateTime^>(val); return true; }

        String^ s = Convert::ToString(val);
        if (String::IsNullOrWhiteSpace(s)) return false;
        s = s->Trim();

        cli::array<String^>^ formats = gcnew cli::array<String^>{
            L"yyyy-MM-dd", L"dd.MM.yyyy", L"dd/MM/yyyy", L"yyyy.MM.dd"
        };

        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        DateTime dt;
        if (DateTime::TryParseExact(s, formats, pl, DateTimeStyles::None, dt)) { outDate = dt; return true; }
        if (DateTime::TryParse(s, dt)) { outDate = dt; return true; }
        return false;
    }

    void FinForm::RecalculateTotals()
    {
        if (this->dataGridView1 == nullptr) return;

        double sumIncomeAll = 0.0;
        double sumExpenseAll = 0.0;
        double sumIncomeMonth = 0.0;
        double sumExpenseMonth = 0.0;

        DateTime now = DateTime::Now;
        int curMonth = now.Month;
        int curYear = now.Year;

        for each(DataGridViewRow ^ row in this->dataGridView1->Rows)
        {
            if (row->IsNewRow) continue;

            double amount;
            if (!TryParseKwota(row->Cells[L"kwota"] ? row->Cells[L"kwota"]->Value : nullptr, amount))
                continue;

            DateTime opDate;
            bool hasDate = TryParseDate(row->Cells[L"data"] ? row->Cells[L"data"]->Value : nullptr, opDate);

            if (amount >= 0.0) {
                sumIncomeAll += amount;
                if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
                    sumIncomeMonth += amount;
            }
            else {
                sumExpenseAll += amount;
                if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
                    sumExpenseMonth += amount;
            }
        }

        double balance = sumIncomeAll + sumExpenseAll;

        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        auto fmt = L"C2";

        if (this->wydatki_miesiac) this->wydatki_miesiac->Text = L"Miesiąc: " + (Math::Abs(sumExpenseMonth)).ToString() + " PLN";
        if (this->wydatki_razem)   this->wydatki_razem->Text = L"Wszystko: " + (Math::Abs(sumExpenseAll)).ToString() + " PLN";

        if (this->wplywy_miesiac)  this->wplywy_miesiac->Text = L"Miesiąc: " + (sumIncomeMonth).ToString() + " PLN";
        if (this->wplywy_razem)    this->wplywy_razem->Text = L"Wszystko: " + (sumIncomeAll).ToString() + " PLN";

        if (this->stan_konta)      this->stan_konta->Text = L"Stan: " + (balance).ToString() + " PLN";
		this->UpdateStampFromLabel(balance);
    }

    void Szablon::FinForm::ReapplyCurrentSort(System::Windows::Forms::DataGridViewRow^ preferSelect)
    {
        auto grid = this->dataGridView1;
        if (grid == nullptr) return;

        auto col = grid->SortedColumn;
        if (col != nullptr && grid->SortOrder != System::Windows::Forms::SortOrder::None)
        {
            auto dir = (grid->SortOrder == System::Windows::Forms::SortOrder::Ascending)
                ? System::ComponentModel::ListSortDirection::Ascending
                : System::ComponentModel::ListSortDirection::Descending;

            try { grid->Sort(col, dir); }
            catch (...) {}
        }

        if (preferSelect != nullptr && !preferSelect->IsNewRow)
        {
            grid->ClearSelection();
            preferSelect->Selected = true;
            try { grid->FirstDisplayedScrollingRowIndex = preferSelect->Index; }
            catch (...) {}
        }
    }
    void FinForm::button_stamp_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->dataGridView1 == nullptr) return;

        String^ kwotaStr = this->textBox_stamp ? this->textBox_stamp->Text->Trim() : L"";
        double amount = 0.0;
        if (!this->TryParseKwota(kwotaStr, amount)) {
            MessageBox::Show(this, L"Nieprawidłowa kwota. Użyj liczby, np. 123,45.", L"Błąd walidacji",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            if (this->textBox_stamp) {
                this->textBox_stamp->Focus();
                this->textBox_stamp->SelectAll();
            }
            return;
        }
        this->_finlogic->setStamp(amount);
        this->RecalculateTotals();
        MessageBox::Show(this, L"Zaktualizowano pieczątkę do wartości: " + amount.ToString() + L".", L"Sukces",
			MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    void FinForm::button_random_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->loadRandomData();
		this->RecalculateTotals();
    }
    void FinForm::InitTypeCombo()
    {
        if (this->type_combobox == nullptr) return;
        this->type_combobox->DropDownStyle = ComboBoxStyle::DropDown;
        this->type_combobox->AutoCompleteMode = AutoCompleteMode::SuggestAppend;
        this->type_combobox->AutoCompleteSource = AutoCompleteSource::ListItems;
        this->type_combobox->Items->Clear();
        cli::array<String^>^ kategorie = gcnew cli::array<String^>{
            L"Jedzenie", L"Transport", L"Mieszkanie", L"Rachunki", L"Zdrowie",
                L"Rozrywka", L"Zakupy", L"Edukacja", L"Sport", L"Inne"
        };

        for each (String ^ k in kategorie)
            this->type_combobox->Items->Add(k);
    }

    void FinForm::wprowadz_button_Click(System::Object^, System::EventArgs^)
    {
        if (this->dataGridView1 == nullptr) return;

        String^ typVal = this->type_combobox ? this->type_combobox->Text->Trim() : L"";
        String^ kwotaStr = this->kwota_textbox ? this->kwota_textbox->Text->Trim() : L"";

        if (String::IsNullOrWhiteSpace(typVal)) {
            MessageBox::Show(this, L"Podaj typ/kategorię.", L"Brak danych",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            if (this->type_combobox) this->type_combobox->Focus();
            return;
        }
        if (this->type_combobox && !this->type_combobox->Items->Contains(typVal)){
            this->type_combobox->Items->Add(typVal);
        }
        double amount = 0.0;
        if (!this->TryParseKwota(kwotaStr, amount)) {
            MessageBox::Show(this, L"Nieprawidłowa kwota. Użyj liczby, np. 123,45.", L"Błąd walidacji",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            if (this->kwota_textbox) {
                this->kwota_textbox->Focus();
                this->kwota_textbox->SelectAll();
            }
            return;
        }

        DateTime now = DateTime::Now;
        String^ dataStr = now.ToString(L"yyyy-MM-dd");

        int rowIdx = this->dataGridView1->Rows->Add(dataStr, typVal, amount, nullptr, nullptr);

        DataGridViewRow^ row = this->dataGridView1->Rows[rowIdx];
        this->SetKwotaColor(row);
        row->Cells[L"data"]->ReadOnly = true;
        row->Cells[L"typ"]->ReadOnly = true;
        row->Cells[L"kwota"]->ReadOnly = true;
        row->Tag = false;

        this->ReapplyCurrentSort(row);
        if (this->kwota_textbox) this->kwota_textbox->Clear();
        if (this->kwota_textbox) this->kwota_textbox->Focus();
        this->RecalculateTotals();
    }

    void FinForm::kwota_textbox_KeyDown(System::Object^, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter) {
            e->Handled = true;
            e->SuppressKeyPress = true;
            this->wprowadz_button_Click(nullptr, EventArgs::Empty);
        }
    }

    void FinForm::type_combobox_KeyDown(System::Object^, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter) {
            e->Handled = true;
            e->SuppressKeyPress = true;
            if (this->kwota_textbox) this->kwota_textbox->Focus();
        }
    }


    void FinForm::dataGridView1_CellContentClick(System::Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = this->dataGridView1;
        auto col = grid->Columns[e->ColumnIndex];

        if (col->Name == L"rem")
        {
            DataGridViewRow^ row = grid->Rows[e->RowIndex];
            String^ msg = L"Czy na pewno chcesz usunąć wybrany wiersz?";
            auto res = MessageBox::Show(this, msg, L"Usuń", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
            if (res == ::DialogResult::Yes)
            {
                grid->Rows->RemoveAt(e->RowIndex);
            }
            return;
        }

        if (col->Name == L"edit")
        {
            DataGridViewRow^ row = grid->Rows[e->RowIndex];

            bool isEditing = false;
            if (row->Tag != nullptr) isEditing = safe_cast<bool>(row->Tag);

            if (!isEditing)
            {
                row->Tag = true;
                row->Cells[L"data"]->ReadOnly = false;
                row->Cells[L"typ"]->ReadOnly = false;
                row->Cells[L"kwota"]->ReadOnly = false;

                row->Cells[L"edit"]->Value = L"💾";
                grid->CurrentCell = row->Cells[L"data"];
                grid->BeginEdit(true);
            }
            else
            {
                DataGridViewCell^ kw = row->Cells[L"kwota"];
                double parsed;
                if (!ValidateKwotaCell(Convert::ToString(kw->Value), parsed))
                {
                    MessageBox::Show(this, L"Nieprawidłowa wartość w kolumnie 'Kwota'. Użyj liczby (np. 123,45).",
                        L"Błąd walidacji", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    grid->CurrentCell = kw;
                    grid->BeginEdit(true);
                    return;
                }
                kw->Value = parsed;

                row->Cells[L"data"]->ReadOnly = true;
                row->Cells[L"typ"]->ReadOnly = true;
                row->Cells[L"kwota"]->ReadOnly = true;

                row->Cells[L"edit"]->Value = L"✎";
                row->Tag = false;

                SetKwotaColor(row);
            }
        }
    }

    void FinForm::dataGridView1_CellValidating(System::Object^ sender, DataGridViewCellValidatingEventArgs^ e)
    {
        auto grid = this->dataGridView1;
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto col = grid->Columns[e->ColumnIndex];
        if (col->Name == L"kwota")
        {
            double parsed;
            if (!ValidateKwotaCell(Convert::ToString(e->FormattedValue), parsed))
            {
                grid->Rows[e->RowIndex]->ErrorText = L"Kwota musi być liczbą.";
                e->Cancel = true;
            }
            else
            {
                grid->Rows[e->RowIndex]->ErrorText = String::Empty;
            }
        }
    }

    void FinForm::dataGridView1_CellEndEdit(System::Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = this->dataGridView1;
        auto row = grid->Rows[e->RowIndex];
        auto col = grid->Columns[e->ColumnIndex];

        if (col->Name == L"kwota")
        {
            SetKwotaColor(row);
        }
        if (col->Name == L"data")
        {
            this->ReapplyCurrentSort(this->dataGridView1->Rows[e->RowIndex]);
        }
        this->RecalculateTotals();
        row->ErrorText = String::Empty;
    }

    void FinForm::dataGridView1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Delete)
        {
            auto grid = this->dataGridView1;
            if (grid->CurrentRow != nullptr && !grid->CurrentRow->IsNewRow)
            {
                auto res = MessageBox::Show(this, L"Usunąć zaznaczony wiersz?", L"Usuń", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
                if (res == ::DialogResult::Yes)
                {
                    grid->Rows->Remove(grid->CurrentRow);
                }
                e->Handled = true;
            }
        }
    }
}
