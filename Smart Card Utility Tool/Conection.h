#pragma once
#include<vector>

class CConectionExeption{
	public:
		virtual void DispatchException() = 0;
};

class CConection
{
	struct pimpl;
	static pimpl* impl;

	CConection();
	~CConection();
	static CConection* body;
	static CConection* GetInstance();
public:
	
	

	//static bool Conectare();
	static void EstablishContext();
	static std::vector<std::string> ListCardReaders();
};

