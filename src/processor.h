#pragma once
#include <stack>
#include <vector>
#include <string>
#include <map>
#include "header.h"
#include "variable.h"
#include "codereader.h"
#include "codeloader.h"
#include "stringtable.h"
#include "opcode.h"

enum class ProcessorState
{
	Stopped,
	Running,
};

class Processor
{
public:
	Processor(void) = default;
	Processor(CodeReader &codeReader,CodeLoader &codeLoader);
	
	void Process(void);

	ProcessorState State = ProcessorState::Stopped;
public:	//to:do MAKE UNPUBLIC
	CodeReader * codeReader;
	CodeLoader * codeLoader;

	StringTable stringTable;

	std::string StringBuffer;
	std::string VariableBuffer;

	using VariableStack = std::stack<Variable,std::vector<Variable>>;
	VariableStack stack;
};