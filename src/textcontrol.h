#include "common.h"

class TextControl
{
private:
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//I hope to one day swap these with an actual font loader so that it's all shared.
	char * Text;	//this can only end well.
public:
	~TextControl();
	TextControl();

	void Draw(float X, float Y);
};