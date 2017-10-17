#include "vndsparse.h"

VNDSParser::VNDSParser()
{
	Active = false;
}

void VNDSParser::LoadFile(const std::string Path, const std::string File)
{
	Active = true;
	this->Path = Path+"/script";
	this->CurrentScript = this->Path + "/"+ File;

	std::string Line;
	std::ifstream text(CurrentScript);
	if (text.is_open())
	{
		while (text.good())
		{
			getline(text,Line);
			if(!Line.empty())
			{
				OpcodeType code = GetOpcode(Line);
				if(code != OpcodeType::None)
				{
					Line = Line.substr(Line.find_first_of(" \t")+1);	//Delete the opcode
					Script.emplace_back(code,Line);
				}
			}	
		}
		text.close();
	}
	else
	{
		Script.emplace_back(OpcodeType::Text,"can't open file!");
	}
}

OpcodeType VNDSParser::GetOpcode(const std::string Line)
{
	std::string type = Line.substr(0, Line.find(" "));
	if(OpcodeLookup.count(type) == 1)
		return OpcodeLookup[type];
	return OpcodeType::None;
}

std::string VNDSParser::GetNextLine()
{
	++CurrentLine;
	while(Script[CurrentLine].Opcode != OpcodeType::Text)
	{
		++CurrentLine;
		if(IsFinished())
			return "oh no, EOF!";
	}
	return(Script[CurrentLine].Operand);
}

void VNDSParser::JumpTo(int LineNo)
{
	CurrentLine = LineNo;
}

bool VNDSParser::IsFinished()
{
	return (CurrentLine >= (int)Script.size());
}