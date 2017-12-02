#pragma once
#include "instruction.h"
#include "novelheader.h"

class NovelParser
{
private:
	//Loading
	void LoadScript(std::string const& ScriptName);
	void LoadState(std::string const& SaveName);

	void LoadScriptVNDS(std::string const& ScriptName);
	void LoadScriptVNVita(std::string const& ScriptName);

	//
	std::vector<InstructionType> Instructions;
	InstructionType GetNextInstruction();

	//Meta
	std::string ScriptPath;
	std::string ScriptName;
	NovelType 	ScriptType;
public:
	NovelParser();
	NovelParser(NovelType ScriptType, std::string ScriptPath, std::string ScriptName);
	NovelParser(NovelType ScriptType, std::string ScriptBasePath);

	void Tick();
};

