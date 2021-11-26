#pragma once
#include"../share/common.h"


//适配器模式

class CAdapterPattern
{
	public:
		virtual void Play(std::string& t,std::string& f){

		}
};


class CA
{
	public:
		virtual void Play1(std::string& f){

		}

		virtual void Play2(std::string& f){

		}
};


class CA1 : public CA
{
	public:
		void Play1(std::string& f);
};

class CA2 : public CA
{
	public:
		void Play2(std::string& f);

};


class Adapter : public CAdapterPattern
{
	public:
		CA ca_;
		
		Adapter(std::string& a);
		
		

};

