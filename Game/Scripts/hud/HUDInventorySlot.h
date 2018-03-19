#pragma once
#include "hud\HUDWidget.h"
#include <string>
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"

namespace EHUD = Engine::HUD;

class HUDInventorySlot : public EHUD::HUDWidget
{
public:
	static HUDInventorySlot * Create(HUDElement * element, EHUD::HUDRect rect, std::string bgImage);

	void Start();
	void DrawWidget(unsigned int shader);
	void Update();

	void SetIcon(string icon) { iconImage = icon; }
	void SetQuantity(int quan) { quantity = quan; }

private:
	EHUD::WHUDContainer * iconWrapper;
	EHUD::WHUDContainer * icon;
	EHUD::TextWidget * quantityText;

	int quantity;
	string bgImage;
	string iconImage;
};
