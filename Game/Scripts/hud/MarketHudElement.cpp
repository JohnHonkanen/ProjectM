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

	marketHUD = EHUD::WHUDContainer::Create(this, { -25, 20, 240, 32 }, "Game/Assets/Textures/transparent_black.png", true);
	text = EHUD::TextWidget::Create(marketHUD, { 5, 20, 0, 0 }, "Resources  Quantity   Price", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	auto marketList = market->GetResources();
	int y = 0;
	float increment = 45;

	for (auto resource : marketList) {
		resourceHUD = EHUD::WHUDContainer::Create(this, { -25, 65 + y * increment, 240, 40 }, "Game/Assets/Textures/transparent_black.png", true);
		resourceIcon = EHUD::WHUDContainer::Create(this, { -5, 70 + y * increment, 32, 32 }, resource.GetResourceIcon(), true);
		quantity = EHUD::TextWidget::Create(resourceHUD, { 115, 25, 0, 0 }, "0", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
		price = EHUD::TextWidget::Create(resourceHUD, { 175, 25, 0, 0 }, "$ " + to_string(resource.GetBasePrice()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
		
		y++;
	}
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
