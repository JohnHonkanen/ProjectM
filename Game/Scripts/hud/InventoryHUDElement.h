#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>

//Namespace Alias 
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
	}
}

class InventoryHUDElement : public EHUD::HUDWidget {

public:

	static InventoryHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, vector<class Inventory*> inv);

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);

private:
	vector<class Inventory*> inv;
	EHUD::TextWidget* title;
	EHUD::TextWidget* text;

	EHUD::HUDElement* inventoryHUD;

};

