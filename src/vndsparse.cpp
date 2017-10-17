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
				Script.emplace_back(code,Line);
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
	return OpcodeType::Text;
}

std::string VNDSParser::GetNextLine()
{
	CurrentLine++;
	if(!IsFinished())
	{
		return Script[CurrentLine].Operand;
	}
	else
	{
		return "oh no, EOF!";
	}
}

void VNDSParser::JumpTo(int LineNo)
{
	CurrentLine = LineNo;
}

bool VNDSParser::IsFinished()
{
	return (CurrentLine >= (int)Script.size());
}