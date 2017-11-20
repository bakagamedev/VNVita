#pragma once

enum class OpcodeType
{	
	Nop = 0,
	Text,
	Delay,
	Waitui,
	Goto,
	Varselect,
	Varsetint,
	Varsetstring,
	Varpurge,
	Varcheckequals,
	Varchecknotequals,
	Varcheckgreaterthan,
	Varchecklesserthan,
	Varcheckgreaterorequals,
	Varchecklesserorequals,
};

class Parser
{
private:
	OpcodeType GetNextOpcode() { return OpcodeType::Nop;	}
public:
	void Tick();
};