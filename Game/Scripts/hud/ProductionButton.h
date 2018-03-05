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
class ProductionButton : public ButtonWidget {
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);
	void EventRegistration();
	void Start();

	static ProductionButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture);


private:
	class EHUD::HUDElement *root;
	class EHUD::HUDElement *container;
};