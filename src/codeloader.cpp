#include "codeloader.h"

	/*
CodeReader CodeLoader::Load(std::string& FilePath)
{
	uint8_t Nop = static_cast<uint8_t>(Opcode::Nop);
	std::vector<uint8_t> data = 
		{	Push,4,Addi,5,DebugPrint,   };
	return CodeReader(data);

}*/

CodeReader CodeLoader::Load(void)
{
	uint8_t Nop = static_cast<uint8_t>(Opcode::Nop);
	std::vector<uint8_t> data = 
	{	
		static_cast<uint8_t>(Opcode::Push),
		14,
		static_cast<uint8_t>(Opcode::Addi),
		205,
		static_cast<uint8_t>(Opcode::DebugPrint),
	};
	return CodeReader(data);
}