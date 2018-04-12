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
	void OnPointerMouseDown(EventData data);					//Sets the buildings production to the resource that has been clicked			
	void EventRegistration();
	void Start();
	void SetProduction(class Production *production);			//When button is clicked, selected building production is changed
	void SetResource(ResourceName resource);					//Sets the resource produced to the one selected
	void SetIcon(std::string icon);								//Sets the icon to that of the resource clicked

	static ProductionSetterButton *Create(HUDElement *element, EHUD::HUDRect rect, std::string icon, class Production *production, ResourceName resource);
private:
	class Production *production;
	class EHUD::HUDElement *root;
	ResourceName resource;

};