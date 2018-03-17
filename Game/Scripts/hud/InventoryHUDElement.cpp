/*
InventoryHUDElement class that creates and processes HUD elements within 
the HUD space for strucuture inventories.
Dev: Jack Smith (B00308927) & John Honkanen (B00291253)
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
	GameEngine::manager.inputManager.AddKey("PlaceRes1", "1");
	// Hud Title
	inventoryHUD = EHUD::WHUDContainer::Create(this, { 0, 20, 390, 75 }, 
		"Game/Assets/Textures/black.jpg", true);
	// Inventory contents
	EHUD::TextWidget::Create(inventoryHUD, { 10, 20, 0, 0 }, "Inventory contents:", 
		"Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	float y = 40.0;
	float x = 10.0;
	int index = 0;

	for (int x = 0; x < 3; x++)
	{

		for (int y = 0; y < 3; y++)
		{
			slots[x + y] = HUDInventorySlot::Create(this, { float(60 * x),float(60 * y), 50, 50}, "Game/Assets/Texture/building_hud.jpg");
			
		}
	}

	/*for(int i =0; i < slots.size(); i++)
	{
		if(index>=3 && index < 6)
		{
			x = 135.0;
			if(index == 3)
			{
				y = 40.0;
			}
		}
		else if(index>=6)
		{
			
			x = 255.0;
			if (index == 6)
			{
				y = 40.0;
			}
		}*/
	/*	text[i] = (EHUD::TextWidget::Create(inventoryHUD, { x, y, 0, 0 }, "",
			"Game/Assets/Fonts/MavenPro-Regular.ttf",
			12, 1, vec3(1, 1, 1)));
		y += 15.0;
		index++;
	}*/
		StartChildWidgets();
}

void InventoryHUDElement::Update()
{
	int placeRes1 = GameEngine::manager.inputManager.GetKey("PlaceRes1");
	if (placeRes1 == 1)
	{
		if (!keyHeld)
		{
			keyHeld = true;
		}
	}
	else {
		keyHeld = false;
	}
}

/*
	Draws the widgets on the HUD, specifically the inventory's contents

	@param - shader for the widget.
*/
void InventoryHUDElement::DrawWidget(unsigned int shader)
{
	if (pla->GetSelectedStructure() != nullptr)
	{
		Warehouse * warehouse = dynamic_cast<Warehouse*>(pla->GetSelectedStructure());

		if (warehouse != nullptr)
		{
			v2::Inventory& inv = warehouse->GetInventory();
			if (inv.CheckStorageFull(ResourceName::Chicken_Egg) > 0)// Test add chicken to prove work
			{
				inv.AddItem(ResourceName::Chicken_Egg, 100);
				inv.AddItem(ResourceName::Chicken_Meat, 100);
			}
			for (int i = 0; i < slots.size(); i++)
			{
				v2::Inventory::Slot slot = inv.At(i);
				if (slot.resource != nullptr)
				{
					string icon = slot.resource->GetResourceIcon();
					slots[i]->SetIcon(slot.resource->GetResourceIcon());
					slots[i]->SetQuantity(slot.quantity);
				}
				else
				{
					// Need to change slot image to default image.
				}
			}
		}
	}

}

void InventoryHUDElement::Input()
{
}
