#include "FinForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Globalization;
using namespace System::Drawing;

namespace Szablon {

    void Szablon::FinForm::dataGridView1_RowsAdded(System::Object^, System::Windows::Forms::DataGridViewRowsAddedEventArgs^)
    {
        this->RecalculateTotals();
    }

    void Szablon::FinForm::dataGridView1_RowsRemoved(System::Object^, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^)
    {
        this->RecalculateTotals();
    }

    void Szablon::FinForm::dataGridView1_Sorted(System::Object^, System::EventArgs^)
    {
        this->RecalculateTotals();
    }

    // ====== POMOCNICZE ======
    bool FinForm::ValidateKwotaCell(System::String^ text, double% parsed)
    {
        // Akceptuj kropkę i przecinek, usuń spacje
        String^ t = text ? text->Trim()->Replace(L' ', L'\0') : L"";
        if (String::IsNullOrWhiteSpace(t)) return false;

        // Spróbuj wg kultury PL, a następnie invariant
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
        // Spróbuj z wartości typu double lub tekstu
        if (c->Value->GetType() == double::typeid || c->Value->GetType() == Decimal::typeid) {
            val = Convert::ToDouble(c->Value);
        }
        else {
            double parsed;
            if (ValidateKwotaCell(Convert::ToString(c->Value), parsed)) val = parsed;
        }

        Color incomeFg = Color::FromArgb(22, 163, 74);   // zielony
        Color expenseFg = Color::FromArgb(220, 38, 38);   // czerwony
        c->Style->ForeColor = (val >= 0.0) ? incomeFg : expenseFg;
    }

    void FinForm::loadRandomData()
    {
        // Bezpiecznik
        if (this->dataGridView1 == nullptr) return;

        // Wyczyść stare
        this->dataGridView1->Rows->Clear();

        // Prosta paleta do kwot +/- (spójna z motywem)
        Color incomeFg = Color::FromArgb(22, 163, 74);   // zielony
        Color expenseFg = Color::FromArgb(220, 38, 38);  // czerwony

        // Losowe dane
        cli::array<String^>^ kategorie = gcnew cli::array<String^>{
            L"Jedzenie", L"Transport", L"Mieszkanie", L"Rachunki", L"Zdrowie",
                L"Rozrywka", L"Zakupy", L"Edukacja", L"Sport", L"Inne"
        };

        Random^ rnd = gcnew Random();

        // Ile rekordów wygenerować
        const int rowsCount = 25;

        for (int i = 0; i < rowsCount; ++i)
        {
            // data z ostatnich 90 dni
            int past = rnd->Next(0, 90);
            DateTime dt = DateTime::Now.AddDays(-past);

            // kategoria
            String^ typ = kategorie[rnd->Next(kategorie->Length)];

            // 35% to wpływy, reszta wydatki
            bool isIncome = rnd->NextDouble() < 0.35;

            // generuj kwotę
            double base = isIncome ? rnd->Next(100, 1200) : rnd->Next(10, 500);
            double cents = rnd->NextDouble(); // ułamek
            double amount = Math::Round(base + cents, 2);
            if (!isIncome) amount = -amount;  // wydatki ujemne

            // Dodaj wiersz: data | typ | kwota | [przyciski]
            // Przyciski mają UseColumnTextForButtonValue = true -> wartości można zostawić null
            int rowIdx = this->dataGridView1->Rows->Add(
                dt.ToString(L"yyyy-MM-dd"), // albo "dd.MM.yyyy" jeżeli tak wolisz
                typ,
                amount,   // kolumna jest numeryczna i ma format "N2" z ApplyModernTheme
                nullptr,
                nullptr
            );

            // Kolor kwoty zależnie od znaku
            DataGridViewRow^ row = this->dataGridView1->Rows[rowIdx];
            DataGridViewCell^ kwCell = row->Cells[L"kwota"];
            kwCell->Style->ForeColor = amount >= 0 ? incomeFg : expenseFg;

            // Drobne tooltipy
            row->Cells[L"data"]->ToolTipText = L"Data operacji";
            row->Cells[L"typ"]->ToolTipText = L"Kategoria";
            row->Cells[L"kwota"]->ToolTipText = isIncome ? L"Wpływ" : L"Wydatek";
        }

        // Opcjonalnie: posortuj malejąco po dacie
        try {
            this->dataGridView1->Sort(this->dataGridView1->Columns[L"data"], System::ComponentModel::ListSortDirection::Descending);
        }
        catch (...) {
            // ignoruj jeśli kolumna nie pozwala na sortowanie
        }
        this->ReapplyCurrentSort(nullptr);
    }

