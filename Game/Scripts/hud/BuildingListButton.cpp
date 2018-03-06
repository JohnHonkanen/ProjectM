#include "BuildingListButton.h"

BuildingListButton * BuildingListButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, HUDElement *group)
{
	BuildingListButton *blb = new BuildingListButton();
	blb->rect = rect;
	blb->baseTexture = baseTexture;
	blb->SetOriginalDimensions(rect.width, rect.height);
	blb->group = group;

	element->AttachWidget(blb);
	return blb;
}

void BuildingListButton::OnPointerMouseDownImplementation(EventData data)
{
	group->SetActive(!group->IsActive());
}
