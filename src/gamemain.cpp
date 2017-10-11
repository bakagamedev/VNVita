#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = ErrorType::OK;
	vita2d_init();
}

void GameMain::GameTick()
{
	vita2d_texture *imagetest = vita2d_load_JPEG_file("ux0:data/testimage.jpg");
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	uint8_t tick = 0;
	memset(&GamePad, 0, sizeof(GamePad));
	while(GamePad.buttons != SCE_CTRL_START)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);

		if (GamePad.buttons & SCE_CTRL_DOWN)
			tick--;
		if (GamePad.buttons & SCE_CTRL_UP)
			tick++;

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT , RGBA8(128,128,128, 255));

		vita2d_draw_texture_rotate(imagetest, 940/2, 544/2, ((float)tick)/10);

		vita2d_pgf_draw_text(pgf, 300, 30, RGBA8(0,255,0,255), 1.0f, "oh god what am I doing i'm not good at computer\nnewline\nhmmmmmm....");

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	vita2d_fini();
	vita2d_free_texture(imagetest);
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
}