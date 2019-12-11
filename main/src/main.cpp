#include<iostream>
#include<vector>
#include<string.h>
#include <json/json.h>
#include "TestA.h"
#include "TestB.h"
#include <stdint.h>

int main()	 
{
/*
		std::vector<std::string> a;
		a.push_back("aaa");
		std::cout<<"size = " << a.size() <<std::endl;	
		for(auto i : a)
		{
			std::cout<< *i << std::endl;
		}
		std::cout<<"Hello word!"<<std::endl;
*/
/*
	Json::Value root;
    Json::Value arrayObj;
    Json::Value item;
    for (int i=0; i<10; i++)
    {
		item["key"] = i;
		arrayObj.append(item);
    }

    root["key1"] =  "value1";
    root["key2"] =  "value2";
    root["array"] = arrayObj;
    root.toStyledString();
    std::string out = root.toStyledString();
    std::cout << out << std::endl;


    Json::Reader reader;
    Json::Value value;

    if (reader.parse(out, value))
    {
		std::string out1 = value["key1"].asString();
		std::cout << out1 << std::endl;
		const Json::Value arrayObj = value["array"];
		for (int i=0;i<arrayObj.size();i++)
		{
			int out2 = arrayObj[i]["key"].asInt();
			std::cout << out2 << std::endl;
		}
    }
*/   

	B *a =new B();
	uint32_t b = a->GetB();
	std::cout << "b = " << b << std::endl;
	a->SetB(10);
	b = a->GetB();
	std::cout << "b = " << b << std::endl;

/*
	std::vector<int>  Avec;
	for(int i = 0;i < 10;i++)
	{
		Avec.push_back(i);
	}

	for(int a : Avec)
	{
		std::cout << a << std::endl;
	}
*/
	return 0;
}
