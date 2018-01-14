#pragma once

enum class Opcode
{
	Nop = 0,
	HCF = 255,

	Add = 1,
	Sub = 2,
	Div = 3,
	Mul = 4,
	Addi = 5,
	Subi = 6,
	Divi = 7,
	Muli = 8,

	Push = 9,
	Pop  = 10, 
	Pull = 11,

	DebugPrint,
};