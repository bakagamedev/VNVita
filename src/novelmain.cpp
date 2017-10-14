#include "novelmain.h"

NovelMain::~NovelMain()
{
}

NovelMain::NovelMain(std::string LoadPath)
{
	this->Path = LoadPath;
	Novel.Reset(Path,false);
	Foreground.SetNovelSize(Novel.Width,Novel.Height);
	Background.SetNovelSize(Novel.Width,Novel.Height);
}

bool NovelMain::Tick(SceCtrlData GamePad,SceCtrlData GamePadLast)
{
	if((GamePad.buttons & SCE_CTRL_CIRCLE) && ((GamePadLast.buttons & SCE_CTRL_CIRCLE) == 0))
	{
		return true;
	} 
	return false;
}

void NovelMain::Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));

	Background.Draw();

	vita2d_end_drawing();
	vita2d_swap_buffers();
} 

void NovelMain::Run()
{
	SceCtrlData GamePad, GamePadLast;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	
	bool Ready = false;
	while(!Ready)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);

		Ready = Tick(GamePad,GamePadLast);
		Draw();

		GamePadLast = GamePad;
	}

	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}