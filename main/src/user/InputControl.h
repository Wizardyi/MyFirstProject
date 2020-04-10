#pragma once
#include <termio.h>
#include <stdio.h> 
#include "GameMap.h"
int scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	 
	in = getchar();
	 
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}


bool InputControlMain(){
	bool bk = false;
	auto ch = scanKeyboard();//获取按下的键值
	
	switch(ch)
	{
		case 27:
			bk = true;
			break;
		default:
			std::cout << ch << std::endl;
			break;
	}	

	return bk;
}
