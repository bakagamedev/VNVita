#include "vndsparse.h"

VNDSParser::VNDSParser()
{
}

void VNDSParser::SetPath(const std::string Path)
{
	this->Path = Path+"/script/";
}

void VNDSParser::SetFile(const std::string File)
{
	this->File = File;

	//Clear State
	StringBlob.clear();
	CurrentLine = 0;

	//Log label locations
	std::map<std::string,uint> LabelLocations;

	//Read file
	uint LineNo = 0;

	std::ifstream fileread(Path + File);
	std::string Line;
	while(std::getline(fileread, Line))
	{
		//skip empty lines
		if(Line.empty())
			continue;

		stringltrim(Line);

		OpcodeType Opcode = GetOpcode(Line);

		//Skip recognisable lines
		if(Opcode == OpcodeType::None)
			continue;

		GetOperand(Line);

		if(Opcode == OpcodeType::Label)
		{
			LabelLocations[Line] = LineNo;
			continue;
		}

		uint StringLength = Line.size();
		//Instructions.push_back(Opcode,CharViewer(&StringBlob,StringBlob.size(),StringLength));
		StringBlob.append(Line);
		++LineNo;
	}
}

void VNDSParser::RunNextLine()
{
	VNDSInstruction CurrentInstruction = Instructions[CurrentLine];
	/*
	switch(CurrentInstruction.Opcode)
	{
		case OpcodeType::Text:
			//????
			break;
	}
	*/
}

void VNDSParser::DumpStrings(const std::string outfile)
{
    std::ofstream out(Path + outfile);
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