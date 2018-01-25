#pragma once
#include <string>
#include <vector>
#include "../defines.h"
#include "../stringviewer.h"
#include "animatedsprite.h"
#include "boxbase.h"

class UITextBox : public UIBoxBase
{
public:
	void Print(std::string String);

	UITextBox(void) = default;
	UITextBox(Rectangle rectangle);

	UIAnimatedSprite SprContinue = UIAnimatedSprite("app0:assets/continue1.png","app0:assets/continue2.png");
	
	void Draw(void)
	{
		DrawBox();
		SprContinue.Draw(956-16,540-16);
	}
};
