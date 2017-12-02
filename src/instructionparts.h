#pragma once

enum class OpcodeType
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