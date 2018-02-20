/*
InventoryHUDElement class that creates and processes HUD elements within 
the HUD space for strucuture inventories.
Dev: Jack Smith (B00308927) & John Honkanen (B00291253)
*/
#include "InventoryHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Inventory.h"
#include "../PlayerActions.h"
#include "../Structure.h"
#include "../Warehouse.h"
#include "../test/InventoryPopulator.h"

/*
	Initialises the needed fields for the HudElements to funtion
*/
InventoryHUDElement * InventoryHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, vector<Inventory*> inv, PlayerActions* pla)
{
	InventoryHUDElement *i = new InventoryHUDElement();
	i->rect = rect;
	i->inv = inv;
	i->pla = pla;
	element->AttachWidget(i);

	return i;
}

/*
	Initialises the HudElements for the inventory by creating the container and placing the elements within
*/
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

/*
	Draws the widgets on the HUD, specifically the inventory's contents

	@param - shader for the widget.
*/
void InventoryHUDElement::DrawWidget(unsigned int shader)
{
	if (pla->GetSelectedStructure() != nullptr)
	{
		if (dynamic_cast<Warehouse*>(pla->GetSelectedStructure())!=nullptr)
		{
			text->text = pla->GetSelectedStructure()->ViewInventory();
			invP->TestItem(pla);
		}
	}

}