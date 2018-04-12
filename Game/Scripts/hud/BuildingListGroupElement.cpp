#include "BuildingListGroupElement.h"
#include "BuildingSelectorButton.h"
#include "../BuildingController.h"
BuildingListGroup * BuildingListGroup::Create(HUDElement * element, EHUD::HUDRect rect, BuildingController * buildingController)
{
	BuildingListGroup * blg = new BuildingListGroup();
	blg->rect = rect;
	blg->parent = element;
	blg->buildingController = buildingController;
	element->AttachWidget(blg);

	return blg;
}

void BuildingListGroup::Start()
{

	buttons.push_back(BuildingSelectorButton::Create(parent, { 100,500, 60,60}, "Game/Assets/Textures/dome_icon.png", buildingController, "Dome"));
	buttons.push_back(BuildingSelectorButton::Create(parent, { 170,500, 60,60 }, "Game/Assets/Textures/factory_icon.png", buildingController, "Factory"));
	buttons.push_back(BuildingSelectorButton::Create(parent, { 240,500, 60,60 }, "Game/Assets/Textures/warehouse_icon.png", buildingController, "Warehouse"));
	buttons.push_back(BuildingSelectorButton::Create(parent, { 310,500, 60,60 }, "Game/Assets/Textures/dock_icon.png", buildingController, "Dock"));
}

void BuildingListGroup::Update()
{
	ToggleButtons();
}

void BuildingListGroup::DrawWidget(unsigned int shader)
{
}

void BuildingListGroup::AddButtons(AnimatedButton * button)
{
	buttons.push_back(button);
}

void BuildingListGroup::ToggleButtons()
{
	for (HUDElement *e : buttons)
	{
		e->SetActive(IsActive());
	}
}
