#include "processor.h"

Processor::Processor(CodeReader &codeReader, CodeLoader &codeLoader)
{
	this->codeReader = &codeReader;
	this->codeLoader = &codeLoader;
}

void Processor::Process(void)
{
	if(State != ProcessorState::Running)
		return;

	Opcode op = codeReader->ReadOpcode();
	switch(op)
	{
		case Opcode::Push:
		{
			stack.push(Variable(codeReader->ReadU8(), Variable::Type::Integer));
		} break;
		case Opcode::Pop:
		{
			stack.pop();
		} break;
		case Opcode::Add:
		{
			uint8_t first = stack.top().GetValue();
				stack.pop();
			uint8_t second = stack.top().GetValue();
				stack.pop();
			uint32_t result = first + second;
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Sub:
		{
			uint8_t first = stack.top().GetValue();
			stack.pop();
			uint8_t second = stack.top().GetValue();
			stack.pop();
			uint32_t result = first - second;
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Div:
		{
			uint8_t first = stack.top().GetValue();
			stack.pop();
			uint8_t second = stack.top().GetValue();
			stack.pop();
			uint32_t result = first / second;
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Mul:
		{
			uint8_t first = stack.top().GetValue();
			stack.pop();
			uint8_t second = stack.top().GetValue();
			stack.pop();
			uint32_t result = first * second;
			stack.push(Variable(result,Variable::Type::Integer));

		} break;
		case Opcode::Addi:
		{
			uint32_t result = stack.top().GetValue() + codeReader->ReadU8(); 
			stack.pop();
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Subi:
		{
			uint32_t result = stack.top().GetValue() - codeReader->ReadU8();
			stack.pop();
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Divi:
		{
			uint32_t result = stack.top().GetValue() / codeReader->ReadU8();
			stack.pop();
			stack.push(Variable(result,Variable::Type::Integer));
		} break;
		case Opcode::Muli:
		{
			uint32_t result = stack.top().GetValue() * codeReader->ReadU8();
			stack.pop();
			stack.push(Variable(result,Variable::Type::Integer));
		} break;

		case Opcode::VarLoadID:
		{

		} break;
		case Opcode::VarLoadString:
		{

		} break;
		case Opcode::VarClearBuffer:
		{
			VariableBuffer.clear();
		} break;

		case Opcode::TextClear:
		{
			StringBuffer.clear();
		}; break;
		case Opcode::TextAddID:
		{
			StringBuffer.append(stringTable[codeReader->ReadU32()]);
		} break;
		case Opcode::TextAddFromVar:
		{
			StringBuffer.append(VariableBuffer);
		} break;
		case Opcode::TextPrint:
		{
			//Send StringBuffer to screen
		} break;
		case Opcode::TextPrintDirect:
		{
			std::string TempString = stringTable[codeReader->ReadU32()];
			//send TempString to screen
		} break;
		case Opcode::DebugPrint:
		{
			auto file = std::fopen("ux0:data/_vnvitastack.txt","w");
			uint32_t buffer[] = { stack.top().GetValue() };
			std::fwrite(buffer, sizeof(uint32_t), 1, file);
			std::fflush(file);
			std::fclose(file);
		} break;
	}
}