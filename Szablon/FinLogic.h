#pragma once

#include <string>
#include <vector>
#include <random>
#include <array>
#include <cctype>
#include <cstring>
#include "FinBase.h"
namespace Szablon {
    class FinLogic {
    public:
        FinLogic(std::string name, std::string password);

		std::string getName();
        std::string getPassword();
        
        double getStamp();
		void setStamp(double newStamp);
    private:
        std::string name;
        std::string password; // :) full protected password
        
        double stamp; //próg 

        //bool TryParseKwota(std::string val, double% outVal);
        //bool ValidateKwotaCell(std::string val, double% parsed);
        //bool TryParseDate(std::string val, System::DateTime% outDate);

        //void CalculateTotalsFrom
    };
}
