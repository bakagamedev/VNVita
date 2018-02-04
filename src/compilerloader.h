#pragma once
#include "stringtable.h"
#include "stringhelpers.h"
#include "compiler.h"

class CompilerLoader
{
private:
	StringTable sourceFiles;
	void DetectVNDS(const std::string& ScriptPath);
	void DetectVNVita(const std::string& ScriptPath);
public:
	CompilerLoader() = default;

	Compiler Load(const std::string& ScriptPath,const std::string& OutputPath,NovelFormatType Type);
};
