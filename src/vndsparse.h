#pragma once
#include "common.h"
#include <fstream>
#include <psp2/io/stat.h>
#include "ini/INIReader.h"
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
	ImageControl * Images;
	TextControl * Text;

	std::string BasePath;
	std::string ScriptPath;
	std::string SavePath;
	std::string SoundPath;
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

	std::string TempString;	//Pass to Text object
	std::map<std::string,uint> LabelLocations;
	std::vector<VNDSInstruction> Instructions;
	std::string StringBlob;	

	StringViewer QuestionAnswerViewer;

	int DelayFrames = -1;
	bool Continue = false;
	bool Blocking = false;
	uint CurrentLine = 0;

	bool QuestionWait = false;
	int QuestionAnswer = -1;

	//Loading
	OpcodeType GetOpcode(const std::string &line);
	void GetOperand(std::string &line);

	void TextAdd(const std::string &String);

	//Variables
	std::map<std::string,std::string> LocalVariables;
	std::map<std::string,std::string> GlobalVariables;
	void SetVar(std::string Var, std::string Value);
	void SetVar(std::string Var, int Value);
	void SetGVar(std::string Var, std::string Value);

	//VNDS Functions
	void FunctionText(StringViewer Viewer);
	void FunctionJump(StringViewer Viewer);
	void FunctionBgload(StringViewer Viewer);
	void FunctionSetimg(StringViewer Viewer);
	void FunctionGoto(StringViewer Viewer);
	void FunctionClearText();
	void FunctionDelay(StringViewer Viewer);
	void FunctionChoice(StringViewer Viewer);
	void FunctionIf(StringViewer Viewer);

public:
	VNDSParser(ImageControl *Image, TextControl *Text);
	void Tick(bool Pressed);
	bool IsFinished();

	bool IsQuestion();
	void SetAnswer(int Answer);
	std::string GetQuestionAnswers();

	void SaveState(const std::string SaveFile);
	void LoadState(const std::string SaveFile);

	void SetPath(const std::string Path);
	void SetFile(const std::string File);

	void RunNextLine();
	void DumpStrings(const std::string &outfile);
};