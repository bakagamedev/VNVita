#pragma once
#include "common.h"
#include "vndsinstruction.h"
#include "stringhelpers.h"

class VNDSParser
{
private:
	std::string Path;
	std::string File;

	std::map<std::string,OpcodeType> OpcodeStrings = {
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

	char * TextTable;

public:
	VNDSParser(std::string Path,std::string File);
	void SetPath(const std::string Path);
	void SetFile(const std::string File);
};