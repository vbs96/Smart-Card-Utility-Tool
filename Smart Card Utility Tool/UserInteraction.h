#pragma once
#include<winscard.h>
#include"Instruction.h"

class InteractionErr
{
	public:
		virtual void Dispatch() const = 0;
};

class CUserInteraction
{

public:
	static void SendAPDU(Instruction& _instrName, const BYTE* appletAID);

};