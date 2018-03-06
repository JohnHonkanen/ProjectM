#pragma once
#include "ButtonWidget.h"
#include "hud\HUDRect.h"

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TestWidget;
	}
}

namespace EHUD = Engine::HUD;
class ProductionSetterButton : public ButtonWidget {
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);
	void EventRegistration();
	void Start();
	void SetProduction(class Production *production);
	void SetResource(int resource);
	void SetIcon(std::string icon);

	static ProductionSetterButton *Create(HUDElement *element, EHUD::HUDRect rect, std::string icon, class Production *production, int resource);
private:
	class Production *production;
	class EHUD::HUDElement *root;
	int resource;

};