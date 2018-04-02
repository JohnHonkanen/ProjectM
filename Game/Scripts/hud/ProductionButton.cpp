#include "ProductionButton.h"
#include "hud\widgets\HUDContainer.h"
#include "..\Production.h"
#include "ProductionSetterButton.h"
#include "../GameManager.h"
#include "core\InputManager.h"
#include "core\GameEngine.h"

string GetIcon(ResourceName resource) {
	return GameManager::gameManager->resourceManager.Find(resource)->GetResourceIcon();
}

void ProductionButton::OnPointerEnter(EventData data)
{
}

void ProductionButton::OnPointerExit(EventData data)
{
}

void ProductionButton::OnPointerMouseDown(EventData data)
{
	if (production->GetType() == DOME) {
		if (data.mouseButton0 == 1) {
			containerDome->SetActive(true);
			ConfigureResources();
			for (ProductionSetterButton* button : resourceListDome) {
				if (containerDome->IsActive() == false) {
					return;
				}
				else {
					button->SetActive(true);
				}
			}
		}
		if (data.mouseButton1 == 1) {
			containerDome->SetActive(false);
			for (ProductionSetterButton* button : resourceListDome) {
				button->SetActive(false);
			}
		}
	}
	else if (production->GetType() == FACTORY) {
		if (data.mouseButton0 == 1) {
			containerFactory->SetActive(true);
			ConfigureResources();
			for (ProductionSetterButton* button : resourceListFactory) {
				if (containerFactory->IsActive() == false) {
					return;
				}
				else {
					button->SetActive(true);
				}
			}
		}
		if (data.mouseButton1 == 1) {
			containerFactory->SetActive(false);
			for (ProductionSetterButton* button : resourceListFactory) {
				button->SetActive(false);
			}
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

	containerDome = EHUD::WHUDContainer::Create(root, { 310,0,210,280 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	containerDome->SetActive(false);
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 330,20,50,50 }, "Game/Assets/Textures/cow-16.png", nullptr, ResourceName::SpaceCow));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 390,20,50,50 }, "Game/Assets/Textures/livechicken-16.png", nullptr, ResourceName::Chicken));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 450,20,50,50 }, "Game/Assets/Textures/egg-16.png", nullptr, ResourceName::Chicken_Egg));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 330,80,50,50 }, "Game/Assets/Textures/sheep-16.png", nullptr, ResourceName::Sheep));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 390,80,50,50 }, "Game/Assets/Textures/kittain-16.png", nullptr, ResourceName::Kittain));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 450,80,50,50 }, "Game/Assets/Textures/grape-16.png", nullptr, ResourceName::Grape));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 330,140,50,50 }, "Game/Assets/Textures/mandrake-16.png", nullptr, ResourceName::Mandrake));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 390,140,50,50 }, "Game/Assets/Textures/unilateralis-16.png", nullptr, ResourceName::Unilateralis));
	resourceListDome.push_back(ProductionSetterButton::Create(root, { 450,140,50,50 }, "Game/Assets/Textures/steel_cotton-16.png", nullptr, ResourceName::Steel_Cotton));


	for (ProductionSetterButton* button : resourceListDome) {
		button->SetActive(false);
	}

	containerFactory = EHUD::WHUDContainer::Create(root, { 310,0,210,210 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	containerFactory->SetActive(false);
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 330,20,50,50 }, "Game/Assets/Textures/steak-16.png", nullptr, ResourceName::SpaceCow_Beef));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 390,20,50,50 }, "Game/Assets/Textures/milk-16.png", nullptr, ResourceName::SpaceCow_Milk));//Idealy made in a dome but in factory for example of recipy complexity
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 450,20,50,50 }, "Game/Assets/Textures/egg-16.png", nullptr, ResourceName::SpaceCow_Cheese));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 330,80,50,50 }, "Game/Assets/Textures/chicken-16.png", nullptr, ResourceName::Chicken_Meat));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 390,80,50,50 }, "Game/Assets/Textures/kittain-16.png", nullptr, ResourceName::Sheep_Meat));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 450,80,50,50 }, "Game/Assets/Textures/unilateralis-16.png", nullptr, ResourceName::Sheep_Wool));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 330,140,50,50 }, "Game/Assets/Textures/wine-16.png", nullptr, ResourceName::Wine));
	resourceListFactory.push_back(ProductionSetterButton::Create(root, { 390,140,50,50 }, "Game/Assets/Textures/component-16.png", nullptr, ResourceName::Electronic_Component));


	for (ProductionSetterButton* button : resourceListFactory) {
		button->SetActive(false);
	}

}

