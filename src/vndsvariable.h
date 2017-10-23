#pragma once
#include "common.h"

enum class VNDSVariableType
{
	Integer,
};

union VNDSVariableData {
	int Integer;
};

class VNDSVariable
{
public:
	std::string Name;
	VNDSVariableData Data;
	VNDSVariableType Type;

	VNDSVariable(std::string Name, int Data)
	{
		this->Name = Name;
		this->Data.Integer = Data;
		this->Type = VNDSVariableType::Integer;
	}
};

inline bool operator==(const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 
	if((lhs.Type == VNDSVariableType::Integer) && (rhs.Type == VNDSVariableType::Integer))
		return lhs.Data.Integer == rhs.Data.Integer; 
	return false;
}
inline bool operator!=(const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 
	return !(lhs == rhs);
}
inline bool operator< (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.Type == VNDSVariableType::Integer) && (rhs.Type == VNDSVariableType::Integer))
		return lhs.Data.Integer < rhs.Data.Integer;
	return false;
}
inline bool operator> (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.Type == VNDSVariableType::Integer) && (rhs.Type == VNDSVariableType::Integer))
		return lhs.Data.Integer > rhs.Data.Integer;
	return false;
}
inline bool operator<= (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.Type == VNDSVariableType::Integer) && (rhs.Type == VNDSVariableType::Integer))
		return lhs.Data.Integer <= rhs.Data.Integer;
	return false;
}
inline bool operator>= (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.Type == VNDSVariableType::Integer) && (rhs.Type == VNDSVariableType::Integer))
		return lhs.Data.Integer >= rhs.Data.Integer;
	return false;
}