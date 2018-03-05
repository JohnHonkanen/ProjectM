#include "BuildingListButton.h"

BuildingListButton * BuildingListButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture)
{
	BuildingListButton *blb = new BuildingListButton();
	blb->rect = rect;
	blb->baseTexture = baseTexture;

	element->AttachWidget(blb);
	return blb;
}
