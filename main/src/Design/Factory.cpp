#include"Factory.h"


std::shared_ptr<CAbstractFactory> CFactoryPattern::GetProduct(uint32_t type)
{
	switch(type)
	{
		case 1:
			{
				return std::make_shared<CProduct1>();
			}
		case 2:
			{
				return std::make_shared<CProduct2>();
			}
		default:
			return nullptr;
	}


}


void CProduct1::Print()
{
	cout << "CProduct1 Print" << endl;
}

void CProduct2::Print()
{
	cout << "CProduct2 Print" << endl;
}




