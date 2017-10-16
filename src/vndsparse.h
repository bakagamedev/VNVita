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
	void LoadFile(const std::string Path, const std::string File);
	std::string GetNextLine();
	void JumpTo(int LineNo);
	bool IsFinished();
};