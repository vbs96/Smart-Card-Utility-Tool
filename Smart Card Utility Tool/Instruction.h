#pragma once
#include<winscard.h>
#include<vector>

class Instruction
{
	BYTE* standardInstruction;
	int len;

public:
	Instruction(const BYTE* _stdInstruction,int _len);
	LPCBYTE Append(const BYTE* toAdd,int len);
	BYTE* GetInstr() { return standardInstruction; }
	~Instruction();

};
