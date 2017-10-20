#pragma once
#include "common.h"
#include "charviewer.h"

enum class OpcodeType 
{
	None,
	End,
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

enum class OperandType
{
	Integer,
	String,
};

class VNDSInstruction
{
public:
	/*
	OpcodeType Opcode;

	union {
		TypeInt,
		TypeViewer,
	} Operand;
	
	VNDSInstruction(OpcodeType Opcode)
	{
		this->Opcode = Opcode;
		this->Operand = Operand;
	}
	*/
};