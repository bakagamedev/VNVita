#pragma once

enum class VNDSVariableType
{
	Integer,
	String,
};

union VNDSVariableStore
{
	int Integer;
	std::string String;
}

class VNDSVariable
{
public:
	std::string Name;
	VNDSVariableStore Data;

	VNDSVariable(std::string Name, std::string Data)
	{
		this->Name = Name;
		this->Data = Data;
		this->Type = VNDSVariableType::String;
	}
	VNDSVariable(std::string Name, int Data)
	{
		this->Name = Name;
		this->Data = Data;
		this->Type = VNDSVariableType::Integer;
	}
}