#include "MainForm.h"
#include <regex>
#include <msclr/marshal_cppstd.h>
#include <cctype>
#include <unordered_set>
#include <algorithm>
#include "FinForm.h"
namespace Szablon {
	MainForm::MainForm(void) {
		InitializeComponent();
        this->finlogic = new FinLogic();
        this->finlogic->setFinBase(new FinBase());
	}
	void MainForm::start_Click(System::Object^ sender, System::EventArgs^ e){
        if (!this->finlogic->isUserLoaded()) {
            System::String^ message = "Za³aduj bazê uzytkowników";
            MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        if (!this->finlogic->isUserLogLoaded()) {
            System::String^ message = "Za³aduj bazê z logami u¿ytkowników";
            MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
		std::string email = msclr::interop::marshal_as<std::string>(this->email_input->Text);
		if (email.empty() || !this->emailValidator(email)) {
			System::String^ message = "Twój email, jest nie poprawny! \nLub nie spe³nia norm";
			MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		std::string password = msclr::interop::marshal_as<std::string>(this->password_input->Text);
		if (password.empty() || !this->passwordValidator(password)) {
			System::String^ message = 
				"Twoje has³o, jest nie poprawne! \nLub nie spe³nia nastêpuj¹cych wymagañ\n - min 8 znaków \n - max 256 znaków \n - brak spacji \n - min jeden znak specjalny!";
            MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
		}

	}
    void MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
    {
        FinForm^ fin = gcnew FinForm();
        fin->Show();
    }
	void MainForm::clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
        this->email_input->Text = "";
        this->password_input->Text = "";
	}
	void MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
		this->Close();
	}
	void MainForm::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
		System::String^ message = "test";
		MessageBox::Show(message, "Informacje", MessageBoxButtons::OK, MessageBoxIcon::Information);
		//AboutForm^ aboutForm = gcnew AboutForm();
		//aboutForm->Show();
	}
    static std::string trim(const std::string& s) {
        size_t a = 0, b = s.size();
        while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
        while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1]))) --b;
        return s.substr(a, b - a);
    }
    bool MainForm::emailValidator(const std::string& email){
        const std::string s = trim(email);
        if (s.empty() || s.size() > 254) return false;
        static const std::regex pattern(
            R"(^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@(?:[A-Za-z0-9-]+\.)+[A-Za-z]{2,}$)",
            std::regex::ECMAScript
        );
        return std::regex_match(s, pattern);
    }
    bool MainForm::passwordValidator(const std::string& password){
        if (password.size() < 8 || password.size() > 256) return false;
        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
        int seen[256] = { 0 };
        int distinctCount = 0;
        unsigned char prev = 0;
        int repeat = 1;
        for (unsigned char ch : password){
            if (std::isspace(ch)) return false;
            if (std::islower(ch)) hasLower = true;
            if (std::isupper(ch)) hasUpper = true;
            if (std::isdigit(ch)) hasDigit = true;
            if (std::ispunct(ch)) hasSpecial = true;
            if (ch == prev) {
                if (++repeat >= 3) return false;
            }else {
                prev = ch;
                repeat = 1;
            }

            if (!seen[ch]) {
                seen[ch] = 1;
                ++distinctCount;
            }
        }
        if (!(hasLower && hasUpper && hasDigit && hasSpecial)) return false;
        if (distinctCount < 4) return false;
        std::string lower;
        lower.reserve(password.size());
        for (unsigned char ch : password) lower.push_back(static_cast<char>(std::tolower(ch)));

        static const std::unordered_set<std::string> weakList = {
            "password", "password1!", "qwertyui", "qwerty123",
            "12345678", "123456789", "11111111", "haslo123"
        };
        if (weakList.count(lower) > 0) return false;
        if (lower.find("password") != std::string::npos) return false;
        if (lower.find("haslo") != std::string::npos) return false;
        return true;
    }
    void MainForm::usersToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
        this->finlogic->getFinBase()->openDialogFile("user");
    }
    void MainForm::userLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
        this->finlogic->getFinBase()->openDialogFile("user_log");
    }
    void MainForm::setFinLogic(FinLogic* finlogic) {
        this->finlogic = finlogic;
    }
    FinLogic* MainForm::getFinLogic() {
        return this->finlogic;
    }
}
