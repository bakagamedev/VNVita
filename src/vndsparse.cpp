#include "vndsparse.h"


VNDSParser::VNDSParser()
{
	Active = false;
}

void VNDSParser::SetPath(const std::string Path)
{
	this->Path = Path+"/script";
}

void VNDSParser::LoadFile(const std::string File)
{
	Active = true;
	this->CurrentScript = this->Path + "/"+ File;

	//Clear out old data
	Script.clear();
	LabelLocations.clear();
	CurrentLine = 0;

	uint LineNo = 0;
	std::string Line;
	std::ifstream text(CurrentScript);
	if (text.is_open())
	{
		while (text.good())
		{
			getline(text,Line);
			if(!Line.empty())
			{
				trim(Line);	//Remove surrounding whitespace
				OpcodeType code = GetOpcode(Line);
				Line = Line.substr(Line.find_first_of(" \t")+1);	//Delete the opcode	

				switch(code)
				{
					case OpcodeType::None: break;	//Don't bother with NOPs.
					case OpcodeType::Label:	//Store label position
					{
						LabelLocations[Line] = LineNo+1;	//+1 because it's the next instruction that you care about
					}; break;
					default:	//If it's anything else, store that thing
					{
						Script.emplace_back(code,Line);
						++LineNo;	
					}; break;
				}		
			}	
		}
		text.close();
		Script.emplace_back(OpcodeType::FileEnd,"");	//actually not a bad idea, IMO
	}
	else
	{
		Script.emplace_back(OpcodeType::Text,"can't open file!");
		Script.emplace_back(OpcodeType::FileEnd,"");
	}

	RunNextLine();	//Run first few lines to start things off
}

OpcodeType VNDSParser::GetOpcode(const std::string Line)
{
	std::string type = Line.substr(0, Line.find(" "));
	if(OpcodeLookup.count(type) == 1)
		return OpcodeLookup[type];
	return OpcodeType::None;
}

void VNDSParser::RunNextLine()
{
	if(IsFinished())
	{
		return;
	}
	WaitingForInput = false;

	const int MaxLinesParse = 100;  //if you've parsed more than 100 instructions and haven't found a reason to stop, ask user to continue. 
	int LinesParsed = 0;

	CurrentLineText = "";
	bool CanContinue = false;
	while(CanContinue == false)
	{
		++CurrentLine;
		ParseCurrentLine();

		//Reasons to stop parsing for current frame:
		if(IsFinished())	//EOF
			CanContinue = true;
		if(WaitingForInput)	//User input needed
			CanContinue = true;
		if(++LinesParsed > MaxLinesParse)	//Parsed too many things, need a rest.
			CanContinue = true;
	}
}

std::string VNDSParser::GetLineText()
{
	return CurrentLineText;
}

bool VNDSParser::HasText()
{
	return (!CurrentLineText.empty());
}

bool VNDSParser::IsFinished()
{
	if(CurrentLine > Script.size())	///juussst in case I fucked up elsewhere
		return true;

	return (Script[CurrentLine].Opcode == OpcodeType::FileEnd);
}

void VNDSParser::ParseCurrentLine()
{
	OpcodeType code = Script[CurrentLine].Opcode;

	switch(code)	//Replace with map
	{
		case OpcodeType::Text:
			FunctionText();
			break;
		case OpcodeType::Jump:
			FunctionJump();
			break;
	}
}

void VNDSParser::DebugDump()
{
	CurrentLineText = CurrentScript + " : " + std::to_string(CurrentLine) + " : "+std::to_string(WaitingForInput) + " : "+std::to_string(IsFinished());
}

///Functions : 
void VNDSParser::FunctionGoto()
{
	//If find line value in map, jump to it
	//CurrentLine = LineNo;
}
void VNDSParser::FunctionJump()
{
	std::string File = Script[CurrentLine].Operand;
	CurrentLineText.append("Jump to : ");
	CurrentLineText.append(File);
	WaitingForInput = true;
	LoadFile(File);
}

void VNDSParser::FunctionText()
{
	auto Line = Script[CurrentLine].Operand;

	if(Line.length() == 1)
	{
		if(Line.compare("~"))	//Blank line
		{
			CurrentLineText.append("\n");
			WaitingForInput = false;
			return;
		}
		if(Line.compare("!"))	//Blank line, but input needed to continue
		{
			CurrentLineText.append("\n");
			WaitingForInput = true;
			return;
		}
	}
	CurrentLineText.append(Script[CurrentLine].Operand);
	WaitingForInput = true;
}