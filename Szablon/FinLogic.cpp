#include "FinLogic.h"
#include "FinBase.h"
namespace Szablon {
	FinLogic::FinLogic() {

	}

	bool FinLogic::isUserLoaded() {
		return !this->finbase->getTypePath("user").empty();
	}

	bool FinLogic::isUserLogLoaded() {
		return !this->finbase->getTypePath("user_log").empty();
	}

	FinBase* FinLogic::getFinBase(){
		return this->finbase;
	}
	void FinLogic::setFinBase(FinBase* base) {
		this->finbase = base;
	}
}

