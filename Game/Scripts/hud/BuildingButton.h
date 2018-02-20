#pragma once
#include "ButtonWidget.h"
#include "hud\HUDRect.h"

namespace EHUD = Engine::HUD;
class BuildingButton : public ButtonWidget
{
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);
	void EventRegistration();

	static BuildingButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string structure, class BuildingHUD *hud, std::string baseTexture);
	static BuildingButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string structure, class BuildingHUD *hud,
		std::string baseTexture, std::string mouseOverTexture, std::string mouseDownTexture);

private:
	class BuildingHUD * hud;
	std::string structure;
};