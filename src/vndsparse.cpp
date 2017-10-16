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
}

std::string VNDSParser::GetNextLine()
{
	CurrentLine++;
	return "nope";
}

void VNDSParser::JumpTo(int LineNo)
{
	CurrentLine = LineNo;
}

bool VNDSParser::IsFinished()
{
	return false;
}