void ProductionButton::Input()
{
}

void ProductionButton::Update()
{
	if (!active) {
		return;
	}
	if (GameEngine::manager.inputManager.GetKey("mouse1")) {
		containerFactory->SetActive(false);
		for (ProductionSetterButton* button : resourceListFactory) {
			button->SetActive(false);
		}
		containerDome->SetActive(false);
		for (ProductionSetterButton* button : resourceListDome) {
			button->SetActive(false);
		}
	}
}

void ProductionButton::SetProduction(Production * production)
{
	if (this->production != production) {
		this->production = production;
		if (production->GetType() == DOME) {
			for (ProductionSetterButton* button : resourceListDome) {
				button->SetProduction(production);
			}
		}
		else if (production->GetType() == FACTORY) {
			for (ProductionSetterButton* button : resourceListFactory) {
				button->SetProduction(production);
			}
		}
	}

}

void ProductionButton::CloseProductionWindows()
{
	if (currentStructure != production->GetType()) {
		containerFactory->SetActive(false);
		for (ProductionSetterButton* button : resourceListFactory) {
			button->SetActive(false);
		}
		containerDome->SetActive(false);
		for (ProductionSetterButton* button : resourceListDome) {
			button->SetActive(false);
		}
		currentStructure = production->GetType();
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
		//for (int i = 0; i <= resourceListDome.size; i++)
		//{
		//	resourceListDome[i]->SetResource(resourceListDome.;
		//	resourceListDome[i]->SetIcon(GetIcon(ResourceName::SpaceCow));//test if cow appears
		//}
		resourceListDome[0]->SetResource(ResourceName::SpaceCow);
		resourceListDome[0]->SetIcon(GetIcon(ResourceName::SpaceCow));//test if cow appears
		resourceListDome[1]->SetResource(ResourceName::Chicken);
		resourceListDome[1]->SetIcon(GetIcon(ResourceName::Chicken));
		resourceListDome[2]->SetResource(ResourceName::Chicken_Egg);
		resourceListDome[2]->SetIcon(GetIcon(ResourceName::Chicken_Egg));
		resourceListDome[3]->SetResource(ResourceName::Sheep);
		resourceListDome[3]->SetIcon(GetIcon(ResourceName::Sheep));
		resourceListDome[4]->SetResource(ResourceName::Kittain);
		resourceListDome[4]->SetIcon(GetIcon(ResourceName::Kittain));
		resourceListDome[5]->SetResource(ResourceName::Mandrake);
		resourceListDome[5]->SetIcon(GetIcon(ResourceName::Mandrake));
		resourceListDome[6]->SetResource(ResourceName::Grape);
		resourceListDome[6]->SetIcon(GetIcon(ResourceName::Grape));
		resourceListDome[7]->SetResource(ResourceName::Unilateralis);
		resourceListDome[7]->SetIcon(GetIcon(ResourceName::Unilateralis));
		resourceListDome[8]->SetResource(ResourceName::Steel_Cotton);
		resourceListDome[8]->SetIcon(GetIcon(ResourceName::Steel_Cotton));
		break;
	case StructureType::FACTORY:
		resourceListFactory[0]->SetResource(ResourceName::SpaceCow_Beef);
		resourceListFactory[0]->SetIcon(GetIcon(ResourceName::SpaceCow_Beef));
		resourceListFactory[1]->SetResource(ResourceName::SpaceCow_Milk);
		resourceListFactory[1]->SetIcon(GetIcon(ResourceName::SpaceCow_Milk));
		resourceListFactory[2]->SetResource(ResourceName::SpaceCow_Cheese);
		resourceListFactory[2]->SetIcon(GetIcon(ResourceName::SpaceCow_Cheese));
		resourceListFactory[3]->SetResource(ResourceName::Chicken_Meat);
		resourceListFactory[3]->SetIcon(GetIcon(ResourceName::Chicken_Meat));
		resourceListFactory[4]->SetResource(ResourceName::Sheep_Meat);
		resourceListFactory[4]->SetIcon(GetIcon(ResourceName::Sheep_Meat));
		resourceListFactory[5]->SetResource(ResourceName::Sheep_Wool);
		resourceListFactory[5]->SetIcon(GetIcon(ResourceName::Sheep_Wool));
		resourceListFactory[6]->SetResource(ResourceName::Wine);
		resourceListFactory[6]->SetIcon(GetIcon(ResourceName::Wine));
		resourceListFactory[7]->SetResource(ResourceName::Electronic_Component);
		resourceListFactory[7]->SetIcon(GetIcon(ResourceName::Electronic_Component));
		break;
	default:
		break;
	}
}

