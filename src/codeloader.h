#pragma once
#include "codereader.h"
#include <string>
#include "opcode.h"

class CodeLoader
{
private:

public:
	CodeReader Load(void);
	//CodeReader Load(std::string& FilePath);
};