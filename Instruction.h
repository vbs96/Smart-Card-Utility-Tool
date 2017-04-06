#pragma once


class Instruction
{
	unsigned char* standardInstruction;
	int len;

	LPCBYTE Append(const unsigned char* toAdd,int len);
	unsigned char* GetInstr() { return standardInstruction; }
	//eventual poti sa faci chestia aia cu private implementation 
public:
	Instruction(const unsigned char* stdInstruction,int len);
	~Instruction();

};
