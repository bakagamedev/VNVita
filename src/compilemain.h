#pragma once
#include "novelinfo.h"
#include "userinterface/progressbar.h"

class CompileMain
{
private:
	NovelInfo header;

	UIProgressbar progress;
public:
	CompileMain(NovelInfo header);
	void Run();
	void Draw();
};

CompileMain::CompileMain(NovelInfo header)
{
	this->header = header;
}

void CompileMain::Run()
{
	static const int Tasks = 10;
	for(int i=0; i<Tasks; ++i)
	{
		//Do task
		Draw();
	}
}

void CompileMain::Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,RGBA8(0,0,0,255));
	if(!header.Preview.IsNull())
	{
		header.Preview.Draw(0,0);
		//SCREEN_WIDTH / SCREEN_HEIGHT;
	}

	progress.Draw((SCREEN_WIDTH/2)-200,SCREEN_HEIGHT-48,400,32);

	vita2d_end_drawing();
	vita2d_swap_buffers();
}