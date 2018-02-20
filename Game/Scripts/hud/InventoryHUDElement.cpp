#include "InventoryHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Inventory.h"


InventoryHUDElement * InventoryHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, vector<class Inventory*> inv)
{
	InventoryHUDElement *i = new InventoryHUDElement();
	i->rect = rect;
	i->inv = inv;
	element->AttachWidget(i);

	return i;
}


void InventoryHUDElement::Start()
{
	// Hud Title
	inventoryHUD = EHUD::WHUDContainer::Create(this, { 0, 20, 350, 150 }, "Game/Assets/Textures/black.jpg", true);
	// Inventory contents
	EHUD::TextWidget::Create(inventoryHUD, { 10, 20, 0, 0 }, "Inventory contents:", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	text = EHUD::TextWidget::Create(inventoryHUD, { 10, 40, 0, 0 }, " " ,"Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	StartChildWidgets();
}

void InventoryHUDElement::Update()
{
}

void InventoryHUDElement::DrawWidget(unsigned int shader)
{
	for (int i = 0; i < inv.size(); i++)
	{
		text->text = inv[i]->GetAtStorageIndex(i);
	}
}