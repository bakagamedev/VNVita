#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	StatusCode = ErrorType::OK;

	auto Directory = sceIoDopen("ux0:data/vnvita/");
	if(Directory < 0)
	{
		StatusCode = ErrorType::EpicFail;
		throw std::runtime_error("No directory!");
	}
}

void NovelBrowser::Run()
{
	if(StatusCode == ErrorType::EpicFail)
	{
		vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(255,0,0,255), 2.0f, "bad. No directory for you.");
	}
}