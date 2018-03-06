#pragma once
#include "AnimatedButton.h"

class WidgetToggleButton : public AnimatedButton
{
public:
	static WidgetToggleButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, HUDElement *group);
private:
	/** Pointer Click Event Implementation */
	virtual void OnPointerMouseDownImplementation(EventData data);

	HUDElement * group;
};