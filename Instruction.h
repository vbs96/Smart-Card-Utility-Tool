#pragma once


class Instruction
{
	unsigned char* standardInstruction;
	int len;

public:
	Instruction(const unsigned char* stdInstruction,int len);
	LPCBYTE Append(const unsigned char* toAdd,int len);
	unsigned char* GetInstr() { return standardInstruction; }
	~Instruction();

};
