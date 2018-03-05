#pragma once
#include "BooblyButton.h"

class BuildingListButton : public BooblyButton
{
public:
	static BuildingListButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture);

};