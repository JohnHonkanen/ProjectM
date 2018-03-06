#pragma once
#include "AnimatedButton.h"

class BuildingSelectorButton : public AnimatedButton
{
public:
	static BuildingSelectorButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, class BuildingController * buildingController, std::string structure);
private:
	/** Pointer Click Event Implementation */
	virtual void OnPointerMouseDownImplementation(EventData data);

	class BuildingController * buildingController;
	std::string structure;
};