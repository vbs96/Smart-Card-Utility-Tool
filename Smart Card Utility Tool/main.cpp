#include<winscard.h>
#include"Conection.h"
int main() {

	try {
		CConection::EstablishContext();

		auto containerReaderi = CConection::ListCardReaders();



	}
	catch (CConectionExeption *exep) {
		exep->DispatchException();
	}

	return 0;
}