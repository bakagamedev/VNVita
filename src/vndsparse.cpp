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
	this->SavePath = Path + "/foreground/";
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
	/*
	if(--DelayFrames >= 0)
		return
	*/

	TempString.clear();
	blocking = false;
	//"Blocking" being set to true hands control back to the UI.
	while(!blocking)
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
			case OpcodeType::Cleartext:
				FunctionClearText();
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
			case OpcodeType::If:
				TextAdd("If");
				break;
			case OpcodeType::Fi:
				TextAdd("Fi");
				break;
			case OpcodeType::Setvar:
				TextAdd("Setvar");
				break;
			case OpcodeType::Gsetvar:
				TextAdd("GSetvar");
				break;
			case OpcodeType::Random:
				TextAdd("Random");
				break;
			case OpcodeType::Delay:
				TextAdd("Delay");
				break;
			case OpcodeType::Music:
				TextAdd("Music");
				break;
			case OpcodeType::Sound:
				TextAdd("Sound");
				break;
			case OpcodeType::Choice:
				TextAdd("Choice");
				break;

		}
		++CurrentLine;
	}

	if(!TempString.empty())
		Text->TextAdd(TempString);
}

void VNDSParser::DumpStrings(const std::string outfile)
{
    std::ofstream out(outfile);
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
	if(line == "text")	//Blank lines manifest here as just "text"
	{
		line = "";
	}
	else
	{
		line = line.substr(line.find_first_of(" \t")+1);
	}
}

void VNDSParser::TextAdd(std::string String)
{
	if(!TempString.empty())	TempString += "\n";
	TempString += String;
}

/*
	Function zone! Actung!
*/
void VNDSParser::FunctionText(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	if (String.size() == 0)
		return;

	blocking = true;
	char firstchar = String.at(0);
	if(firstchar == '@')	
		{	blocking = false;	String.erase(0,1);	}
	if(firstchar == '~')	
		{	String = "";	blocking = false;	}
	if(firstchar == '!')	
		{	String = ""; blocking = true;	}

	TextAdd(String);
}

void VNDSParser::FunctionClearText()
{
	for(int i=0; i<Text->MaxLines; ++i)
		TempString += "\n";
}

void VNDSParser::FunctionJump(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	std::vector<StringViewer> Tokens = stringsplit(String);
	SetFile(Tokens[0].GetString(String));
}

void VNDSParser::FunctionBgload(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	auto Tokens = stringsplit(String);
	TextAdd(BackgroundPath+String);
	Background->SetImage(BackgroundPath+Tokens[0].GetString(String));

	if(Tokens.size() > 1)
	{
		//Change bg delay
	}
}

void VNDSParser::FunctionSetimg(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	auto Tokens = stringsplit(String);
	Foreground->SetImage(ForegroundPath+Tokens[0].GetString(String));
	int x,y;
	if(Tokens.size()>1)
	{
		try
		{
			x = std::stoi(Tokens[1].GetString(String));
			y = std::stoi(Tokens[2].GetString(String));
		}
		catch(std::invalid_argument)
		{
			x = 0;
			y = 0;
		}
	}
	Foreground->SetPosition(x,y);
	TextAdd(ForegroundPath+String);
}

void VNDSParser::FunctionGoto(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	TextAdd("Goto : "+String);
	if(LabelLocations.count(String) != 0)
	{
		CurrentLine = LabelLocations[String];
		TextAdd("Cool!");
	}
	else
	{
		TextAdd("Failed.");
	}
}