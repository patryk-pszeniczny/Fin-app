#include "FinForm.h"
#include <regex>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Globalization;
using namespace System::Drawing;

namespace Szablon {

    // =================== INIT / KONSTRUKTOR ===================

    FinForm::FinForm(FinLogic* finlogic)
    {
        _finlogic = finlogic;
        init();
    }

    void FinForm::init()
    {
        InitializeComponent();
        ApplyModernTheme();
        ApplyEvents();
        InitTypeCombo();
        RecalculateTotals();
    }

    // =================== PROSTE EVENTY ===================

    void FinForm::dataGridView1_RowsAdded(Object^, DataGridViewRowsAddedEventArgs^)
    {
        RecalculateTotals();
    }

    void FinForm::dataGridView1_RowsRemoved(Object^, DataGridViewRowsRemovedEventArgs^)
    {
        RecalculateTotals();
    }

    void FinForm::dataGridView1_Sorted(Object^, EventArgs^)
    {
        RecalculateTotals();
    }

    // =================== UI: PIECZATKA (OBRAZEK) ===================

    void FinForm::UpdateStampFromLabel(double balance)
    {
        if (pictureBox_stamp == nullptr) return;

        // wybierz obrazek na podstawie progu
        String^ fileName = (balance >= _finlogic->getStamp()) ? L"success.jpg" : L"fail.jpg";
        String^ fullPath = System::IO::Path::GetFullPath(fileName);

        // jak to samo co już jest -> nie ruszaj
        String^ currentPath = dynamic_cast<String^>(pictureBox_stamp->Tag);
        if (currentPath != nullptr &&
            String::Equals(currentPath, fullPath, StringComparison::OrdinalIgnoreCase))
            return;

        if (!System::IO::File::Exists(fullPath)) {
            MessageBox::Show(L"Brak pliku: " + fullPath);
            return;
        }

        try
        {
            // wczytaj bytesy i zrób kopię obrazka
            array<Byte>^ bytes = System::IO::File::ReadAllBytes(fullPath);
            auto ms = gcnew System::IO::MemoryStream(bytes);
            auto tmp = Image::FromStream(ms, true, true);
            Image^ newImg = safe_cast<Image^>(tmp->Clone());

            delete tmp;
            delete ms;

            // podmień obraz
            Image^ oldImg = pictureBox_stamp->Image;
            pictureBox_stamp->Image = newImg;
            pictureBox_stamp->Tag = fullPath;
            pictureBox_stamp->SizeMode = PictureBoxSizeMode::Zoom;

            if (oldImg != nullptr) delete oldImg;
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(L"Błąd wczytywania: " + ex->Message);
        }
    }

    // =================== UI: KOLOR KWOTY ===================

    void FinForm::SetKwotaColor(DataGridViewRow^ row)
    {
        if (row == nullptr) return;

        auto cell = row->Cells[L"kwota"];
        if (cell == nullptr) return;

        double val;
        if (!_finlogic->TryParseKwota(cell->Value, val)) return;

        Color green = Color::FromArgb(22, 163, 74);
        Color red = Color::FromArgb(220, 38, 38);

        cell->Style->ForeColor = (val >= 0.0) ? green : red;
    }

    // =================== SUMY / BILANS ===================

    void FinForm::RecalculateTotals()
    {
        if (dataGridView1 == nullptr) return;

        double incAll, expAll, incMonth, expMonth, bal;

        _finlogic->CalculateTotalsFrom(
            dataGridView1,
            incAll, expAll,
            incMonth, expMonth,
            bal
        );

        if (wydatki_miesiac) wydatki_miesiac->Text = L"Miesiąc: " + Math::Abs(expMonth).ToString() + L" PLN";
        if (wydatki_razem)   wydatki_razem->Text = L"Wszystko: " + Math::Abs(expAll).ToString() + L" PLN";

        if (wplywy_miesiac)  wplywy_miesiac->Text = L"Miesiąc: " + incMonth.ToString() + L" PLN";
        if (wplywy_razem)    wplywy_razem->Text = L"Wszystko: " + incAll.ToString() + L" PLN";

        if (stan_konta)      stan_konta->Text = L"Stan: " + bal.ToString() + L" PLN";

        UpdateStampFromLabel(bal);
    }

