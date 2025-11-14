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
        FinLogic();
        bool isUserLoaded();
        bool isUserLogLoaded();
        FinBase* getFinBase();
        void setFinBase(FinBase* base);
    private:
        FinBase* finbase;
    };
}
