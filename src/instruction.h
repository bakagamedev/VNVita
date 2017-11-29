#pragma once
#include "stringviewer.h"

enum class OperandType
{	
	Nop,
};

enum class DataType
{
	Null,
	Int,
	String,
}

class InstructionType {
public:
	OperandType Operand;
	DataType 	Type;
	union Data
	{
		int Integer,
		StringViewer String,
	};

	InstructionType() 
	{
		this->Operand = OperandType::Nop;
		this->Data = DataType::Null;
	} = default;

	InstructionType(OperandType Operand)
	{
		this->Operand = OperandType::Operand;
		this->Type = DataType::Null;
	}
	InstructionType(OperandType Operand, DataType Type)
	{
		this->Operand = OperandType::Operand;
		this->Type = Type;
	}

	InstructionType(OperandType Operand, int Data)
	{
		this->Operand = Operand;
		this->Type = DataType::Int;
		this->Data = Data;
	}	
	InstructionType(OperandType Operand, StringViewer Data)
	{
		this->Operand = Operand;
		this->Type = DataType::String;
		this->Data = Data;
	}
}
