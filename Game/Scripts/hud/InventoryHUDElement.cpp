/*
InventoryHUDElement class that creates and processes HUD elements within 
the HUD space for strucuture inventories.
*/
#include "InventoryHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../PlayerActions.h"
#include "../Structure.h"
#include "../Warehouse.h"

InventoryHUDElement::InventoryHUDElement()
{
}

InventoryHUDElement::~InventoryHUDElement()
{
}

/*
	Initialises the needed fields for the HudElements to funtion
*/
InventoryHUDElement * InventoryHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, PlayerActions* pla, ResourceManager* rManager)
{
	InventoryHUDElement *i = new InventoryHUDElement();
	
	i->rManager = rManager;
	i->rect = rect;
	i->pla = pla;
	element->AttachWidget(i);

	return i;
}

/*
	Initialises the HudElements for the inventory by creating the container and placing the elements within
*/
void InventoryHUDElement::Start()
{
	slots.resize(9);
	slots.reserve(9);
	// Inventory contents
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			slots[x + (3*y)] = HUDInventorySlot::Create(this, { float(55 * x),float(55 * y), 50,50}, "Game/Assets/Textures/Production_HUD_Texture.png");
		}
	}
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
		Structure * selected = pla->GetSelectedStructure();

		if (selected->GetType() == WAREHOUSE)
		{
			v2::Inventory& inv = selected->GetInventory();
			for (int i = 0; i < slots.size(); i++)
			{
				v2::Inventory::Slot slot = inv.At(i);
				if (slot.resource != nullptr)
				{
					slots[i]->SetIcon(slot.resource->GetResourceIcon());
					slots[i]->SetQuantity(slot.quantity);
				}
				else
				{
					slots[i]->SetIcon("Game/Assets/Textures/Production_HUD_Texture.png");
					slots[i]->SetQuantity(NULL);
				}
			}
		}
	}

}

void InventoryHUDElement::Input()
{
}
