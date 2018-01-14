#include "processor.h"

Processor::Processor(CodeReader &codeReader, CodeLoader &codeLoader)
{
	this->codeReader = &codeReader;
	this->codeLoader = &codeLoader;
}

void Processor::Process(void)
{
	Opcode op = codeReader->ReadOpcode();
	switch(op)
	{
		case Opcode::Push:
		{
			stack.push(Variable(codeReader->ReadU8(), Variable::Type::Integer));
		}
		break;
		case Opcode::Addi:
		{
			uint8_t result = stack.top().GetValue() + codeReader->ReadU8(); 
			stack.pop();
			stack.push(Variable(result,Variable::Type::Integer));
		}
		break;
		case Opcode::DebugPrint:
		{
			/*
			auto file = std::fopen("ux0:data/vnvitaStack.txt","w");
			uint8_t buffer[] = { stack.top().GetValue() };
			std::fwrite(buffer, sizeof(uint8_t), 1, file);
			std::fflush(file);
			std::fclose(file);
			*/
			Panic = true;
		}
		break;
	}
}