#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>
#include "ButtonWidget.h"

// Namespace Alias
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class TextWidget;
		class WHUDContainer;
	}
}



class MarketHUDElement : public EHUD::HUDWidget { 
public:
	

	static MarketHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class LocalMarket* market);

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	

private:

	class WHUDContainerWrapper {
	public:
		WHUDContainerWrapper() {};
		WHUDContainerWrapper(EHUD::WHUDContainer *container, int elementID) : container(container), ID(elementID) {};

		int GetID() { return this->ID; };
		EHUD::WHUDContainer *GetContainer() { return this->container; };

	private:
		int ID;
		EHUD::WHUDContainer *container;


	};

	class LocalMarket* market;
	EHUD::TextWidget* text, *rate, *quantity, *price;
	EHUD::HUDElement *resourceHUD; 
	EHUD::WHUDContainer* resourceIcon;
	WHUDContainerWrapper marketHUD;
	ButtonWidget *buttonWidget;

	int y = 0;
};