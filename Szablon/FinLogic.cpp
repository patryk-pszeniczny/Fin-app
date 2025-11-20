#include "FinLogic.h"
#include "FinBase.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Globalization;
using namespace System::Drawing;

namespace Szablon {

	FinLogic::FinLogic(std::string name, std::string password)
	{
		this->name = name;
		this->password = password;
		this->stamp = 50;
	}
	std::string FinLogic::getName()
	{
		return this->name;
	}
	std::string FinLogic::getPassword()
	{
		return this->password;
	}
	double FinLogic::getStamp()
	{
		return this->stamp;
	}
	void FinLogic::setStamp(double newStamp)
	{
		this->stamp = newStamp;
	}
	bool FinLogic::TryParseKwota(System::Object^ val, double% outVal)
	{
		outVal = 0.0;
		if (val == nullptr) return false;

		if (val->GetType() == double::typeid || val->GetType() == Decimal::typeid || val->GetType() == Single::typeid || val->GetType() == Int32::typeid) {
			try { 
				outVal = Convert::ToDouble(val); 
				return true; 
			}
			catch (...) { 
				return false; 
			}
		}

		String^ s = Convert::ToString(val);
		if (String::IsNullOrWhiteSpace(s)) return false;
		s = s->Trim();

		CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
		double tmp;
		if (Double::TryParse(s, NumberStyles::Number | NumberStyles::AllowLeadingSign, pl, tmp)) { 
			outVal = tmp;
			return true; 
		}
		if (Double::TryParse(s, NumberStyles::Number | NumberStyles::AllowLeadingSign, CultureInfo::InvariantCulture, tmp)) {
			outVal = tmp;
			return true; 
		}
		return false;
	}
	bool FinLogic::TryParseDate(System::Object^ val, System::DateTime% outDate) {
		outDate = DateTime::MinValue;
		if (val == nullptr) return false;
		if (val->GetType() == DateTime::typeid) {
			outDate = safe_cast<DateTime>(val);
			return true;
		}
		String^ s = Convert::ToString(val);
		if (String::IsNullOrWhiteSpace(s)) return false;
		s = s->Trim();

		array<String^>^ formats = gcnew array<String^>{
			L"yyyy-MM-dd", L"dd.MM.yyyy", L"dd/MM/yyyy", L"yyyy.MM.dd"
		};
		CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
		DateTime dt;
		if (DateTime::TryParseExact(s, formats, pl, DateTimeStyles::None, dt)) {
			outDate = dt;
			return true;
		}
		if (DateTime::TryParse(s, pl, DateTimeStyles::None, dt)) {
			outDate = dt;
			return true;
		}
		return false;
	}
	bool FinLogic::ValidateKwotaCell(String^ text, double% parsed)
	{
		parsed = 0.0;
		String^ t = text ? text->Trim()->Replace(L' ', L'\0') : L"";
		if (String::IsNullOrWhiteSpace(t)) return false;

		CultureInfo^ pl = gcnew CultureInfo(L"pl-PL");
		double val;

		if (Double::TryParse(t, NumberStyles::Number | NumberStyles::AllowLeadingSign, pl, val))
		{
			parsed = val; 
			return true;
		}

		if (Double::TryParse(t, NumberStyles::Number | NumberStyles::AllowLeadingSign, CultureInfo::InvariantCulture, val))
		{
			parsed = val; 
			return true;
		}
		return false;
	}
	void FinLogic::CalculateTotalsFrom(
		DataGridView^ grid,
		double% sumIncomeAll,
		double% sumExpenseAll,
		double% sumIncomeMonth,
		double% sumExpenseMonth,
		double% balance
	)
	{
		sumIncomeAll = 0.0;
		sumExpenseAll = 0.0;
		sumIncomeMonth = 0.0;
		sumExpenseMonth = 0.0;
		balance = 0.0;
		if (grid == nullptr) return;

		DateTime now = DateTime::Now;
		int curMonth = now.Month;
		int curYear = now.Year;
		for each(DataGridViewRow ^ row in grid->Rows)
		{
			if (row->IsNewRow) continue;

			double amount;
			if (!TryParseKwota(row->Cells[L"kwota"] ? row->Cells[L"kwota"]->Value : nullptr, amount))
				continue;

			DateTime opDate;
			bool hasDate = TryParseDate(row->Cells[L"data"] ? row->Cells[L"data"]->Value : nullptr, opDate);

			if (amount >= 0.0)
			{
				sumIncomeAll += amount;
				if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
					sumIncomeMonth += amount;
			}
			else
			{
				sumExpenseAll += amount;
				if (hasDate && opDate.Month == curMonth && opDate.Year == curYear)
					sumExpenseMonth += amount;
			}
		}
		balance = sumIncomeAll + sumExpenseAll;
	}
	void FinLogic::LoadRandomDataToGrid(DataGridView^ grid) {
		if (grid == nullptr) return;

		grid->Rows->Clear();

		Color incomeFg = Color::FromArgb(22, 163, 74);
		Color expenseFg = Color::FromArgb(220, 38, 38);

		array<String^>^ kategorie = gcnew array<String^>{
			L"Jedzenie", L"Transport", L"Mieszkanie", L"Rachunki", L"Zdrowie",
				L"Rozrywka", L"Zakupy", L"Edukacja", L"Sport", L"Inne"
		};
		Random^ rnd = gcnew Random();

		int rowsCount = 25;

		for (int i = 0; i < rowsCount; i++) {
			int past = rnd->Next(0, 90);
			DateTime dt = DateTime::Now.AddDays(-past);

			String^ typ = kategorie[rnd->Next(kategorie->Length)];

			bool isIncome = rnd->NextDouble() < 0.35;

			double base = isIncome ? rnd->Next(100, 1200) : rnd->Next(10, 500);
			double cents = rnd->NextDouble();
			double amount = Math::Round(base + cents, 2);
			if (!isIncome) amount = -amount;

			int rowIdx = grid->Rows->Add(
				dt.ToString(L"yyyy-MM-dd"),
				typ,
				amount,
				nullptr,
				nullptr
			);

			DataGridViewRow^ row = grid->Rows[rowIdx];
			DataGridViewCell^ kwCell = row->Cells[L"kwota"];
			kwCell->Style->ForeColor = amount >= 0 ? incomeFg : expenseFg;

			row->Cells[L"data"]->ToolTipText = L"Data operacji";
			row->Cells[L"typ"]->ToolTipText = L"Kategoria";
			row->Cells[L"kwota"]->ToolTipText = isIncome ? L"Wp³yw" : L"Wydatek";
		}
		try {
			grid->Sort(grid->Columns[L"data"], System::ComponentModel::ListSortDirection::Descending);
		}catch(...) {} //ignorowanko :)
	}

}

