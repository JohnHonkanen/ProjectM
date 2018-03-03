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
#include "../test/InventoryPopulator.h"
#include "../Warehouse.h"

InventoryHUDElement::InventoryHUDElement()
{
}

InventoryHUDElement::~InventoryHUDElement()
{
	delete invP;
}

/*
	Initialises the needed fields for the HudElements to funtion
*/
InventoryHUDElement * InventoryHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, vector<Inventory*> inv, PlayerActions* pla, ResourceManager* rManager)
{
	InventoryHUDElement *i = new InventoryHUDElement();
	
	i->rManager = rManager;
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
	/*int invLimit=0;
	if (dynamic_cast<Warehouse*>(pla->GetSelectedStructure()) != nullptr)
	{
		invLimit = pla->GetSelectedStructure()->GetInventory()->InventorySize();
	}*/
	text.resize(9);
	invP = new InventoryPopulator();
	GameEngine::manager.inputManager.AddKey("PlaceRes1", "1");
	// Hud Title
	inventoryHUD = EHUD::WHUDContainer::Create(this, { 0, 20, 350, 150 }, 
		"Game/Assets/Textures/black.jpg", true);
	// Inventory contents
	EHUD::TextWidget::Create(inventoryHUD, { 10, 20, 0, 0 }, "Inventory contents:", 
		"Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	float y = 40.0;
	float x = 10.0;
	int index = 0;
	for(int i =0; i<text.size(); i++)
	{
		if(index>=3 && index < 6)
		{
			x = 120.0;
			if(index == 3)
			{
				y = 40.0;
			}
		}
		else if(index>=6)
		{
			
			x = 240.0;
			if (index == 6)
			{
				y = 40.0;
			}
		}
		text[i] = (EHUD::TextWidget::Create(inventoryHUD, { x, y, 0, 0 }, "",
			"Game/Assets/Fonts/MavenPro-Regular.ttf",
			12, 1, vec3(1, 1, 1)));
		y += 15.0;
		index++;
	}
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
		if (dynamic_cast<Warehouse*>(pla->GetSelectedStructure())!=nullptr)
		{
			for (int i = 0; i < text.size(); i++)
			{
				std::string hudText = pla->GetSelectedStructure()->ViewInventoryAt(i);
				if(!hudText.empty())
				{
					text[i]->text = hudText;
				}
			}
			invP->TestItem(pla, rManager);
		}
	}

}
