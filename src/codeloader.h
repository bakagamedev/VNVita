#pragma once
#include "codereader.h"
#include <string>
#include "opcode.h"
#include "stringtable.h"
#include "novelinfo.h"

class CodeLoader
{
private:
	NovelInfo header;

	CodeReader LoadVNDS(std::string& URL);
	CodeReader LoadVNVita(std::string& URL);
	CodeReader LoadError(std::string& URL);
public:
	CodeLoader(void) = default;
	CodeLoader(NovelInfo& header);

	CodeReader Load(std::string& URL);
	CodeReader Load(void);
};