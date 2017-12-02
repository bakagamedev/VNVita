#pragma once
#include "stringviewer.h"
#include "instructionparts.h"

class InstructionType {
public:
	OperandType Operand;
	DataType 	Type;
	DataFormat 	Data;

	InstructionType() 
	{
		this->Operand = OperandType::Nop;
		this->Type = DataType::Null;
	}

	InstructionType(OperandType Operand)
	{
		this->Operand = Operand;
		this->Type = DataType::Null;
	}
	InstructionType(OperandType Operand, DataType Type)
	{
		this->Operand = Operand;
		this->Type = Type;
	}

	InstructionType(OperandType Operand, int Data)
	{
		this->Operand = Operand;
		this->Type = DataType::Int;
		this->Data.Integer = Data;
	}	
	InstructionType(OperandType Operand, StringViewer Data)
	{
		this->Operand = Operand;
		this->Type = DataType::String;
		this->Data.String = Data;
	}
};