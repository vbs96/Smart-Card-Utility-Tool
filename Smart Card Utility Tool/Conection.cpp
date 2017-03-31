#include "Conection.h"
#include <winscard.h>
#include <iostream>
//#include <vector>
//#include <string>

//
// Exception clases
class BadEstablishContext :public CConectionExeption {
public:
	void DispatchException();
};
class BadReaderList :public CConectionExeption {
	LONG returnValue;
public:
	BadReaderList(LONG value) :returnValue{ value } {}
	void DispatchException();
};
class BadMemoryDealloc :public CConectionExeption {
public:
	void DispatchException();
};

void BadEstablishContext::DispatchException() {
	std::cout << "Nu s-a facut cum trebuie establish conexion." << std::endl;
}
void BadReaderList::DispatchException() {
	if (returnValue == SCARD_E_NO_READERS_AVAILABLE) {
		std::cout << "Nu s-a detectat nici un cititor de carduri." << std::endl;
		//cel mai probabil un exit(1) sau ceva...
	}
	else {
		std::cout << "Eroare necunoscuta la detectarea readerelor." << std::endl;
		//iarasi un exit sau ceva de genul asta...
	}
}
void BadMemoryDealloc::DispatchException() {
	std::cout << "Nu s-a putut dezaloca memorie undeva." << std::endl;
}
//
//

typedef std::vector<std::string> containerType;

//
//
// Implementation
CConection::pimpl* CConection::impl;
CConection* CConection::body;
struct CConection::pimpl{

	SCARDCONTEXT handleContext;
	
	void _implEstablishContext(SCARDCONTEXT&);
	containerType _implListCardReaders();
};

void CConection::pimpl::_implEstablishContext(SCARDCONTEXT& x) {


	
	LONG returnValue;
	SCARDCONTEXT localHandleContext = NULL;

	returnValue = SCardEstablishContext(SCARD_SCOPE_USER,
		NULL,
		NULL,
		&localHandleContext);

	if (returnValue != SCARD_S_SUCCESS) {
		throw new BadEstablishContext{};
	}
	GetInstance()->impl->handleContext = localHandleContext;
}

containerType CConection::pimpl::_implListCardReaders() {

	containerType toReturn;
	LONG controlValue;
	DWORD len = SCARD_AUTOALLOCATE;
	LPTSTR buffer = NULL;

	controlValue = SCardListReaders(handleContext,
		NULL,
		(LPTSTR)&buffer,
		&len);
			
	if (controlValue != SCARD_S_SUCCESS) {
		throw new BadReaderList{ controlValue };
	}
	else {
		LPTSTR toParse = buffer;
		while (*toParse != '\0') {
			std::string aux{ toParse };
			toReturn.push_back(aux);
			toParse += strlen(toParse) + 1;

		}
		LONG controlValue1 = SCardFreeMemory(handleContext, buffer);
		if (controlValue1 != SCARD_S_SUCCESS)
			throw new BadMemoryDealloc{};
		return toReturn;
	}
}

//
//
//

CConection::CConection()
{
	impl = new pimpl{};
}


CConection::~CConection()
{
	delete impl;
}

CConection* CConection::GetInstance() {

	if (body == nullptr)
		body = new CConection{};
	return body;
}


//
//
// User interface

void CConection::EstablishContext(){
	impl->_implEstablishContext(impl->handleContext);
}

containerType CConection::ListCardReaders() {
	return impl->_implListCardReaders();
}

