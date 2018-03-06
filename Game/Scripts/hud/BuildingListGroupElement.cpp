#include "BuildingListGroupElement.h"
#include "BuildingSelectorButton.h"
BuildingListGroup * BuildingListGroup::Create(HUDElement * element, EHUD::HUDRect rect)
{
	BuildingListGroup * blg = new BuildingListGroup();
	blg->rect = rect;
	blg->parent = element;
	element->AttachWidget(blg);

	return blg;
}

void BuildingListGroup::Start()
{
	BuildingSelectorButton::Create(this, { 0,0, 60,60}, "Game/Assets/Textures/circle.png");
	BuildingSelectorButton::Create(this, { 70,0, 60,60 }, "Game/Assets/Textures/circle.png");
	BuildingSelectorButton::Create(this, { 140,0, 60,60 }, "Game/Assets/Textures/circle.png");
}

void BuildingListGroup::Update()
{
}

void BuildingListGroup::DrawWidget(unsigned int shader)
{
}

void BuildingListGroup::AddButtons(AnimatedButton * button)
{
	buttons.push_back(button);
}
