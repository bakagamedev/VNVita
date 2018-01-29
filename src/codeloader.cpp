#include "codeloader.h"

CodeLoader::CodeLoader(NovelInfo& header)
{
	this->header = header;
}

CodeReader CodeLoader::Load(std::string& URL)
{
	return LoadError(URL);
	/*
	switch(header.Type)
	{
		case NovelType::VNDS:
			return(LoadVNDS(URL));
		break;
		case NovelType::VNVita:
			return(LoadVNVita(URL));
		break;
		case NovelType::Error:
			return(LoadError(URL));
		break;
	}
	*/
}

CodeReader CodeLoader::LoadError(std::string& URL)
{
	//Print an error message in dialogue box
	/*
		Say something like
			"bad file : " + URL
	*/
	StringTable table;
	table.Add(URL);
	table.Add("Malformed file. Sorry.");

	std::vector<uint8_t> data = 
	{
		static_cast<uint8_t>(Opcode::TextAddID),0,
		static_cast<uint8_t>(Opcode::TextAddID),1,
		static_cast<uint8_t>(Opcode::TextPrint),
		static_cast<uint8_t>(Opcode::WaitUI),
	};
	return CodeReader(data);
}

CodeReader CodeLoader::Load(void)
{
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

CodeReader CodeLoader::LoadVNDS(std::string& URL)
{
	//Unimplemented
	return CodeReader();
}

CodeReader CodeLoader::LoadVNVita(std::string& URL)
{
	//Unimplemented
	return CodeReader();	
}