    // =================== SORTOWANIE PO EDYCJI ===================

    void FinForm::ReapplyCurrentSort(DataGridViewRow^ preferSelect)
    {
        auto grid = dataGridView1;
        if (grid == nullptr) return;

        auto col = grid->SortedColumn;
        if (col != nullptr && grid->SortOrder != SortOrder::None)
        {
            auto dir = (grid->SortOrder == SortOrder::Ascending)
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

    // =================== BUTTONY ===================

    void FinForm::button_stamp_Click(Object^, EventArgs^)
    {
        String^ s = textBox_stamp ? textBox_stamp->Text->Trim() : L"";
        double amount;

        if (!_finlogic->TryParseKwota(s, amount))
        {
            MessageBox::Show(L"Nieprawidłowa kwota (np. 123,45).");
            if (textBox_stamp) { textBox_stamp->Focus(); textBox_stamp->SelectAll(); }
            return;
        }

        _finlogic->setStamp(amount);
        RecalculateTotals();
        MessageBox::Show(L"Pieczątka ustawiona na: " + amount.ToString() + L".");
    }

    void FinForm::button_random_Click(Object^, EventArgs^)
    {
        _finlogic->LoadRandomDataToGrid(dataGridView1);
        ReapplyCurrentSort(nullptr);
        RecalculateTotals();
    }

    // =================== COMBOBOX ===================

    void FinForm::InitTypeCombo()
    {
        if (type_combobox == nullptr) return;

        type_combobox->DropDownStyle = ComboBoxStyle::DropDown;
        type_combobox->AutoCompleteMode = AutoCompleteMode::SuggestAppend;
        type_combobox->AutoCompleteSource = AutoCompleteSource::ListItems;
        type_combobox->Items->Clear();

        array<String^>^ kategorie = gcnew array<String^>{
            L"Jedzenie", L"Transport", L"Mieszkanie", L"Rachunki", L"Zdrowie",
                L"Rozrywka", L"Zakupy", L"Edukacja", L"Sport", L"Inne"
        };

        for each (String ^ k in kategorie)
            type_combobox->Items->Add(k);
    }

    // =================== DODAWANIE NOWEGO WPISU ===================

    void FinForm::wprowadz_button_Click(Object^, EventArgs^)
    {
        if (dataGridView1 == nullptr) return;

        String^ typ = type_combobox ? type_combobox->Text->Trim() : L"";
        String^ kw = kwota_textbox ? kwota_textbox->Text->Trim() : L"";

        if (String::IsNullOrWhiteSpace(typ))
        {
            MessageBox::Show(L"Podaj typ/kategorię.");
            if (type_combobox) type_combobox->Focus();
            return;
        }

        if (type_combobox && !type_combobox->Items->Contains(typ))
            type_combobox->Items->Add(typ);

        double amount;
        if (!_finlogic->TryParseKwota(kw, amount))
        {
            MessageBox::Show(L"Nieprawidłowa kwota (np. 123,45).");
            if (kwota_textbox) { kwota_textbox->Focus(); kwota_textbox->SelectAll(); }
            return;
        }

        String^ dateStr = DateTime::Now.ToString(L"yyyy-MM-dd");
        int rowIdx = dataGridView1->Rows->Add(dateStr, typ, amount, nullptr, nullptr);

        auto row = dataGridView1->Rows[rowIdx];
        SetKwotaColor(row);

        row->Cells[L"data"]->ReadOnly = true;
        row->Cells[L"typ"]->ReadOnly = true;
        row->Cells[L"kwota"]->ReadOnly = true;
        row->Tag = false;

        ReapplyCurrentSort(row);

        if (kwota_textbox) { kwota_textbox->Clear(); kwota_textbox->Focus(); }

        RecalculateTotals();
    }

    // =================== ENTER W POLACH ===================

    void FinForm::kwota_textbox_KeyDown(Object^, KeyEventArgs^ e)
    {
        if (e->KeyCode != Keys::Enter) return;

        e->Handled = true;
        e->SuppressKeyPress = true;
        wprowadz_button_Click(nullptr, EventArgs::Empty);
    }

    void FinForm::type_combobox_KeyDown(Object^, KeyEventArgs^ e)
    {
        if (e->KeyCode != Keys::Enter) return;

        e->Handled = true;
        e->SuppressKeyPress = true;
        if (kwota_textbox) kwota_textbox->Focus();
    }

    // =================== GRID: KLIKNIĘCIA (USUŃ / EDYTUJ) ===================

    void FinForm::dataGridView1_CellContentClick(Object^, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = dataGridView1;
        auto col = grid->Columns[e->ColumnIndex];
        auto row = grid->Rows[e->RowIndex];

        // ---- USUŃ ----
        if (col->Name == L"rem")
        {
            auto res = MessageBox::Show(L"Usunąć wiersz?", L"Usuń",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question);

            if (res == ::DialogResult::Yes)
                grid->Rows->RemoveAt(e->RowIndex);

            return;
        }

        // ---- EDYTUJ / ZAPISZ ----
        if (col->Name != L"edit") return;

        bool isEditing = (row->Tag != nullptr) ? safe_cast<bool>(row->Tag) : false;

        if (!isEditing)
        {
            row->Tag = true;
            row->Cells[L"data"]->ReadOnly = false;
            row->Cells[L"typ"]->ReadOnly = false;
            row->Cells[L"kwota"]->ReadOnly = false;

            row->Cells[L"edit"]->Value = L"💾";
            grid->CurrentCell = row->Cells[L"data"];
            grid->BeginEdit(true);
            return;
        }

        // zapis edycji
        double parsed;
        auto kwCell = row->Cells[L"kwota"];

        if (!_finlogic->ValidateKwotaCell(Convert::ToString(kwCell->Value), parsed))
        {
            MessageBox::Show(L"Kwota musi być liczbą (np. 123,45).");
            grid->CurrentCell = kwCell;
            grid->BeginEdit(true);
            return;
        }

        kwCell->Value = parsed;

        row->Cells[L"data"]->ReadOnly = true;
        row->Cells[L"typ"]->ReadOnly = true;
        row->Cells[L"kwota"]->ReadOnly = true;

        row->Cells[L"edit"]->Value = L"✎";
        row->Tag = false;

        SetKwotaColor(row);
        RecalculateTotals();
    }

    // =================== GRID: WALIDACJA KWOTY ===================

    void FinForm::dataGridView1_CellValidating(Object^, DataGridViewCellValidatingEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = dataGridView1;
        auto col = grid->Columns[e->ColumnIndex];

        if (col->Name != L"kwota") return;

        double parsed;
        if (!_finlogic->ValidateKwotaCell(Convert::ToString(e->FormattedValue), parsed))
        {
            grid->Rows[e->RowIndex]->ErrorText = L"Kwota musi być liczbą.";
            e->Cancel = true;
        }
        else
        {
            grid->Rows[e->RowIndex]->ErrorText = String::Empty;
        }
    }

    // =================== GRID: KONIEC EDYCJI ===================

    void FinForm::dataGridView1_CellEndEdit(Object^, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0 || e->ColumnIndex < 0) return;

        auto grid = dataGridView1;
        auto row = grid->Rows[e->RowIndex];
        auto col = grid->Columns[e->ColumnIndex];

        if (col->Name == L"kwota") SetKwotaColor(row);
        if (col->Name == L"data")  ReapplyCurrentSort(row);

        row->ErrorText = String::Empty;
        RecalculateTotals();
    }

    // =================== DELETE NA GRIDZIE ===================

    void FinForm::dataGridView1_KeyDown(Object^, KeyEventArgs^ e)
    {
        if (e->KeyCode != Keys::Delete) return;

        auto grid = dataGridView1;
        if (grid->CurrentRow == nullptr || grid->CurrentRow->IsNewRow) return;

        auto res = MessageBox::Show(L"Usunąć zaznaczony wiersz?", L"Usuń",
            MessageBoxButtons::YesNo, MessageBoxIcon::Question);

        if (res == ::DialogResult::Yes)
            grid->Rows->Remove(grid->CurrentRow);

        e->Handled = true;
    }
}
