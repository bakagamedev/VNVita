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

	LoadImages();
}

void NovelInfo::LoadImages()
{
	switch(Format)
	{
		case NovelFormatType::VNDS:
		{
			//Horrible. Just horrible. Rewrite.
			std::string IconPath;
			if(FileExists(Path+"\\icon-high.png")) IconPath = Path+"\\icon-high.png";
			else if (FileExists(Path+"\\icon-high.jpg")) IconPath = Path+"\\icon-high.jpg";
			else if (FileExists(Path+"\\icon.png")) IconPath = Path+"icon.png";
			else if (FileExists(Path+"\\icon.jpg")) IconPath = Path+"icon.jpg";
			Icon = UISprite(IconPath);

			std::string ThumbPath;
			if(FileExists(Path+"\\thumbnail-high.png")) ThumbPath = Path+"\\thumbnail-high.png";
			else if (FileExists(Path+"\\thumbnail-high.jpg")) ThumbPath = Path+"\\thumbnail-high.jpg";
			else if (FileExists(Path+"\\thumbnail.png")) ThumbPath = Path+"thumbnail.png";
			else if (FileExists(Path+"\\thumbnail.jpg")) ThumbPath = Path+"thumbnail.jpg";
			Preview = UISprite(ThumbPath);
		} break;
		case NovelFormatType::VNVita:
		{
			//much nicer.
			const std::string IconPath = Path + "\\icon.png";
			const std::string ThumbPath= Path + "\\preview.png";
			if(FileExists(IconPath))	Icon = UISprite(IconPath);
			if(FileExists(ThumbPath))	Preview = UISprite(ThumbPath);
		} break;
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
			//Sets name to dir name by default.
			std::string defaultName = Path.substr(Path.find_last_of("/")+1);
			Title = reader.Get("","title",defaultName);	
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