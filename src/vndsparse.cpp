#include "vndsparse.h"

VNDSParser::VNDSParser()
{
	Active = false;
}

void VNDSParser::LoadFile(std::string Path,std::string File)
{
	Active = true;
	this->Path = Path+"/script";
	this->CurrentScript = this->Path + "/"+ File;

	std::string line;
	std::ifstream text("ux0:data/vnvita/ever17/script/op00.scr");
	if (text.is_open())
	{
		while (text.good())
		{
			getline(text,line);
			if(line != "")
			{
				Script.push_back(line);
			}	
		}
		text.close();
	}
	else
	{
		Script.push_back("can't open file!");
	}
}

std::string VNDSParser::GetNextLine()
{
	CurrentLine++;
	return Script[CurrentLine];
}

void VNDSParser::JumpTo(int LineNo)
{
	CurrentLine = LineNo;
}

bool VNDSParser::IsFinished()
{
	return false;
}