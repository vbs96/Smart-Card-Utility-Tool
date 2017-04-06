#include"UserInteraction.h"
#include<iostream>



//Exceptions
class BadSCardTransmit : public InteractionErr
{
	LONG returnValue;
public:
	BadSCardTransmit(LONG value) :returnValue{ value } {}
	void Dispatch()const;
};


///
void BadSCardTransmit::Dispatch()const {
	if (returnValue == SCARD_E_INSUFFICIENT_BUFFER) {
		std::cout << " RecvLength was not large enough for the card response." << std::endl;
		//The expected size is now in cbRecvLength -----spun si asta?
	}
	if (returnValue == SCARD_E_INVALID_HANDLE) {
		std::cout << "Invalid hCard handle " << std::endl;
	}
	if (returnValue == SCARD_E_INVALID_PARAMETER) {
		std::cout << "Invalid parameter" << std::endl;
	}
	if (returnValue == SCARD_E_INVALID_VALUE) {
		std::cout << "  Invalid Protocol/reader name  " << std::endl;
	}
	if (returnValue == SCARD_E_NO_SERVICE) {
		std::cout << "	The server is not running " << std::endl;
	}
	if (returnValue == SCARD_E_NOT_TRANSACTED) {
		std::cout << " APDU exchange not successful" << std::endl;
	}
	if (returnValue == SCARD_E_PROTO_MISMATCH) {
		std::cout << " Connect protocol is different than desired " << std::endl;
	}
	if (returnValue == SCARD_E_READER_UNAVAILABLE) {
		std::cout << " The reader has been removed  " << std::endl;
	}
	if (returnValue == SCARD_F_COMM_ERROR) {
		std::cout << " An internal communications error has been detected   " << std::endl;
	}
	if (returnValue == SCARD_W_RESET_CARD) {
		std::cout << "The card has been reset by another application   " << std::endl;
	}
	if (returnValue == SCARD_W_REMOVED_CARD) {
		std::cout << "The card has been removed from the reader   " << std::endl;
	}
	else {
		std::cout << " Unknown APDU sending error." << std::endl;
	}
}
static void SendAPDU( Instruction& _instrName, const BYTE* appletAID)
{

	LONG result;
	SCARDHANDLE hCard;
	LPSCARD_IO_REQUEST recvPci;
	LPCBYTE bufToSend = _instrName.Append(appletAID, sizeof(appletAID));
	BYTE  bufToReceive[10];
	DWORD recvLen = sizeof(bufToReceive);
	
	result = SCardTransmit(
		hCard,
		SCARD_PCI_T0,
		bufToSend,
		sizeof(bufToSend),
		recvPci,
	   bufToReceive,
		&recvLen);

	if (result != SCARD_S_SUCCESS)
	{
		throw new BadSCardTransmit{ result };
	}

}
