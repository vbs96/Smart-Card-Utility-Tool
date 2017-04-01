#include<winscard.h>
#include<iostream>
#include<string>
#include"Conection.h"
int main() {

	try {
		Connect::EstablishContext();

		auto containerReaderi = Connect::ListCardReaders();

		DWORD		protocolActiv;
		SCARDHANDLE cardHandler;
		Connect::Conectare(containerReaderi[0], protocolActiv, cardHandler);
	
		
		/*if (rv == SCARD_S_SUCCESS) {
			std::cout << "Bravo boss" << std::endl;
			SCardDisconnect(cardHandler, SCARD_LEAVE_CARD);
		}
		else if (rv == SCARD_E_NOT_READY)
			std::cout << "Nu e gata?!" << std::endl;
		else
			std::cout << "Nush";*/

		
		Connect::ClearContext();
		//Gemalto USB Smart Card Reader 0
	

	}
	catch (const ExceptieConnect& excep) {
		excep.Dispatch();
	}

	return 0;
}