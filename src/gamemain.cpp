#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = ErrorType::OK;
	vita2d_init();
}

GameMain::~GameMain()
{
	vita2d_fini();
	sceKernelExitProcess(0);
}

void GameMain::GameTick()
{
	RedRectangle rect;

	vita2d_texture *imagetest = vita2d_load_JPEG_file("ux0:data/testimage.jpg");
	vita2d_pgf * pgf = vita2d_load_default_pgf();
	vita2d_pvf * pvf = vita2d_load_default_pvf();

	uint8_t tick = 0;
	while(GamePad.buttons != SCE_CTRL_START)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);

		if (GamePad.buttons & SCE_CTRL_DOWN)
			tick--;
		if (GamePad.buttons & SCE_CTRL_UP)
			tick++;

		vita2d_start_drawing();
		vita2d_clear_screen();

		rect.R = tick;
		rect.G = 255 - tick;
		rect.B = 255 - tick;	

		vita2d_draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT , RGBA8(rect.R,rect.G,rect.B, 255));

		vita2d_draw_texture_rotate(imagetest, 940/2, 544/2, ((float)tick)/10);

		vita2d_pgf_draw_text(pgf, 300, 30, RGBA8(0,255,0,255), 1.0f, "oh god what am I doing i'm not good at computer");

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}


	vita2d_free_texture(imagetest);
	vita2d_free_pgf(pgf);
	vita2d_free_pvf(pvf);
}