#pragma once
#include <stdint.h>


int map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

namespace GameMap
{

	void PrintMap()
	{
		for(int i = 0;i<10;i ++) {
			for(int j = 0; j< 10;j++)
			{
				switch(map[i][j])
				{
					case 0:
						std::cout << " " << " ";
						break;
					case 1:
						std::cout << "■" ;
						break;
					case 2:
						std::cout << "★";
						break;
					default:
						break;
				}       
			}   
			std::cout << std::endl;
		}   
	}

}






