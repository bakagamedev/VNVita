#include "novelmain.h"

NovelMain::~NovelMain()
{
}

NovelMain::NovelMain(std::string LoadPath)
{
	this->Path = LoadPath;
}

void NovelMain::Run()
{
	SceCtrlData GamePad, GamePadLast;
	
	bool Ready = false;
	while(!Ready)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);
		if((GamePad.buttons & SCE_CTRL_CIRCLE) && ((GamePadLast.buttons & SCE_CTRL_CIRCLE) == 0))
		{
			Ready = true;
		}

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		//vita2d_pgf_draw_text(pgf, 64,64, RGBA8(255,0,0,255), 1.0f, "Path.c_str()");

		vita2d_end_drawing();
		vita2d_swap_buffers();

		GamePadLast = GamePad;
	}
}