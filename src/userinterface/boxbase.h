#pragma once
#include "../defines.h"

class UIBoxBase
{
public:
	Rectangle rectangle;
	UIBoxBase(void) = default;
	UIBoxBase(Rectangle rectangle);

	void DrawBox(void);
	void SetRectangle(Rectangle rectangle);
};
