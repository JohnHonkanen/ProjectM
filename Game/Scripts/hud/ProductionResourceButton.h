#pragma once
#include "ButtonWidget.h"
#include "hud\HUDRect.h"
#include <vector>

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TestWidget;
	}
}

namespace EHUD = Engine::HUD;
class ProductionResourceButton : public ButtonWidget {
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);
	void EventRegistration();
	void Start();
	void Input();
	void Update();
	void DeleteItems(class V2 * inv);

	void SetIcon(string icon) { iconImage = icon; }

	static ProductionResourceButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, class Production *production);


private:
	string iconImage;

	class Production *production;
	class EHUD::HUDElement *root;
	class EHUD::HUDElement *container;
};