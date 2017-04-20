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
	
		SCARD_IO_REQUEST pioSendPci;
		switch (protocolActiv)
		{
		case SCARD_PROTOCOL_T0:
			pioSendPci = *SCARD_PCI_T0;
			break;

		case SCARD_PROTOCOL_T1:
			pioSendPci = *SCARD_PCI_T1;
			break;
		}
		SCardTransmit(cardHandler,pioSendPci,)

		
		Connect::ClearContext();
		Connect::Deconectare(cardHandler);
		//Gemalto USB Smart Card Reader 0
	

	}
	catch (const ExceptieConnect& excep) {
		excep.Dispatch();
	}

	return 0;
}