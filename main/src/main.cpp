#include<iostream>
#include<vector>
#include<string.h>
#include <json/json.h>
#include "TestA.h"
#include "TestB.h"
#include <stdint.h>
#include <sys/time.h>
#include "InputControl.h"
#include<map>
#include "logic/CurlCommon.h"
using namespace std;

/*
struct CmpByKeyLength {
    bool operator()(const int k1, const int k2)const {
	        return k1 < k2;
    }
};
*/
int main(int argc,char **argv)	 
{


	// get 请求
	string strURL = "http://www.baidu.com";
	string strResponse;
	CURLcode nRes = CommonTools::HttpGet(strURL, strResponse,300);
	size_t nSrcLength = strResponse.length();
	cout << "aa:"  << nSrcLength << " Res:" << nRes << endl;

	cout << "test:" << strResponse << endl;


	/*	
	PrintMap();
    while (1) {	
			if (InputControlMain()){ 
				//break; 
			}//当按下ESC时循环，ESC键的键值时27.
			PrintMap();
	} 
	*/

	return 0;
}
