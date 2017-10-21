#pragma once
#include "common.h"
#include "vndsinstruction.h"
#include "stringhelpers.h"
#include <fstream>

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

	std::vector<VNDSInstruction> Instructions;
	std::string StringBlob;	

	uint CurrentLine;

	//Loading
	OpcodeType GetOpcode(const std::string line);
	void GetOperand(std::string &line);
public:
	VNDSParser();
	void SetPath(const std::string Path);
	void SetFile(const std::string File);

	void RunNextLine();
	void DumpStrings(const std::string outfile);
};