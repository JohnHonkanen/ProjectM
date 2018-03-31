#include "MarketHudElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../LocalMarket.h"
#include <sstream>
#include  <iomanip>

MarketHUDElement * MarketHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, LocalMarket * market)
{
	MarketHUDElement *m = new MarketHUDElement();
	m->rect = rect;
	m->market = market;

	element->AttachWidget(m);

	return m;
}

void MarketHUDElement::Start()
{
	// Top bar
	
	marketHUD = WHUDContainerWrapper(EHUD::WHUDContainer::Create(this, { -25, 20, 240, 32 }, "Game/Assets/Textures/transparent_black.png", true), this->y);
	text = EHUD::TextWidget::Create(marketHUD.GetContainer(), { 5, 20, 0, 0 }, "Resources  Quantity   Price", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	auto marketList = market->GetResources();
	float increment = 45;
	int resourceID = 0; 
	for (auto resource : marketList) {
		resourceID = this->y;
		switch (resourceID) {
		case 0:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 1:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 2:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 3:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 4:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 5:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		case 6:
			GenerateMarketHUDElement(resourceID, increment, resource);
			break;
		default:
			break;
		}
		this->y++;
	}
}

void MarketHUDElement::Update()
{
	if (!active) {
		return;
	}

	auto marketList = market->GetResources();

	for (int i = 0; i <= MAX_MARKET_ITEM_SIZE; ++i) {
		price[i]->text = "$ " + to_string(market->GetBasePriceOf(i));
		quantity[i]->text = to_string(market->GetItemStock(i));

		// Check if markets current item stock is greater or equal to 1000, then add "K" to it.
		if (market->GetItemStock(i) >= 1000) {
			float q = market->GetItemStock(i) / 1000.0f;
			std::stringstream ss;
			ss << std::fixed << std::setprecision(1) << q;
			quantity[i]->text = ss.str() + "K";
		}

		// Check if markets current item price is greater or equal to 1000, then add "K" to it.
		if (market->GetBasePriceOf(i) >= 1000) {
			float q = market->GetBasePriceOf(i) / 1000.0f;
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << q;
			price[i]->text = ss.str() + "K";
		}
	}
}

void MarketHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}
}

void MarketHUDElement::GenerateMarketHUDElement(int resourceID, float increment, Resources resource)
{
		resourceHUD[resourceID] = EHUD::WHUDContainer::Create(this, { -25, 65 + resourceID * increment, 240, 40 }, "Game/Assets/Textures/transparent_black.png", true);
		resourceIcon[resourceID] = EHUD::WHUDContainer::Create(this, { -5, 70 + resourceID * increment, 32, 32 }, resource.GetResourceIcon(), true);
		quantity[resourceID] = EHUD::TextWidget::Create(resourceHUD[resourceID], { 115, 25, 0, 0 }, to_string(resource.GetItemAmount()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
		price[resourceID] = EHUD::TextWidget::Create(resourceHUD[resourceID], { 175, 25, 0, 0 }, "$ " + to_string(resource.GetBasePrice()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
		
		text = EHUD::TextWidget::Create(resourceHUD[resourceID], { 0, 0, 0, 0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
		StartChildWidgets();
}
