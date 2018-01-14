#pragma once
#include <stack>
#include <vector>
#include "novelheader.h"
#include "variable.h"
#include "codereader.h"
#include "codeloader.h"
#include "stringviewer.h"
#include "opcode.h"

class Processor
{
public:
	bool Panic = false;

	Processor(void) = default;
	Processor(CodeReader &codeReader,CodeLoader &codeLoader);

	void Process(void);
public:	//to:do MAKE UNPUBLIC
	CodeReader * codeReader;
	CodeLoader * codeLoader;

	std::string StringBlob;
	std::vector<StringViewer> StringTable;
	using VariableStack = std::stack<Variable,std::vector<Variable>>;
	VariableStack stack;

};