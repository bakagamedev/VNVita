#pragma once

enum class Opcode
{
	Nop = 0,

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

	VarLoadID,
	VarLoadString,
	VarClearBuffer,

	TextClear,			//Clear strbuffer
	TextAddID,			//$0,Load strbuffer from stringtable
	TextAddFromVar,		//
	TextPrint,			//Prints strbuffer
	TextPrintDirect,	//$0,Prints strbuffer from stringtable

	WaitUI,				//Waits for UI to be ready

	DebugPrint,
	HCF = 255,
};