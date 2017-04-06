#pragma once
#include<winscard.h>
struct {
	BYTE
		bCla,   // the instruction class
		bIns,   // the instruction code 
		bP1,    // parameter to the instruction
		bP2,    // parameter to the instruction
		bP3;    // size of I/O transfer
};