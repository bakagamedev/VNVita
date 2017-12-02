#pragma once
#include "instruction.h"
#include "novelheader.h"

enum class ParserState
{
	Running,
	Finished,
	Confused,
	WaitDecision,
	WaitKey,
}

class NovelParser
{
private:
	//State
	void LoadState(std::string const& SaveName);
	void SaveState(std::string const& SaveName);

	//Script loading
	void LoadScript(std::string const& ScriptPath);
	void LoadScriptVNDS(std::string const& ScriptPath);
	void LoadScriptVNVita(std::string const& ScriptPath);

	//Instruction stuff
	std::vector<InstructionType> Instructions;
	InstructionType GetNextInstruction();
	int16_t InstructionPointer;
	void ParseInstruction();
	bool IsEndOfScript();

	//Meta
	std::string ScriptBasePath;
	std::string ScriptPath;
	NovelType 	ScriptType;
	ParserState State;
public:
	NovelParser();
	NovelParser(NovelType ScriptType, std::string ScriptPath, std::string ScriptName);
	NovelParser(NovelType ScriptType, std::string ScriptBasePath);

	void Tick();
};

