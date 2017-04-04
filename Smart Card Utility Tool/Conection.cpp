#include "Conection.h"
#include <iostream>
//#include <vector>
//#include <string>

//
//
// Exception clases
class BadEstablishContext :public ExceptieConnect {
public:
	void Dispatch() const;
};
class BadReaderList :public ExceptieConnect {
	LONG returnValue;
public:
	BadReaderList(LONG value) :returnValue{ value } {}
	void Dispatch()const;
};
class BadMemoryDealloc :public ExceptieConnect {
public:
	void Dispatch()const;
};
class BadConnection :public ExceptieConnect {
	LONG controlValue;
	public:
		BadConnection(LONG _x) :controlValue{ _x } {}
		~BadConnection() {}
		void Dispatch()const;
};
class BadDecconect :public ExceptieConnect {
	public:
		void Dispatch()const;
};

void BadEstablishContext::Dispatch()const {
	std::cout << "Nu s-a facut cum trebuie establish conexion." << std::endl;
}
void BadReaderList::Dispatch()const {
	if (returnValue == SCARD_E_NO_READERS_AVAILABLE) {
		std::cout << "Nu s-a detectat nici un cititor de carduri." << std::endl;
		//cel mai probabil un exit(1) sau ceva...
	}
	else {
		std::cout << "Eroare necunoscuta la detectarea readerelor." << std::endl;
		//iarasi un exit sau ceva de genul asta...
	}
}
void BadMemoryDealloc::Dispatch()const {
	std::cout << "Nu s-a putut dezaloca memorie undeva." << std::endl;
}
void BadConnection::Dispatch()const{
	if (controlValue == SCARD_E_NOT_READY)
		std::cout << "Readerul nu s-a putut connecta la smart card." << std::endl;
	else
		std::cout << "Eroare necunoscuta la incercarea de connectare la smart card." << std::endl;
}
void BadDecconect::Dispatch()const {
	std::cout << "Nu s-a deconectat corespunzator smart cardul." << std::endl;
}

//
//
//

typedef std::vector<std::string> containerType;

//
//
// Implementation

Connect::pimpl*	Connect::impl;
Connect*			Connect::body;
struct Connect::pimpl{

	SCARDCONTEXT handleContext;
	
	void _implEstablishContext(SCARDCONTEXT&);
	containerType _implListCardReaders();
	void _implConnectSCard(const std::string&, DWORD&, SCARDHANDLE&);
};

void Connect::pimpl::_implEstablishContext(SCARDCONTEXT& x) {
	
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

containerType Connect::pimpl::_implListCardReaders() {

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

void Connect::pimpl::_implConnectSCard(const std::string& nume, DWORD& prot, SCARDHANDLE& sch) {

	LONG controlValue;

	controlValue = SCardConnect(handleContext,
		(LPCTSTR)nume.c_str(),
		SCARD_SHARE_EXCLUSIVE,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&sch,
		&prot);

	if (controlValue != SCARD_S_SUCCESS)
		throw new BadConnection{ controlValue };
}

//
//
//

Connect::Connect()
{
	impl = new pimpl{};
}


Connect::~Connect()
{
	delete impl;
}

Connect* Connect::GetInstance() {

	if (body == nullptr)
		body = new Connect{};
	return body;
}


//
//
// User interface

void Connect::EstablishContext(){
	impl->_implEstablishContext(impl->handleContext);
}

containerType Connect::ListCardReaders() {
	return impl->_implListCardReaders();
}

void Connect::Conectare(const std::string& _numeReader, DWORD& _protocolActiv,SCARDHANDLE& _sch) {
	 impl->_implConnectSCard(_numeReader, _protocolActiv, _sch);
}

void Connect::ClearContext() {
	SCardReleaseContext(impl->handleContext);
}

void Connect::Deconectare(const SCARDHANDLE& sch) {
	LONG controlValue = SCardDisconnect(sch, SCARD_LEAVE_CARD);
	//oricum e by default chestia de mai sus
	//eventual daca vreau sa o modific ulterior
	if (controlValue != SCARD_S_SUCCESS)
		throw	BadDecconect{};
}

//
//
//