#pragma once
#include "AnimatedButton.h"

class BuildingListButton : public AnimatedButton
{
public:
	static BuildingListButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture);
};