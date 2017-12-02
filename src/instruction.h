#pragma once
#include "stringviewer.h"
#include "instructionparts.h"

class InstructionType {
public:
	OpcodeType	Opcode;
	DataType 	Type;
	DataFormat 	Data;

	InstructionType() 
	{
		this->Opcode = OpcodeType::Nop;
		this->Type = DataType::Null;
	}

	InstructionType(OpcodeType OpcodeType)
	{
		this->Opcode = Opcode;
		this->Type = DataType::Null;
	}
	InstructionType(OpcodeType Opcode, DataType Type)
	{
		this->Opcode = Opcode;
		this->Type = Type;
	}

	InstructionType(OpcodeType Opcode, int Data)
	{
		this->Opcode = Opcode;
		this->Type = DataType::Int;
		this->Data.Integer = Data;
	}	
	InstructionType(OpcodeType OpcodeType, StringViewer Data)
	{
		this->Opcode = Opcode;
		this->Type = DataType::String;
		this->Data.String = Data;
	}
};