#include "common.h"

class TextControl
{
private:
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//I hope to one day swap these with an actual font loader so that it's all shared.
	char * Text;	//this can only end well.

	float Scale = 1.0;
	float Border = 32;
	float X,Y,Width,Height;
	uint8_t Alpha = 128;
public:
	~TextControl();
	TextControl();

	bool Show = true;
	void SetAlpha(uint8_t Alpha);
	void SetNovelSize(float Width, float Height);
	void SetBorderSize(float Border);

	void Draw();
};