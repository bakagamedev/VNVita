#pragma once
#include "common.h"
#include <fstream>
#include "vndsinstruction.h"
#include "stringhelpers.h"
#include "stringviewer.h"
#include "imagecontrol.h"
#include "textcontrol.h"
#include "stringviewer.h"

class VNDSParser
{
private:
	BackgroundControl * Background;
	ForegroundControl * Foreground; 
	TextControl * Text;

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

	uint CurrentLine = 0;
	int FramesCountdown = -1;

	//Loading
	OpcodeType GetOpcode(const std::string line);
	void GetOperand(std::string &line);

	//VNDS Functions
	void FunctionText(StringViewer Viewer);
	void FunctionJump(StringViewer Viewer);
public:
	VNDSParser(BackgroundControl *Background, ForegroundControl *Foreground, TextControl *Text);
	void Tick(bool Pressed);

	void SetPath(const std::string Path);
	void SetFile(const std::string File);

	void RunNextLine();
	void DumpStrings(const std::string outfile);
};