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
	LabelLocations.clear();
	Instructions.clear();
	StringBlob.clear();
	CurrentLine = 0;

	//Log label locations
	//Read file
	uint LineNo = 0;

	std::ifstream fileread(ScriptPath + File);
	std::string Line;
	while(std::getline(fileread, Line))
	{
		//skip empty lines
		if(Line.empty())
			continue;

		stringtrim(Line);

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

	if(Instructions.size() == 0)
	{
		Text->TextAdd("Bad script file");
		Text->TextAdd(ScriptPath+File);
	}

	DumpStrings(ScriptPath + File + ".txt");
}

void VNDSParser::Tick(bool Pressed)
{
	RunNextLine();
}

bool VNDSParser::IsFinished()
{
	return (CurrentLine>=Instructions.size());
}

void VNDSParser::RunNextLine()
{
	if(IsFinished())
	{
		return;
	}

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
		case OpcodeType::Setimg:
			FunctionSetimg(CurrentInstruction->Operand.String);
			break;
		case OpcodeType::Goto:
			FunctionGoto(CurrentInstruction->Operand.String);
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
	if (String.size() == 0)
		return;

	bool blocking = true;
	char firstchar = String.at(0);
	if(firstchar == '@')	
		{	blocking = false;	String.erase(0,1);	}
	if(firstchar == '~')	
		{	String = "";	blocking = false;	}
	if(firstchar == '!')	
		{	String = ""; blocking = true;	}

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

void VNDSParser::FunctionSetimg(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	Text->TextAdd(ForegroundPath+String);
}

void VNDSParser::FunctionGoto(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	Text->TextAdd("Goto : "+String);
	if(LabelLocations.count(String) != 0)
	{
		CurrentLine = LabelLocations[String];
		Text->TextAdd("Cool!");
	}
	else
	{
		Text->TextAdd("Failed.");
	}
}