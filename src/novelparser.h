#pragma once
#include "instruction.h"

class Parser
{
private:
	InstructionType GetNextInstruction() { return InstructionType; }
public:
	void Tick();
};