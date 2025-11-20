#include "FinLogic.h"
#include "FinBase.h"
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
}

