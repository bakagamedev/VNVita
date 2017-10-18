#include "vndsparse.h"


VNDSParser::VNDSParser(std::string Path, std::string File)
{
	SetPath(Path);
	SetFile(File);
}

void VNDSParser::SetPath(const std::string Path)
{
	this->Path = Path+"/script/";
}

void VNDSParser::SetFile(const std::string File)
{
	this->File = File;

	//Log label locations
	std::map<std::string,uint> LabelLocations;
}