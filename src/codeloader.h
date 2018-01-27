#pragma once
#include "codereader.h"
#include <string>
#include "opcode.h"
#include "header.h"
#include "stringtable.h"

class CodeLoader
{
private:
	NovelHeader header;

	CodeReader LoadVNDS(std::string& URL);
	CodeReader LoadVNVita(std::string& URL);
	CodeReader LoadError(std::string& URL);
public:
	CodeLoader(void) = default;
	CodeLoader(NovelHeader& header);

	CodeReader Load(std::string& URL);
	CodeReader Load(void);
};