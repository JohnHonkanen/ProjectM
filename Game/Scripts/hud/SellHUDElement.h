/*
SellHUDElement supports elements within the total SellHUD
Dev: Jack Smith (B00308927)
*/
#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include "../ResourceManager.h"
#include <string>

//Namespace Alias 
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
		class WHUDContainer;
	}
}

class SellHUDElement : public EHUD::HUDWidget {

public:
	// Creates the Hud elements
	SellHUDElement();
	~SellHUDElement();
	static SellHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class PlayerActions* pla, class ResourceManager* rManager);
	EHUD::HUDElement* GetWrapper();
	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	void SetAllActive(bool state);
	void Input();
private:
	// Varibles declared and forward delclared
	EHUD::TextWidget* title;
	class PlayerActions* pla;
	EHUD::HUDElement* sellHUD;
	class ResourceManager* rManager;
	bool keyHeld;
};
