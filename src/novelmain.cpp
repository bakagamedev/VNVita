#include "novelmain.h"

NovelMain::NovelMain(NovelHeader Header)
{
	this->Header = Header;
	StatusCode = StatusType::OK;
}

NovelMain::~NovelMain()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

void NovelMain::Run()
{
	sceCtrlPeekBufferPositive(0, &GamePad, 1);
	if(GamePad.buttons != 0)
	{
		StatusType::Finished;
	}

	vita2d_start_drawing();
	vita2d_clear_screen();
	vita2d_pgf_draw_text(pgf, 0,25,RGBA8(255,255,0,255), 1.0f, Header.Name.c_str());
	vita2d_end_drawing();
	vita2d_swap_buffers();
}