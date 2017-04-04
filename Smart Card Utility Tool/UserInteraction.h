#pragma once
#include<winscard.h>
#include"Instruction.h"

class CUserInteraction
{
public:
	template<class BYTE>
	void SendAPDU(CInstruction<BYTE>, char*AID_applet)
	{

	}
};