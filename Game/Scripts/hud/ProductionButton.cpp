#include "ProductionButton.h"
#include "hud\widgets\HUDContainer.h"
#include "..\Production.h"
#include "ProductionSetterButton.h"


void ProductionButton::OnPointerEnter(EventData data)
{
}

void ProductionButton::OnPointerExit(EventData data)
{
}

void ProductionButton::OnPointerMouseDown(EventData data)
{
	if (data.mouseButton0 == 1) {
		container->SetActive(true);
		ConfigureResources();
		for (ProductionSetterButton* button : resourceList) {
			button->SetActive(true);
		}
	}
	if (data.mouseButton1 == 1) {
		container->SetActive(false);
		for (ProductionSetterButton* button : resourceList) {
			button->SetActive(false);
		}
	}
}

void ProductionButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

void ProductionButton::Start()
{

	StartChildWidgets();
	activeTexture = baseTexture;

	EventRegistration();
	RegisterToEvents();

	container = EHUD::WHUDContainer::Create(root, { 310,0,250,200 }, "Game/Assets/Textures/cBlack.jpg", true);
	container->SetActive(false);
	resourceList.push_back(ProductionSetterButton::Create(root, { 320,10,50,50 }, "Game/Assets/Textures/milk-16.png", nullptr, ResourceName::SpaceCow_Milk));
	resourceList.push_back(ProductionSetterButton::Create(root, { 380,10,50,50 }, "Game/Assets/Textures/steak-16.png", nullptr, ResourceName::SpaceCow_Beef));
	//resourceList.push_back(ProductionSetterButton::Create(root, { 440,10,50,50 }, "Game/Assets/Textures/egg-16.png", nullptr,3));
	//resourceList.push_back(ProductionSetterButton::Create(root, { 500,10,50,50 }, "Game/Assets/Textures/chicken-16.png", nullptr, 4));
	//resourceList.push_back(ProductionSetterButton::Create(root, { 320,70,50,50 }, "Game/Assets/Textures/water-16.png", nullptr, 5));
	for (ProductionSetterButton* button : resourceList) {
		button->SetActive(false);
	}
}

void ProductionButton::Input()
{
}

void ProductionButton::Update()
{

}

void ProductionButton::SetProduction(Production * production)
{
	this->production = production;
	for (ProductionSetterButton* button : resourceList) {
		button->SetProduction(production);
	}
}

ProductionButton * ProductionButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, Production *production)
{
	ProductionButton * button = new ProductionButton();
	button->rect = rect;
	button->baseTexture = baseTexture;
	//button->mouseEnterTexture = mouseOverTexture;
	//button->mouseDownTexture = mouseDownTexture;
	button->root = element;
	button->production = production;
	element->AttachWidget(button);

	return button;
}

void ProductionButton::ConfigureResources()
{
	switch (production->GetType())
	{
	case StructureType::DOME:
		resourceList[0]->SetResource(ResourceName::SpaceCow_Milk);
		resourceList[0]->SetIcon("Game/Assets/Textures/milk-16.png");
		resourceList[1]->SetResource(ResourceName::SpaceCow_Beef);
		resourceList[1]->SetIcon("Game/Assets/Textures/steak-16.png");

		break;
	case StructureType::FACTORY:
		resourceList[0]->SetResource(ResourceName::Chicken_Egg);
		resourceList[0]->SetIcon("Game/Assets/Textures/egg-16.png");
		resourceList[1]->SetResource(ResourceName::Chicken_Meat);
		resourceList[1]->SetIcon("Game/Assets/Textures/chicken-16.png");

		break;
	default:
		break;
	}
}
