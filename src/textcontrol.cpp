#include "textcontrol.h"

TextControl::TextControl()
{

}
TextControl::~TextControl()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);	//seriously, I know i'm doing this wrong.
}

void TextControl::Draw(float X, float Y)
{
	vita2d_pgf_draw_text(pgf, X, Y, RGBA8(0,0,0,255), 2.0f, "Test words");
}