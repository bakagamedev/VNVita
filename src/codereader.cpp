#include "codereader.h"


bool CodeReader::InMemory(void) const
{
	return (index < data.size());
}

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
	if(!InMemory())	return 0;
	return this->data[index];
}
uint8_t CodeReader::ReadU8(void) 
{
	auto result = PeekU8();
	++index;
	return result;
}

uint16_t CodeReader::PeekU16(void)
{
	uint16_t result = ReadU16();
	JumpBy(-2);	//move back 2 bytes
	return result;
}
uint16_t CodeReader::ReadU16(void)
{
	uint8_t first = ReadU8();
	return (first<<8)+ReadU8();
}
uint32_t CodeReader::PeekU32(void)
{
	uint32_t result = ReadU32();
	JumpBy(-4);
	return result;
}
uint32_t CodeReader::ReadU32(void)
{
	uint16_t first = ReadU16();
	uint32_t result = (first<<16)+ReadU16();
	return result;
}