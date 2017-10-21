#pragma once
#include "stringviewer.h"
#include "common.h"

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

enum class VNDSInstructionOperandType
{
	Integer,
	String,
};

union VNDSInstructionOperand {
	int Integer;
	StringViewer String;
};

class VNDSInstruction
{
public:
	OpcodeType Opcode;
	VNDSInstructionOperand Operand;
	VNDSInstructionOperandType OperandType;
	
	VNDSInstruction(OpcodeType Opcode, StringViewer Operand)
	{
		this->Opcode = Opcode;
		this->Operand.String = Operand;
		this->OperandType = VNDSInstructionOperandType::Integer;
	}
	VNDSInstruction(OpcodeType Opcode, int Operand)
	{
		this->Opcode = Opcode;
		this->Operand.Integer = Operand;
		this->OperandType = VNDSInstructionOperandType::String;
	}
	
};