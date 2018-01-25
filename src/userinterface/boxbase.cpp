#include "boxbase.h"

UIBoxBase::UIBoxBase(Rectangle rectangle)
{
	this->rectangle = rectangle;
}

void UIBoxBase::SetRectangle(Rectangle rectangle)
{
	this->rectangle = rectangle;
}

void UIBoxBase::DrawBox()
{
	vita2d_draw_rectangle(rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, COLOUR_UIBorder);
	vita2d_draw_rectangle(rectangle.X+UI_BorderSize,rectangle.Y+UI_BorderSize, rectangle.Width-(UI_BorderSize*2), rectangle.Height-(UI_BorderSize*2), COLOUR_UIBackground);
}