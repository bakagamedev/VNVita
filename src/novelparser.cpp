#include "novelparser.h"
#include "common.h"

NovelParser::NovelParser()	{}
NovelParser::NovelParser(NovelType ScriptType, std::string ScriptBasePath, std::string ScriptName)
{
	this->ScriptBasePath = ScriptBasePath;
	this->ScriptType = ScriptType;
	this->ScriptPath = ScriptBasePath+"\\"+ScriptName;
	LoadScript(ScriptName);
}
NovelParser::NovelParser(NovelType ScriptType, std::string ScriptBasePath)
{
	this->ScriptType = ScriptType;
	this->ScriptBasePath = ScriptBasePath;
	switch(ScriptType)
	{
		case NovelType::VNDS:
			this->ScriptPath = ScriptBasePath+"\\main.scr";
			break;
		case NovelType::VNVita:
			this->ScriptPath = ScriptBasePath+"\\main.txt";
			break;
	}
	LoadScript(ScriptPath);
}

void NovelParser::LoadScript(std::string const& ScriptPath)
{
	switch(ScriptType)
	{
		case NovelType::VNDS:
			LoadScriptVNDS(ScriptPath);
			break;
		case NovelType::VNVita:
			LoadScriptVNVita(ScriptPath);
			break;
	}
}
void NovelParser::LoadScriptVNDS(std::string const& ScriptPath)
{

}
void NovelParser::LoadScriptVNVita(std::string const& ScriptPath)
{

}

InstructionType NovelParser::GetNextInstruction()
{
	if(IsEndOfScript())
		return InstructionType();	//No args = nop

	return Instructions[InstructionPointer++];
}
bool NovelParser::IsEndOfScript()
{
	return(InstructionPointer >= Instructions.size());
}

void NovelParser::Tick()
{
	ParseInstruction();
}

void NovelParser::ParseInstruction()
{
	InstructionType Instruction = GetNextInstruction();
	switch(Instruction.Opcode)
	{
		case OpcodeType::Nop:	{}; break;

	}
}