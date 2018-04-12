/*
InventoryHUDElement class that creates and processes HUD elements within
the HUD space for strucuture inventories.
Dev: Jack Smith (B00308927) & John Honkanen (B00291253)
*/
#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include "../ResourceManager.h"
#include "HUDInventorySlot.h"
#include <string>

//Namespace Alias 
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
		class WHUDContainer;
	}
}

class InventoryHUDElement : public EHUD::HUDWidget {

public:
	// Creates the Hud elements
	InventoryHUDElement();
	~InventoryHUDElement();
	static InventoryHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class PlayerActions* pla, class ResourceManager* rManager);
	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	void Input();
private:
	// Varibles declared and forward delclared
	EHUD::TextWidget* title;
	class PlayerActions* pla;
	EHUD::HUDElement* inventoryHUD;
	class ResourceManager* rManager;
	bool keyHeld;
	vector<HUDInventorySlot*> slots;
};

