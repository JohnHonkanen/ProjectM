#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include "PlayerEconHUD.h"
#include <string>

// Namespace Alias

namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
	}
}

class PlayerEconHUDElement : public EHUD::HUDWidget{

public:
	static PlayerEconHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class PlayerEconomy* playerEconomy);

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	
	void SetPlayerEcon(PlayerEconomy* economyToSet);
	class PlayerEconomy* GetPlayerEcon();

private:
	class PlayerEconomy* playerEconomy;
	EHUD::TextWidget* text;
	EHUD::HUDElement* playerEconHUD, *resourceIcon;
};