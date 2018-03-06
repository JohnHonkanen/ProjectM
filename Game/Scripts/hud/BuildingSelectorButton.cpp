#include "BuildingSelectorButton.h"
#include "../BuildingController.h"
BuildingSelectorButton * BuildingSelectorButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, BuildingController * buildingController, std::string structure)
{
	BuildingSelectorButton * bsb = new BuildingSelectorButton();
	bsb->rect = rect;
	bsb->baseTexture = baseTexture;
	bsb->activeTexture = baseTexture;
	bsb->buildingController = buildingController;
	bsb->structure = structure;
	element->AttachWidget(bsb);

	return bsb;
}

void BuildingSelectorButton::OnPointerMouseDownImplementation(EventData data)
{
	if (!active)
	{
		return;
	}
	buildingController->SetObjectToBuild(structure);
	buildingController->SetMouseHeld(true);
}
