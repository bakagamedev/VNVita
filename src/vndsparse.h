#pragma once
#include "common.h"
#include "vndsinstruction.h"

class VNDSParser
{
public:
	std::string Path;
	std::string CurrentScript;

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
public:
	bool Active = false;
	VNDSParser();

	OpcodeType GetOpcode(const std::string Line);
	void LoadFile(const std::string Path, const std::string File);
	std::string GetNextLine();

	void JumpTo(int LineNo);
	bool IsFinished();
};