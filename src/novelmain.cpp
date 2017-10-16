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
	Text.SetNovelSize(Novel.Width,Novel.Height);
	/*
	Foreground.SetPosition(157,25);
	Background.SetImage("ux0:data/vnvita/ever17/background/bg28a2r.jpg");
	Foreground.SetImage("ux0:data/vnvita/ever17/foreground/yu12bdm.png");
	*/
}

void NovelMain::Tick(SceCtrlData GamePad,SceCtrlData GamePadLast)
{
	if((GamePad.buttons & SCE_CTRL_CIRCLE) && ((GamePadLast.buttons & SCE_CTRL_CIRCLE) == 0))
	{

	} 
	if((GamePad.buttons & SCE_CTRL_SQUARE) && ((GamePadLast.buttons & SCE_CTRL_SQUARE) == 0))
	{
		Text.Show = !Text.Show;
	} 
}

void NovelMain::Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	Background.Draw();
	Foreground.Draw();
	Background.DrawBorders();	//Cover up sides so sprites peeking from the side don't show
	Text.Draw();
	//UI Draw
	Menu.Draw();

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
		
		if((GamePad.buttons & SCE_CTRL_TRIANGLE) && ((GamePadLast.buttons & SCE_CTRL_TRIANGLE) == 0))
		{
			Menu.Open = !Menu.Open;
		}

		Menu.Tick(GamePad,GamePadLast);

		if(!Menu.Open)
			Tick(GamePad,GamePadLast);

		Draw();

		GamePadLast = GamePad;
	}

	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}