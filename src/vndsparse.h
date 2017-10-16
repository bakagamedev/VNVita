#pragma once
#include "common.h"

class VNDSParser
{
public:
	std::string Path;
	std::string CurrentScript;

	int CurrentLine = 0;
	std::vector<std::string> Script;
public:
	bool Active = false;

	VNDSParser();
	void LoadFile(std::string Path, std::string File);
	std::string GetNextLine();
	void JumpTo(int LineNo);
	bool IsFinished();
};