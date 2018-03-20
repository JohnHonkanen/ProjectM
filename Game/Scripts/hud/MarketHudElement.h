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
	EHUD::HUDElement* marketHUD, *resourceHUD; //*resourceHUD1, *resourceHUD2, *resourceHUD3, *resourceHUD4, *resourceHUD5, *resourceHUD6, *resourceHUD7;
	EHUD::WHUDContainer* resourceIcon;

};