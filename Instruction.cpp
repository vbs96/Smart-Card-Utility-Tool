#include"Instruction.h"
#include <windows.h>
Instruction::Instruction(const BYTE* _stdInstruction,int _len)
{
	BYTE i = 0;
	len = _len;
	standardInstruction = new BYTE[len];
		for (i = 0; i < len; i++)
	{
		standardInstruction[i]=_stdInstruction[i];
	}
}

LPCBYTE Instruction::Append(const BYTE* toAdd,int _len)
{
	BYTE i = 0;
	BYTE* result = new BYTE[len + _len];
	for (i = 0; i < len; i++)
	{
		result[i] = standardInstruction[i];
	}
	for (i =len; i < len + _len; i++)
	{
		result[i] = toAdd[i];
	}


	 return result;
	
}

Instruction::~Instruction()
{
	if (NULL != standardInstruction)
	{
		delete[]standardInstruction;
		standardInstruction = NULL;
		len = 0;
	}

}