    bool FinForm::TryParseKwota(System::Object^ val, double% outVal)
    {
        outVal = 0.0;
        if (val == nullptr) return false;

        // jeśli to już liczba
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

        // jeśli już DateTime
        if (val->GetType() == DateTime::typeid) { outDate = *safe_cast<DateTime^>(val); return true; }

        String^ s = Convert::ToString(val);
        if (String::IsNullOrWhiteSpace(s)) return false;
        s = s->Trim();

        // obsłuż popularne formaty które używaliśmy w loadRandomData
        cli::array<String^>^ formats = gcnew cli::array<String^> {
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
        double sumExpenseAll = 0.0; // jako wartości ujemne (na końcu weźmiemy moduł do labela)
        double sumIncomeMonth = 0.0;
        double sumExpenseMonth = 0.0;

        DateTime now = DateTime::Now;
        int curMonth = now.Month;
        int curYear = now.Year;

        for each (DataGridViewRow ^ row in this->dataGridView1->Rows)
        {
            if (row->IsNewRow) continue;

            // Kwota
            double amount;
            if (!TryParseKwota(row->Cells[L"kwota"] ? row->Cells[L"kwota"]->Value : nullptr, amount))
                continue;

            // Data (jeśli brak/niepoprawna, licz tylko do "razem")
            DateTime opDate;
            bool hasDate = TryParseDate(row->Cells[L"data"] ? row->Cells[L"data"]->Value : nullptr, opDate);

            if (amount >= 0.0) {
                sumIncomeAll += amount;
                if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
                    sumIncomeMonth += amount;
            }
            else {
                sumExpenseAll += amount; // ujemne
                if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
                    sumExpenseMonth += amount; // ujemne
            }
        }

        // Stan konta: suma wszystkich kwot
        double balance = sumIncomeAll + sumExpenseAll; // expenseAll jest ujemne

        // Do labeli: wydatki pokazujemy jako wartości dodatnie (moduł)
        CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
        auto fmt = L"C2"; // waluta wg PL (zł)

        if (this->wydatki_miesiac) this->wydatki_miesiac->Text = L"Miesiąc: "+(Math::Abs(sumExpenseMonth)).ToString()+" PLN";
        if (this->wydatki_razem)   this->wydatki_razem->Text = L"Wszystko: "+(Math::Abs(sumExpenseAll)).ToString()+" PLN";

        if (this->wplywy_miesiac)  this->wplywy_miesiac->Text = L"Miesiąc: " + (sumIncomeMonth).ToString() + " PLN";
        if (this->wplywy_razem)    this->wplywy_razem->Text = L"Wszystko: " + (sumIncomeAll).ToString() + " PLN";

        if (this->stan_konta)      this->stan_konta->Text = L"Stan: " + (balance).ToString()+ " PLN";
    }
    void Szablon::FinForm::ReapplyCurrentSort(System::Windows::Forms::DataGridViewRow^ preferSelect)
    {
        auto grid = this->dataGridView1;
        if (grid == nullptr) return;

        // Jeśli coś jest już posortowane – zastosuj ponownie
        auto col = grid->SortedColumn;
        if (col != nullptr && grid->SortOrder != System::Windows::Forms::SortOrder::None)
        {
            auto dir = (grid->SortOrder == System::Windows::Forms::SortOrder::Ascending)
                ? System::ComponentModel::ListSortDirection::Ascending
                : System::ComponentModel::ListSortDirection::Descending;

            try { grid->Sort(col, dir); }
            catch (...) { /* ignore */ }
        }

        // Przywróć zaznaczenie i przewiń do wiersza, który właśnie dodaliśmy/edytowaliśmy
        if (preferSelect != nullptr && !preferSelect->IsNewRow)
        {
            grid->ClearSelection();
            preferSelect->Selected = true;
            try { grid->FirstDisplayedScrollingRowIndex = preferSelect->Index; }
            catch (...) {}
        }
    }

    void FinForm::wprowadz_button_Click(System::Object^, System::EventArgs^)
    {
        if (this->dataGridView1 == nullptr) return;

        // Pobierz wartości
        String^ typVal = this->typ_textbox ? this->typ_textbox->Text->Trim() : L"";
        String^ kwotaStr = this->kwota_textbox ? this->kwota_textbox->Text->Trim() : L"";

        // Prosta walidacja typu
        if (String::IsNullOrWhiteSpace(typVal)) {
            MessageBox::Show(this, L"Podaj typ/kategorię.", L"Brak danych", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            if (this->typ_textbox) this->typ_textbox->Focus();
            return;
        }

        // Walidacja kwoty (wykorzystuje wcześniejszą pomocniczą TryParseKwota)
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

        // Data = teraz
        DateTime now = DateTime::Now;
        String^ dataStr = now.ToString(L"yyyy-MM-dd"); // lub "dd.MM.yyyy"

        // Dodaj wiersz: data | typ | kwota | [✎] | [🗑]
        int rowIdx = this->dataGridView1->Rows->Add(dataStr, typVal, amount, nullptr, nullptr);

        // Pokoloruj kwotę i zablokuj wiersz (jeśli używasz edycji przez przycisk ✎)
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

    // Enter w polu kwota -> klik wprowadz
    void FinForm::kwota_textbox_KeyDown(System::Object^, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter) {
            e->Handled = true;
            e->SuppressKeyPress = true;
            this->wprowadz_button_Click(nullptr, EventArgs::Empty);
        }
    }

    // Enter w polu typ -> przejdź do kwota
    void FinForm::typ_textbox_KeyDown(System::Object^, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter) {
            e->Handled = true;
            e->SuppressKeyPress = true;
            if (this->kwota_textbox) this->kwota_textbox->Focus();
        }
    }
    // ====== EDYCJA / USUWANIE ======
    void FinForm::dataGridView1_CellContentClick(System::Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = this->dataGridView1;
        auto col = grid->Columns[e->ColumnIndex];

        // Klik "Usuń"
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

        // Klik "Edytuj" / "Zapisz"
        if (col->Name == L"edit")
        {
            DataGridViewRow^ row = grid->Rows[e->RowIndex];

            bool isEditing = false;
            if (row->Tag != nullptr) isEditing = safe_cast<bool>(row->Tag);

            if (!isEditing)
            {
                // Wejdź w tryb edycji wiersza
                row->Tag = true;
                // odblokuj edycję tylko dla 3 pierwszych kolumn
                row->Cells[L"data"]->ReadOnly = false;
                row->Cells[L"typ"]->ReadOnly = false;
                row->Cells[L"kwota"]->ReadOnly = false;

                // Zmień przycisk na "zapisz"
                row->Cells[L"edit"]->Value = L"💾";
                // Ustaw fokus na pierwszą edytowalną
                grid->CurrentCell = row->Cells[L"data"];
                grid->BeginEdit(true);
            }
            else
            {
                // Zapis: walidacja "kwota"
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
                // Zastąp sformatowaną wartością (ułatwia kolorowanie i sort)
                kw->Value = parsed;

                // Zablokuj edycję pól
                row->Cells[L"data"]->ReadOnly = true;
                row->Cells[L"typ"]->ReadOnly = true;
                row->Cells[L"kwota"]->ReadOnly = true;

                // Zmień przycisk z powrotem
                row->Cells[L"edit"]->Value = L"✎";
                row->Tag = false;

                // Ustaw kolor kwoty
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
        // Możesz dodać walidację daty/kategorii, jeśli chcesz
    }

    void FinForm::dataGridView1_CellEndEdit(System::Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = this->dataGridView1;
        auto row = grid->Rows[e->RowIndex];
        auto col = grid->Columns[e->ColumnIndex];

        // Po edycji kwoty – ustaw kolor
        if (col->Name == L"kwota")
        {
            SetKwotaColor(row);
        }
        if (col->Name == L"data")
        {
            this->ReapplyCurrentSort(this->dataGridView1->Rows[e->RowIndex]);
        }
        this->RecalculateTotals();
        // Wyczyść komunikat błędu wiersza
        row->ErrorText = String::Empty;
    }

    // Klawisz Delete usuwa wybrany wiersz (z potwierdzeniem)
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
