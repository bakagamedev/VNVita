#include "codereader.h"

Opcode CodeReader::PeekOpcode(void) const
{
	return static_cast<Opcode>(this->PeekU8());
}

Opcode CodeReader::ReadOpcode(void) 
{
	return static_cast<Opcode>(this->ReadU8());
}

uint8_t CodeReader::PeekU8(void) const
{
	return this->data[index];
}
uint8_t CodeReader::ReadU8(void) 
{
	const auto result = this->data[index];
	++index;
	return result;
}