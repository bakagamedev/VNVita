#pragma once
#include "common.h"
#include "vndsinstruction.h"

class VNDSParser
{
private:
	std::string Path;
	std::string CurrentScript;

	std::map<std::string,uint> LabelLocations;

	std::map<std::string,OpcodeType> OpcodeLookup = {
		{ "label", OpcodeType::Label },
		{ "jump", OpcodeType::Jump },
		{ "goto", OpcodeType::Goto },
		{ "if", OpcodeType::If },
		{ "fi", OpcodeType::Fi },
		{ "setvar", OpcodeType::Setvar },
		{ "gsetvar", OpcodeType::Gsetvar },
		{ "random", OpcodeType::Random },
		{ "delay", OpcodeType::Delay },
		{ "bgload", OpcodeType::Bgload },
		{ "setimg", OpcodeType::Setimg },
		{ "music", OpcodeType::Music },
		{ "sound", OpcodeType::Sound },
		{ "cleartext", OpcodeType::Cleartext },
		{ "text", OpcodeType::Text },
		{ "choice", OpcodeType::Choice },
	};

	int CurrentLine = 0;
	std::vector<VNDSInstruction> Script;

	void ParseCurrentLine();
	OpcodeType GetOpcode(const std::string Line);

public:
	bool WaitingForInput = false;
	std::string CurrentLineText;
	bool Active = false;

	VNDSParser();

	void SetPath(const std::string Path);
	void LoadFile(const std::string File);

	bool HasText();
	std::string GetLineText();
	void RunNextLine();
	void JumpTo(int LineNo);
	bool IsFinished();

	void DebugDump();

	//Functions
	void FunctionGoto();
	void FunctionJump();
	void FunctionText();
};