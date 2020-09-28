#pragma once
#ifndef _A_H
#define _A_H

#include <stdint.h>
#include <vector>

extern std::vector<uint32_t> vec;

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

	uint32_t test();

	private:
		uint32_t a;
	
};















#endif
