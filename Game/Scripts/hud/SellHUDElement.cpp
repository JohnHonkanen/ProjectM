/*
SellHUDElement supports elements within the total SellHUD
Dev : Jack Smith(B00308927)
*/
#include "SellHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../PlayerActions.h"
#include "../Structure.h"

	SellHUDElement::SellHUDElement()
{
}

	SellHUDElement::~SellHUDElement()
{
}

/*
Initialises the needed fields for the HudElements to funtion
*/
	SellHUDElement * SellHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, PlayerActions* pla, ResourceManager* rManager)
{
	SellHUDElement *i = new SellHUDElement();

	i->rManager = rManager;
	i->rect = rect;
	i->pla = pla;
	element->AttachWidget(i);

	return i;
}

/*
Initialises the HudElements for the inventory by creating the container and placing the elements within
*/
void SellHUDElement::Start()
{
	//GameEngine::manager.inputManager.AddKey("PlaceRes1", "1");
	// This method is available in case the SellHUD requires more widgets in future.
		
	StartChildWidgets();
}

void SellHUDElement::Update()
{
}

/*
Draws the widgets on the HUD

@param - shader for the widget.
*/
void SellHUDElement::DrawWidget(unsigned int shader)
{
	if (pla->GetSelectedStructure() != nullptr)
	{
		auto * selectedStructure = pla->GetSelectedStructure();
	}

}

void SellHUDElement::Input()
{
}
