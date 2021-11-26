#pragma once
#include"../../../main/src/share/common.h"

class CAbstractFactory
{
	public:
		CAbstractFactory(){

		}
		virtual ~CAbstractFactory(){

		}

		std::shared_ptr<CAbstractFactory> GetFactory(uint32_t type);
		virtual std::shared_ptr<CAbstractFactory> GetProduct(uint32_t type){
			return nullptr;
		}

		virtual void Print(){
			
		}
};

class CFactory2 : public CAbstractFactory
{
	public:
		void Print(){

		}
			
		std::shared_ptr<CAbstractFactory> GetProduct(uint32_t type);
};

class CProduct2_1 : public CFactory2
{
	public:
		void Print();
};

class CProduct2_2 : public CFactory2
{
	public:
		void Print();
};




