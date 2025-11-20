#include "AboutForm.h"
namespace Szablon {
	void Szablon::AboutForm::AboutForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if(e->KeyChar == 'm' || e->KeyChar == 'M') {
			this->Close();
		}
	}

}

