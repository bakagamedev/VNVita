#pragma once
#include "common.h"
#include "../inih/cpp/INIReader.h"
#include "userinterface/sprite.h"
#include "stringhelpers.h"

enum class NovelPackType
{
	Folder,
	Zip,
	VNDSNovel,
};

class NovelInfo
{
private:
	bool FileExists(std::string Path)	//Move to some helper .h somewhere
	{
		SceIoStat StatTemp;
		return (sceIoGetstat(Path.c_str(), &StatTemp) >= 0);
	}

	NovelFormatType IdentifyFormat();
	void ReadVNVitaHeader();
	void ReadVNDSHeader();
public:
	std::string Path;
	std::string Title;
	std::string Description;
	UISprite Icon;
	UISprite Preview;

	int Width = 0, Height = 0;

	std::string ScriptEntry;

	NovelFormatType Format;
	NovelPackType PackType;
	bool IsCompiled;

	NovelInfo() = default;
	NovelInfo(const std::string& url);
};