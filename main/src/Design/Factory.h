#pragma once
#include<iostream>
#include<memory>
#include"AbstractFactory.h"
using namespace std;


//工厂模式
class CFactoryPattern : public CAbstractFactory
{
	public:
		CFactoryPattern(){

		}

		~CFactoryPattern(){

		}


		void Print(){

		}

		std::shared_ptr<CAbstractFactory> GetProduct(uint32_t type);

};



class CProduct1 : public CFactoryPattern
{
	public:
		void Print();

};

class CProduct2 : public CFactoryPattern
{
	public:
		void Print();

};


