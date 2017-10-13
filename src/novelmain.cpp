#include "novelmain.h"

NovelMain::NovelMain(NovelHeader * NovelSelected)
{
	this->NovelSelected = NovelSelected;
}

NovelMain::~NovelMain()
{
	vita2d_free_pgf(pgf);
}

void NovelMain::Run()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	vita2d_pgf_draw_text(pgf, 0,64, RGBA8(255,0,0,255), 2.0f, NovelSelected->Name.c_str());

	vita2d_end_drawing();
	vita2d_swap_buffers();
}