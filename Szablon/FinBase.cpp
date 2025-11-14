#include "FinBase.h"
#include <fstream>
#include <msclr/marshal_cppstd.h>

using msclr::interop::marshal_as;

namespace Szablon {
    FinBase::FinBase() {}
    FinBase::~FinBase() {}
    std::string FinBase::getTypePath(std::string type) {
        return (type == "user") ? this->filePathUser : this->filePathUserLog;
    }
    void FinBase::setTypePath(std::string type, std::string path) {
        if (type == "user") this->filePathUser = path;
        else this->filePathUserLog = path;
    }
    bool FinBase::openDialogFile(std::string type) {
        System::Windows::Forms::OpenFileDialog^ dlg = gcnew System::Windows::Forms::OpenFileDialog();
        dlg->Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
        dlg->Title = "Select a Statistics File";

        if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            this->setTypePath(type, marshal_as<std::string>(dlg->FileName));

            std::ifstream inputFile(this->getTypePath(type));
            if (!inputFile.is_open()) {
                System::Windows::Forms::MessageBox::Show("Failed to load the file!", "Error",
                    System::Windows::Forms::MessageBoxButtons::OK,
                    System::Windows::Forms::MessageBoxIcon::Error);
                return false;
            }

            std::string line;
            while (std::getline(inputFile, line)) {
                // loadUser(line);
            }
            inputFile.close();

            System::Windows::Forms::MessageBox::Show("Statistics successfully loaded!", "Info",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Information);
            return true;
        }

        System::Windows::Forms::MessageBox::Show("No file selected!", "Info",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Information);
        return false;
    }
}
