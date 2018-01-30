#include "novelinfo.h"

NovelInfo::NovelInfo(const std::string& url)
{
	Path = url;
	Title = url;	//Gets overwritten later, hopefully.
	Description = "";

	//Work out how to handle these later
	if(StringHasExtension(Path,".novel"))	//".novel" is actually a renamed .zip with the usual VNDS dir structure inside
	{
		PackType = NovelPackType::VNDSNovel;
	}
	if(StringHasExtension(Path,".zip"))		//Potential vnvita format? Same idea as vnds, reuse zip code.
	{
		PackType = NovelPackType::Zip;
	}

	//Strings/bytecode folder
	IsCompiled = (FileExists(Path+"\\Compiled"));

	Format = IdentifyFormat();

	switch(Format)
	{
		case NovelFormatType::VNDS:
		{
			ReadVNDSHeader();
		} break;
		case NovelFormatType::VNVita:
		{
			ReadVNVitaHeader();
		} break;
		default:	return;		//Just break here, no more data needed
	}
}

void NovelInfo::ReadVNDSHeader()
{	
	//Read title from info.txt
	if(FileExists(Path+"\\info.txt"))
	{
		INIReader reader = INIReader(Path + "\\info.txt");
		if(reader.ParseError() >= 0) // >= 0 means no error. Huh?
		{
			Title = reader.Get("","title","");	
		}
	}
	//Read resolution from img.ini
	if(FileExists(Path+"\\img.ini"))
	{
		INIReader reader = INIReader(Path + "\\img.ini");
		if (reader.ParseError() >= 0)
		{
			Width = reader.GetInteger("", "width", 256);
			Height = reader.GetInteger("", "height", 192);
		}
	}
	else //If it doesn't exist, this is just a plain DS file, not an android enchanced version
	{
		Width = 256;
		Height = 192;
	}
}

void NovelInfo::ReadVNVitaHeader()
{
	Width = 960;
	Height = 544;
	if(FileExists(Path +"\\vnvita.ini"))
	{
		INIReader reader = INIReader(Path + "\\vnvita.ini");
		if(reader.ParseError() >= 0)
		{
			Title = reader.Get("","title","error - no title");
			Description = reader.Get("","description","");
			Width = reader.GetInteger("","width",960);
			Height = reader.GetInteger("","height",544);
		}
	}
}

NovelFormatType NovelInfo::IdentifyFormat()
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