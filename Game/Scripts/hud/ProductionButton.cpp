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

	container = EHUD::WHUDContainer::Create(root, { 310,0,210,210 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	container->SetActive(false);
	resourceList.push_back(ProductionSetterButton::Create(root, { 330,20,50,50 }, "Game/Assets/Textures/milk-16.png", nullptr, ResourceName::SpaceCow_Milk));
	resourceList.push_back(ProductionSetterButton::Create(root, { 390,20,50,50 }, "Game/Assets/Textures/steak-16.png", nullptr, ResourceName::SpaceCow_Beef));
	resourceList.push_back(ProductionSetterButton::Create(root, { 450,20,50,50 }, "Game/Assets/Textures/egg-16.png", nullptr, ResourceName::Chicken_Egg));
	resourceList.push_back(ProductionSetterButton::Create(root, { 330,80,50,50 }, "Game/Assets/Textures/mandrake-16.png", nullptr, ResourceName::Mandrake));
	resourceList.push_back(ProductionSetterButton::Create(root, { 390,80,50,50 }, "Game/Assets/Textures/grape-16.png", nullptr, ResourceName::Grape));
	resourceList.push_back(ProductionSetterButton::Create(root, { 450,80,50,50 }, "Game/Assets/Textures/kittain-16.png", nullptr, ResourceName::Kittain));
	resourceList.push_back(ProductionSetterButton::Create(root, { 330,140,50,50 }, "Game/Assets/Textures/unilateralis-16.png", nullptr, ResourceName::Unilateralis));
	resourceList.push_back(ProductionSetterButton::Create(root, { 390,140,50,50 }, "Game/Assets/Textures/steel_cotton-16.png", nullptr, ResourceName::Steel_Cotton));



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
		//Needs to be replaced with a cow item
		resourceList[1]->SetResource(ResourceName::SpaceCow_Beef);
		resourceList[1]->SetIcon("Game/Assets/Textures/steak-16.png");
		resourceList[2]->SetResource(ResourceName::Chicken_Egg);
		resourceList[2]->SetIcon("Game/Assets/Textures/egg-16.png");
		resourceList[3]->SetResource(ResourceName::Mandrake);
		resourceList[3]->SetIcon("Game/Assets/Textures/mandrake-16.png");
		resourceList[4]->SetResource(ResourceName::Grape);
		resourceList[4]->SetIcon("Game/Assets/Textures/grape-16.png");
		resourceList[5]->SetResource(ResourceName::Kittain);
		resourceList[5]->SetIcon("Game/Assets/Textures/kittain-16.png");
		resourceList[6]->SetResource(ResourceName::Unilateralis);
		resourceList[6]->SetIcon("Game/Assets/Textures/unilateralis-16.png");
		resourceList[7]->SetResource(ResourceName::Steel_Cotton);
		resourceList[7]->SetIcon("Game/Assets/Textures/steel_cotton-16.png");
		//Needs to be replaced with a sheep item
		//resourceList[8]->SetResource(ResourceName::Sheep);
		//resourceList[8]->SetIcon("Game/Assets/Textures/sheep-16.png");
		//Needs to be replaced with a chicken item
		//resourceList[8]->SetResource(ResourceName::Chicken);
		//resourceList[8]->SetIcon("Game/Assets/Textures/chicken-16.png");
		break;
	case StructureType::FACTORY:
		resourceList[0]->SetResource(ResourceName::Chicken_Egg);
		resourceList[0]->SetIcon("Game/Assets/Textures/egg-16.png");
		resourceList[1]->SetResource(ResourceName::Chicken_Meat);
		resourceList[1]->SetIcon("Game/Assets/Textures/chicken-16.png");
		resourceList[2]->SetResource(ResourceName::SpaceCow_Beef);
		resourceList[2]->SetIcon("Game/Assets/Textures/steak-16.png");
		resourceList[3]->SetResource(ResourceName::SpaceCow_Cheese);
		resourceList[3]->SetIcon("Game/Assets/Textures/cheese-16.png");
		resourceList[4]->SetResource(ResourceName::Wine);
		resourceList[4]->SetIcon("Game/Assets/Textures/wine-16.png");
		resourceList[5]->SetResource(ResourceName::Electronic_Component);
		resourceList[5]->SetIcon("Game/Assets/Textures/component-16.png");
		resourceList[6]->SetResource(ResourceName::Sheep_Meat);
		resourceList[6]->SetIcon("Game/Assets/Textures/mutton-16.png");
		resourceList[7]->SetResource(ResourceName::Sheep_Wool);
		resourceList[7]->SetIcon("Game/Assets/Textures/wool-16.png");


		break;
	default:
		break;
	}
}