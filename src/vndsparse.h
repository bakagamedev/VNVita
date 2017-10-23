#pragma once
#include "common.h"
#include <fstream>
#include "vndsinstruction.h"
#include "vndsvariable.h"
#include "stringhelpers.h"
#include "stringviewer.h"
#include "imagecontrol.h"
#include "textcontrol.h"
#include "stringviewer.h"
#include "vndsvariable.h"

class VNDSParser
{
private:
	BackgroundControl * Background;
	ForegroundControl * Foreground; 
	TextControl * Text;

	std::string BasePath;
	std::string ScriptPath;
	std::string SavePath;
	std::string BackgroundPath;
	std::string ForegroundPath;

	std::string File;

	std::map<std::string,OpcodeType> OpcodeStrings = {
		{ "label", OpcodeType::Label },	//Done
		{ "jump", OpcodeType::Jump },	//Half done
		{ "goto", OpcodeType::Goto },	//Done
		{ "if", OpcodeType::If },
		{ "fi", OpcodeType::Fi },
		{ "setvar", OpcodeType::Setvar },
		{ "gsetvar", OpcodeType::Gsetvar },
		{ "random", OpcodeType::Random },
		{ "delay", OpcodeType::Delay },
		{ "bgload", OpcodeType::Bgload },	//Half done 
		{ "setimg", OpcodeType::Setimg },	//Sorta done
		{ "music", OpcodeType::Music },
		{ "sound", OpcodeType::Sound },
		{ "cleartext", OpcodeType::Cleartext },	//Done, untested
		{ "text", OpcodeType::Text },	//Done
		{ "choice", OpcodeType::Choice },
	};

	std::vector<VNDSVariable> LocalVariables;
	std::vector<VNDSVariable> GlobalVariables;

	std::string TempString;	//Pass to Text object
	std::map<std::string,uint> LabelLocations;
	std::vector<VNDSInstruction> Instructions;
	std::string StringBlob;	

	bool blocking = false;
	uint CurrentLine = 0;
	int FramesCountdown = -1;

	//Loading
	OpcodeType GetOpcode(const std::string line);
	void GetOperand(std::string &line);

	void TextAdd(std::string String);
	//VNDS Functions
	void FunctionText(StringViewer Viewer);
	void FunctionJump(StringViewer Viewer);
	void FunctionBgload(StringViewer Viewer);
	void FunctionSetimg(StringViewer Viewer);
	void FunctionGoto(StringViewer Viewer);
	void FunctionClearText();
public:
	VNDSParser(BackgroundControl *Background, ForegroundControl *Foreground, TextControl *Text);
	void Tick(bool Pressed);
	bool IsFinished();

	void SetPath(const std::string Path);
	void SetFile(const std::string File);

	void RunNextLine();
	void DumpStrings(const std::string outfile);
};