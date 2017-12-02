#pragma once

enum class OperandType
{	
	Nop,
};

enum class DataType
{
	Null,
	Int,
	String,
};

union DataFormat
{
	int Integer;
	StringViewer String;
};