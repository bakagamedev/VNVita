#pragma once
#include "common.h"
#include <string>

enum class VNDSVariableType
{
	Integer,
	String,
};

struct VNDSVariableData {	//Should be a union.
	int Integer;
	std::string String;
};

class VNDSVariable
{
public:
	VNDSVariableData Data;
	VNDSVariableType Type;

	VNDSVariable(void) {}; 
	VNDSVariable(int Data)
	{
		this->Data.Integer = Data;
		this->Type = VNDSVariableType::Integer;
	}
	VNDSVariable(std::string Data)
	{
		this->Data.String = Data;
		this->Type = VNDSVariableType::String;
	}

	bool IsInteger() const
	{
		return(this->Type == VNDSVariableType::Integer);
	}
	bool IsString()  const
	{
		return(this->Type ==  VNDSVariableType::String);
	}
};

inline VNDSVariable operator+=(const VNDSVariable& Var, const int Value)
{
	switch(Var.Type)
	{
		case VNDSVariableType::Integer:	return VNDSVariable(Var.Data.Integer + Value);	break;
		case VNDSVariableType::String:	return VNDSVariable(Var.Data.String + std::to_string(Value)); break;
		default: return Var;
	}
}
inline VNDSVariable operator+=(const VNDSVariable& Var, const std::string Value)
{
	switch(Var.Type)
	{
		case VNDSVariableType::Integer:
		{
			int TempInt;
			try{	TempInt = std::stoi(Value);	}
			catch(...)	{	TempInt = 0;	}
			return VNDSVariable(Var.Data.Integer + TempInt);
		}; break;
		case VNDSVariableType::String:	VNDSVariable(Var.Data.String + Value); break;
		default: return Var;
	}
}

inline VNDSVariable operator-=(const VNDSVariable& Var, const int Value)
{
	if(Var.IsInteger())
		return VNDSVariable(Var.Data.Integer - Value);
	return Var;	//Invalid
}
inline VNDSVariable operator-=(const VNDSVariable& Var, const std::string Value)
{
	//stoi from value string maybe
	return Var;	//Invalid
}

inline VNDSVariable operator*=(const VNDSVariable& Var, const int Value)
{
	if(Var.IsInteger())
	{
		return VNDSVariable(Var.Data.Integer * Value);
	}
	return Var; 
}
inline VNDSVariable operator*=(const VNDSVariable& Var, const std::string Value)
{
	return Var;
}

inline VNDSVariable operator/=(const VNDSVariable& Var, const int Value)
{
	if(Var.IsInteger())
		return VNDSVariable(Var.Data.Integer / Value);
	return Var;
}
inline VNDSVariable operator/=(const VNDSVariable& Var, const std::string Value)
{
	return Var;
}

inline bool operator==(const VNDSVariable& lhs, const VNDSVariable& rhs)
{ 
	if((lhs.IsInteger()) && (rhs.IsInteger()))	//I == I
	{
		return lhs.Data.Integer == rhs.Data.Integer; 
	}
	if((lhs.IsString()) && (rhs.IsString()))	//S == S
	{
		return lhs.Data.String == rhs.Data.String;
	}
	if((lhs.IsInteger()) && (rhs.IsString()))	//I == S
	{
		int RhsInt = std::stoi(rhs.Data.String);
		return lhs.Data.Integer == RhsInt;
	}
	if((lhs.IsString()) && (rhs.IsInteger()))	//S == I
	{
		int LhsInt = std::stoi(lhs.Data.String);
		return LhsInt == rhs.Data.Integer;
	}
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