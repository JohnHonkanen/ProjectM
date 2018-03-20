#include "MarketHudElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../LocalMarket.h"

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
	marketHUD = EHUD::WHUDContainer::Create(this, { -25, 0, 240, 32 }, "Game/Assets/Textures/transparent_black.png", true);
	text = EHUD::TextWidget::Create(marketHUD, { 5, 20, 0, 0 }, "Resources  Quantity   Price", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Resource Icon
	resourceIcon = EHUD::WHUDContainer::Create(this, {-5, 50, 32, 32}, market->GetResourceIcon(ResourceName::Chicken_Egg), true);

	// Resource Quantity in market
	quantity = EHUD::TextWidget::Create(marketHUD, { 115, 70, 0, 0 }, "0", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Price of Resource in market
	price = EHUD::TextWidget::Create(marketHUD, { 175, 70, 0, 0 }, "$ " + to_string(market->GetResourcePrice(ResourceName::Chicken_Egg)), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
}

void MarketHUDElement::Update()
{
	if (!active) {
		return;
	}
}

void MarketHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}
}
