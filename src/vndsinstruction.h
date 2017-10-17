#pragma once
#include "common.h"

enum class OpcodeType 
{
	None,
	//flow
	Label,
	Jump,
	Goto,
	If,
	Fi,
	Setvar,
	Gsetvar,
	Random,
	Delay,
	//assets
	Bgload,
	Setimg,
	Music,
	Sound,
	//Text
	Cleartext,
	Text,
	Choice,
};

class VNDSInstruction
{
public:
	OpcodeType Opcode;
	std::string Operand;
	
	VNDSInstruction(OpcodeType Opcode, std::string Operand)
	{
		this->Opcode = Opcode;
		this->Operand = Operand;
	}
};

