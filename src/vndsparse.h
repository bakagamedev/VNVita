#pragma once
#include "common.h"
#include "vndsinstruction.h"

class VNDSParser
{
public:
	std::string Path;
	std::string CurrentScript;

	int CurrentLine = 0;
	std::vector<VNDSInstruction> Script;
public:
	bool Active = false;

	VNDSParser();
	void LoadFile(const std::string Path, const std::string File);
	std::string GetNextLine();
	void JumpTo(int LineNo);
	bool IsFinished();
};