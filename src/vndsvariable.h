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

private:


public:
	VNDSVariableData Data;
	VNDSVariableType Type;

	VNDSVariable(int Data)
	{
		this->Data.Integer = Data;
		this->Type = VNDSVariableType::Integer;
	}

	bool IsInteger() const
	{
		return(this->Type == VNDSVariableType::Integer);
	}
};
inline bool operator==(const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 
	if((lhs.IsInteger()) && (rhs.IsInteger()))
		return lhs.Data.Integer == rhs.Data.Integer; 
	return false;
}
inline bool operator!=(const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 
	return !(lhs == rhs);
}
inline bool operator< (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.IsInteger()) && (rhs.IsInteger()))
		return lhs.Data.Integer < rhs.Data.Integer;
	return false;
}
inline bool operator> (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.IsInteger()) && (rhs.IsInteger()))
		return lhs.Data.Integer > rhs.Data.Integer;
	return false;
}
inline bool operator<= (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.IsInteger()) && (rhs.IsInteger()))
		return lhs.Data.Integer <= rhs.Data.Integer;
	return false;
}
inline bool operator>= (const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 

	if((lhs.IsInteger()) && (rhs.IsInteger()))
		return lhs.Data.Integer >= rhs.Data.Integer;
	return false;
}