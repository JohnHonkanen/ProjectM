#pragma once
#include "AnimatedButton.h"

class BuildingListButton : public AnimatedButton
{
public:
	static BuildingListButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, HUDElement *group);
private:
	/** Pointer Click Event Implementation */
	virtual void OnPointerMouseDownImplementation(EventData data);

	HUDElement * group;
};