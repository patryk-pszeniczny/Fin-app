#pragma once
#include <string>

namespace Szablon {
    class FinBase {
    public:
        FinBase();
        ~FinBase();

        std::string getTypePath(std::string type);
        void setTypePath(std::string type, std::string path);
        bool openDialogFile(std::string type);

    private:
        std::string filePathUser;
        std::string filePathUserLog;
    };
}
