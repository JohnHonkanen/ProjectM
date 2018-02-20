#include "BuildingButton.h"
#include "core\GameObject.h"
#include "BuildingHUD.h"
#include "..\BuildingController.h"

void BuildingButton::OnPointerEnter(EventData data)
{
	if (mouseEnterTexture != "")
	{
		activeTexture = mouseEnterTexture;
	}
}

void BuildingButton::OnPointerExit(EventData data)
{
	activeTexture = baseTexture;
}

void BuildingButton::OnPointerMouseDown(EventData data)
{
	if (mouseDownTexture != "")
	{
		activeTexture = mouseDownTexture;
	}

	BuildingController *controller = hud->GetController();
	controller->SetObjectToBuild(structure);
	controller->SetMouseHeld(true);
}

void BuildingButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

BuildingButton * BuildingButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string structure, BuildingHUD *hud, std::string baseTexture)
{
	return Create(element, rect, structure, hud, baseTexture, "", "");
}

BuildingButton * BuildingButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string structure, BuildingHUD *hud,
	std::string baseTexture, std::string mouseOverTexture, std::string mouseDownTexture)
{
	BuildingButton * button = new BuildingButton();
	button->rect = rect;
	button->structure = structure;
	button->hud = hud;
	button->baseTexture = baseTexture;
	button->mouseEnterTexture = mouseOverTexture;
	button->mouseDownTexture = mouseDownTexture;

	element->AttachWidget(button);

	return button;

}
