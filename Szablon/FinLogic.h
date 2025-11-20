#pragma once
#include <string>

namespace Szablon {

    class FinLogic
    {
    private:
        std::string name;
        std::string password;
        double stamp;

    public:
        FinLogic(std::string name, std::string password);

        std::string getName();
        std::string getPassword();

        double getStamp();
        void setStamp(double newStamp);

        // --- WALIDACJA / PARSOWANIE ---
        bool TryParseKwota(System::Object^ val, double% outVal);
        bool ValidateKwotaCell(System::String^ text, double% parsed);
        bool TryParseDate(System::Object^ val, System::DateTime% outDate);

        // --- LICZENIE SUM Z GRIDA ---
        void CalculateTotalsFrom(
            System::Windows::Forms::DataGridView^ grid,
            double% sumIncomeAll,
            double% sumExpenseAll,
            double% sumIncomeMonth,
            double% sumExpenseMonth,
            double% balance
        );

        // --- LOSOWE DANE DO GRIDA ---
        void LoadRandomDataToGrid(
            System::Windows::Forms::DataGridView^ grid
        );
    };

}
