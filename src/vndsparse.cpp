#include "vndsparse.h"

VNDSParser::VNDSParser(BackgroundControl *Background, ForegroundControl *Foreground, TextControl *Text)
{
	this->Background = Background;
	this->Foreground = Foreground;
	this->Text = Text;
}

void VNDSParser::SetPath(const std::string Path)
{
	this->BasePath = Path;
	this->ScriptPath = Path + "/script/";
	this->BackgroundPath = Path + "/background/";
	this->ForegroundPath = Path + "/foreground/";
}

void VNDSParser::SetFile(const std::string File)
{
	this->File = File;

	//Clear State
	Instructions.clear();
	StringBlob.clear();
	CurrentLine = 0;

	//Log label locations
	std::map<std::string,uint> LabelLocations;

	//Read file
	uint LineNo = 0;

	std::ifstream fileread(ScriptPath + File);
	std::string Line;
	while(std::getline(fileread, Line))
	{
		//skip empty lines
		if(Line.empty())
			continue;

		stringltrim(Line);

		OpcodeType Opcode = GetOpcode(Line);

		//Skip unrecognisable lines
		if(Opcode == OpcodeType::None)
			continue;

		GetOperand(Line);

		if(Opcode == OpcodeType::Label)
		{
			LabelLocations[Line] = LineNo;
			continue;
		}

		uint StringLength = Line.size();
		Instructions.push_back(VNDSInstruction(Opcode, StringViewer(StringBlob.size(),StringLength)));
		StringBlob.append(Line);
		++LineNo;
	}

	DumpStrings(ScriptPath + File + ".txt");
}

void VNDSParser::Tick(bool Pressed)
{
	RunNextLine();
}

void VNDSParser::RunNextLine()
{
	VNDSInstruction * CurrentInstruction = &Instructions[CurrentLine];

	//replace with map or something
	switch(CurrentInstruction->Opcode)
	{
		case OpcodeType::Text:
			FunctionText(CurrentInstruction->Operand.String);
			break;
		case OpcodeType::Jump:
			FunctionJump(CurrentInstruction->Operand.String);
			break;
		case OpcodeType::Bgload:
			FunctionBgload(CurrentInstruction->Operand.String);
			break;
	}

	++CurrentLine;
}

void VNDSParser::DumpStrings(const std::string outfile)
{
    std::ofstream out(ScriptPath + outfile);
    out << StringBlob;
    out.close();
}

OpcodeType VNDSParser::GetOpcode(const std::string line)
{
	std::string opstring = line.substr(0, line.find(" "));
	if(OpcodeStrings.find(opstring) != OpcodeStrings.end())
	{
		return OpcodeStrings[opstring];
	}
	return OpcodeType::None;
}
void VNDSParser::GetOperand(std::string &line)
{
	line = line.substr(line.find_first_of(" \t")+1);
}

/*
	Function zone! Actung!
*/

void VNDSParser::FunctionText(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	Text->TextAdd(String);	//shrug!
}

void VNDSParser::FunctionJump(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	std::string File = String.substr(0, String.find(" "));	//Find first arg. todo: Make a splitter function
	SetFile(File);
}

void VNDSParser::FunctionBgload(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	Text->TextAdd(BackgroundPath+String);
	Background->SetImage(BackgroundPath+String);
}