#include<iostream>
#include<vector>
#include<string.h>
#include <json/json.h>
#include "TestA.h"
#include "TestB.h"
#include <stdint.h>
#include <sys/time.h>
#include "InputControl.h"

int main(int argc,char **argv)	 
{
	
    while (1) {	
			PrintMap();
			if (InputControlMain()){ break; }//当按下ESC时循环，ESC键的键值时27.
	} 
	
	return 0;
}
