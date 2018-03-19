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
	iconWrapper = EHUD::WHUDContainer::Create(this, { 0,0,50,50 }, bgImage, false);
	icon = EHUD::WHUDContainer::Create(iconWrapper, { 5,5,40,40 }, "", false);
	quantityText = EHUD::TextWidget::Create(iconWrapper, { 5, 30, 0, 0 }, "",
		"Game/Assets/Fonts/MavenPro-Regular.ttf", 12, 1, vec3(1, 1, 1));
}

void HUDInventorySlot::DrawWidget(unsigned int shader)
{
	// not implemented because this class uses other widget classes to draw
	if (!this->IsActive())
	{
		return;
	}
	icon->ChangeImage(iconImage);
	if (quantity > 0)
	{
		float q =(quantity / 1000);
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << q;
		quantityText->text = ss.str() + "K";
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
