#pragma once
#include "common.h"
#include "../inih/cpp/INIReader.h"
#include "userinterface/sprite.h"

//Move somewhere else!
bool FileExists(std::string Path)
{
	SceIoStat StatTemp;
	return (sceIoGetstat(Path.c_str(), &StatTemp) >= 0);
}

enum class NovelPackType
{
	Folder,
	Zip,
	VNDSNovel,
}

class NovelHeader
{
private:
	NovelFormatType IdentifyFormat();
	void ReadVNVitaHeader();
	void ReadVNDSHeader();
public:
	std::string Path;
	std::string Title;
	int resolutionX = 0, resolutionY = 0;

	NovelFormatType FormatType;
	NovelPackType PackType;
	bool Compiled;

	NovelHeader() = default;
	NovelHeader(const std::string& url);
};

NovelHeader::NovelHeader(const std::string& url)
{
	Path = url;
	Title = url;	//Gets overwritten later, hopefully.

	//Work out how to handle these later
	if(BasePath.substr(Path.size()-6)) = ".novel"	//".novel" is actually a renamed .zip with the usual VNDS dir structure inside
	{
		PackType = NovelPackType::VNDSNovel;
	}
	if(BasePath.substr(Path.size()-4)) = ".zip"		//Potential vnvita format? Same idea as vnds, reuse zip code.
	{
		PackType = NovelPackType::Zip;
	}

	//Strings/bytecode folder
	Compiled = (FileExists(Path+"\\Compiled"));

	FormatType = IdentifyFormat();

	switch(FormatType)
	{
		case FormatType::VNDS:
		{
			ReadVNDSHeader();
		} break;
		case FormatType::VNVita:
		{
			ReadVNVitaHeader();
		} break;
		default:	return;		//Just break here, no more data needed
	}
}

void NovelHeader::ReadVNDSHeader()
{	
	//Read title from info.txt
	if(FileExists(Path+"\\info.txt"))
	{
		INIReader reader = INIReader(Path + "\\info.txt");
		if(reader.ParseError() >= 0) // >= 0 means no error. Huh?
		{
			Title = Reader.Get("","title","");	
		}
	}
	//Read resolution from img.ini
	if(FileExists(Path+"\\img.ini"))
	{
		reader = INIReader(Path + "\\img.ini");
		if (reader.ParseError() >= 0)
		{
			Width = reader.GetInteger("", "width", 256);
			Height = reader.GetInteger("", "height", 192);
		}
	}
	else //If it doesn't exist, this is just a plain DS file, not an android version
	{
		Width = 256;
		Height = 192;
	}
}

void NovelHeader::ReadVNVitaHeader()
{
	Width = 960;
	Height = 544;
	if(FileExists(Path +"\\vnvita.ini"))
	{
		INIReader reader = INIReader(Path + "\\vnvita.ini");
		if(reader.ParseError() >= 0)
		{
			Title = Reader.Get("","title","error - no title");
			Width = Reader.GetInteger("","width",960);
			Height = Reader.GetInteger("","height",544);
		}
	}
}

NovelFormatType NovelHeader::IdentifyFormat()
{
	if(PackType == NovelPackType::VNDSNovel)
		return NovelFormatType::VNDS;
	if(PackType == NovelPackType::Zip)
	{
		return NovelFormatType::VNVita;
	}

	//Plain dir
	if(FileExists(Path+"\\info.txt"))
		return NovelFormatType::VNDS;
	if(FileExists(Path+"\\vnvita.ini"))
		return NovelFormatType::VNVita;

	return NovelFormatType::Error;
}