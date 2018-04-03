#include "HUDInventorySlot.h"
#include <math.h>
#include <sstream>
#include <iomanip>

HUDInventorySlot * HUDInventorySlot::Create(HUDElement * element, EHUD::HUDRect rect, std::string bgImage)
{
	HUDInventorySlot * slot = new HUDInventorySlot();
	slot->rect = rect;
	slot->bgImage = bgImage;
	element->AttachWidget(slot);

	return slot;
}

void HUDInventorySlot::Start()
{
	iconWrapper = EHUD::WHUDContainer::Create(this, { 0,0,rect.width,rect.height }, bgImage, false);
	icon = EHUD::WHUDContainer::Create(iconWrapper, { 5,5,rect.width -10 ,rect.height -10 }, "", false);
	quantityText = EHUD::TextWidget::Create(iconWrapper, { 7.5, rect.height - 10, 0, 0 }, "",
		"Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 12, 1, vec3(0, 0, 0));
}

void HUDInventorySlot::DrawWidget(unsigned int shader)
{
	if (!this->IsActive())
	{
		return;
	}
	icon->ChangeImage(iconImage);
	if (quantity > 0)
	{
		if (quantity > 1000) {
			float q = (quantity / 1000.0f);
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << q;
			quantityText->text = ss.str() + "K";
		}
		else {
			quantityText->text = to_string(quantity);
		}
		
	}
	else
	{
		quantityText->text = "";
	}
}

void HUDInventorySlot::Update()
{
	int test = 0;
}
