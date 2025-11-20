#include "MainForm.h"
#include <regex>
#include <msclr/marshal_cppstd.h>
#include <cctype>
#include <unordered_set>
#include <algorithm>
#include "FinForm.h"
#include "AboutForm.h"
namespace Szablon {
	MainForm::MainForm(void) {
		InitializeComponent();
	}
	void MainForm::start_Click(System::Object^ sender, System::EventArgs^ e){
		std::string username = msclr::interop::marshal_as<std::string>(this->username_input->Text);
		if (username.empty() || !this->usernameValidation(username)) {
			System::String^ message = "Twój username, jest nie poprawny! \nLub nie spe³nia norm";
			MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		std::string password = msclr::interop::marshal_as<std::string>(this->password_input->Text);
		if (password.empty() || !this->passwordValidator(password)) {
			System::String^ message = 
				"Twoje has³o, jest nie poprawne! \nLub nie spe³nia nastêpuj¹cych wymagañ\n - min 8 znaków \n - max 256 znaków!";
            MessageBox::Show(message, "B£AD", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
		}
		FinLogic* finlogic = new FinLogic(username, password);
        FinForm^ fin = gcnew FinForm(finlogic);
        fin->Show();
	}
	void MainForm::clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
        this->username_input->Text = "";
        this->password_input->Text = "";
	}
	void MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
		this->Close();
	}
	void MainForm::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e){
		AboutForm^ aboutForm = gcnew AboutForm();
		aboutForm->Show();
	}
    bool MainForm::usernameValidation(const std::string& username){
        //username, nie moze byc mniejszy od 8 znakow i nie moze byc pusty oraz nie moze byc dluzszy niz 255 znakow
        if (username.empty() || username.size() > 254 || username.size() < 8) return false;
        return true;
    }
    bool MainForm::passwordValidator(const std::string& password){
        if (password.size() < 8 || password.size() > 256) return false;
        return true;
    }
}
