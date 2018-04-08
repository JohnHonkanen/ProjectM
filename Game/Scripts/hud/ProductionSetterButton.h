#pragma once
#include "ButtonWidget.h"
#include "hud\HUDRect.h"
#include "../Resources.h"

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
	void SetProduction(class Production *production);			//When button is clicked, building production is set to related resource
	void SetResource(ResourceName resource);					
	void SetIcon(std::string icon);

	static ProductionSetterButton *Create(HUDElement *element, EHUD::HUDRect rect, std::string icon, class Production *production, ResourceName resource);
private:
	class Production *production;
	class EHUD::HUDElement *root;
	ResourceName resource;

};