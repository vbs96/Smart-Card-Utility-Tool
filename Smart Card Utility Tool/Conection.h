#pragma once
#include<vector>
#include<winscard.h>

class ExceptieConnect{
	public:
		virtual void Dispatch() const = 0;
};

class Connect
{
	struct pimpl;
	static pimpl* impl;

	Connect();
	~Connect();
	static Connect* body;
	static Connect* GetInstance();
public:

	static SCARDCONTEXT&	GetContext();

	static void						EstablishContext();
	static std::vector<std::string> ListCardReaders	();
	static void						Conectare		(const std::string&, DWORD&, SCARDHANDLE&);
	static void						ClearContext	();
	static void						Deconectare		(const SCARDHANDLE&);
};

