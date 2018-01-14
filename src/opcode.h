#pragma once

enum class Opcode
{
	Nop,
	HCF,

	Add,
	Sub,
	Div,
	Mul,
	Addi,
	Subi,
	Divi,
	Muli,

	Push,
	Pop,
	Pull,

	DebugPrint,
};