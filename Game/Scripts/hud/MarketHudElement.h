#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>
#include "ButtonWidget.h"
#include "../Resources.h"
#include "core\GameObject.h"
#include "utility\Clock.h"

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
	
	void GenerateMarketHUDElement(int resourceID, float increment, Resources resource);
	void GenerateKSuffix(int resourceID); // Add K if value of resource quantity exceeds 1000
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
	static const int MAX_MARKET_ITEM_SIZE = 9;

	EHUD::TextWidget* text, *rate, *quantity[MAX_MARKET_ITEM_SIZE], *price[MAX_MARKET_ITEM_SIZE];
	EHUD::HUDElement *resourceHUD[MAX_MARKET_ITEM_SIZE];
	EHUD::WHUDContainer* resourceIcon[MAX_MARKET_ITEM_SIZE];
	WHUDContainerWrapper marketHUD;
	ButtonWidget *buttonWidget;
	Engine::Utility::Clock clock;

	int y = 0;
	
};