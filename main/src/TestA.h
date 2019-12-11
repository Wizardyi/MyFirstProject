#pragma once
#ifndef _A_H
#define _A_H

#include <stdint.h>



class A{
	public:
		A(){
			a = 0;
		};
	void SetA(uint32_t value){
			a = value;
	}

	uint32_t GetA(){
		return a;
	}

	private:
		uint32_t a;
	
};















#endif
