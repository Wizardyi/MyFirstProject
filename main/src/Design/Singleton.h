#pragma once
#include"../share/common.h"


class Singleton
{
	public:
		static Singleton* GetInstance(){
			if(_instance == nullptr){
				_instance = new Singleton();
			}

			return _instance;
		}

	private:
		Singleton(){
			
		}

		char a[10000];
		static Singleton* _instance;

};

Singleton* Singleton::_instance = nullptr;

