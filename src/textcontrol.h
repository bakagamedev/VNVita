#pragma once
#include "common.h"
#include "stringhelpers.h"

class TextControl
{
private:
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//I hope to one day swap these with an actual font loader so that it's all shared.
	
	std::vector<std::string> TextList;
	int CharsDisplay = 0;
	int Scroll = 0; 

	float Scale = 1.0;
	float Border = 32;
	float X,Y,Width,Height;
	uint8_t Alpha = 128;
	bool SmallMode = true;

	bool DoneTyping = false;

	//UI Gizmos
	vita2d_texture * ptrArrowUp;
	std::shared_ptr<vita2d_texture> ImgArrowUp;
	vita2d_texture * ptrArrowDown;
	std::shared_ptr<vita2d_texture> ImgArrowDown;


	void ScrollClamp();
public:
	bool QuestionActive = false;
	int QuestionAnswer = -1;
	int QuestionSize = 1;
	std::string QuestionText;

	~TextControl();
	TextControl();

	void TextAdd(std::string Text);
	void TextClear();

	void ScrollUp();
	void ScrollDown();

	void EndQuestion();
	void SetQuestion(const std::string Text);

	int MaxLines = 10;	//Calculated on draw
	bool Ready = true;
	bool Show = true;
	void SetAlpha(uint8_t Alpha);
	void SetNovelSize(float Width, float Height);
	void SetBorderSize(float Border);

	void Tick(bool Continue, bool Up, bool Down);
	void Draw();
};