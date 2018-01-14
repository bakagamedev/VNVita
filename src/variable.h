#pragma once

class Variable
{
public:
	enum class Type : uint8_t
	{
		Undefined,
		Integer, 
		String,
	};

private:
	Type type;
	uint32_t value;

public:
	Variable(void) : value(), type(Type::Undefined) { }
	Variable(uint32_t value, Type type) : value(value), type(type) { }

	Type GetType(void) const 		{ 	return type;	}
	uint32_t GetValue(void) const  	{ 	return value;	}
};