#include "AbstractFactory.h"
#include "Factory.h"


std::shared_ptr<CAbstractFactory> CAbstractFactory::GetFactory(uint32_t type)
{
	switch(type)
	{
		case 1:
			{
				return std::make_shared<CFactoryPattern>();
				//return nullptr;
			}
		case 2:
			{
				return std::make_shared<CFactory2>();
			}
		default:
			return nullptr;
	}
}


std::shared_ptr<CAbstractFactory> CFactory2::GetProduct(uint32_t type)
{
	switch(type)
	{
		case 1:
			{
				return std::make_shared<CProduct2_1>();
			}
		case 2:
			{
				return std::make_shared<CProduct2_2>();
			}
		default:
			return nullptr;
	}
}


void CProduct2_1::Print()
{
	cout << "CProduct2_1 Print" << endl;
}


void CProduct2_2::Print()
{
	cout << "CProduct2_2 Print" << endl;
}





