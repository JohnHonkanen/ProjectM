#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>

// Namespace Alias
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
		class WHUDContainer;
	}
}

class MarketHUDElement : public EHUD::HUDWidget{
public:
	
	static MarketHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class LocalMarket* market);

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	
private:
	class LocalMarket* market;
	EHUD::TextWidget* text, *rate, *quantity, *price;
	EHUD::HUDElement* marketHUD, *resourceHUD; 
	EHUD::WHUDContainer* resourceIcon;

};