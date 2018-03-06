#pragma once
#include "AnimatedButton.h"

class BuildingSelectorButton : public AnimatedButton
{
public:
	static BuildingSelectorButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture);
private:
};