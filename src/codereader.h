#pragma once
#include <utility>
#include <vector>
#include <cstdint>
#include "opcode.h"

class CodeReader
{
public: //UNPUBLIC
	std::vector<uint8_t> data;
	size_t index = 0;

public:
	CodeReader(void) = default;
	CodeReader(std::vector<uint8_t> data)
	{
		this->data = data;
	}
	CodeReader(std::vector<uint8_t>&& data)
	{
		this->data = std::move(data);
	}

	const std::vector<uint8_t> & GetData() const 
	{
		return this->data;
	}
	void JumpBy(int32_t jump)
	{
		index += jump;
	}
	void JumpTo(size_t jump)
	{
		index = jump;
	}

	bool InMemory(void) const;
	
	Opcode PeekOpcode(void) const;
	Opcode ReadOpcode(void);

	uint8_t PeekU8(void) const;
	uint8_t ReadU8(void);
	uint16_t PeekU16(void);
	uint16_t ReadU16(void);
	uint32_t ReadU32(void);
	uint32_t PeekU32(void);
};