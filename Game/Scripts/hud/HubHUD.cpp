#include "HubHUD.h"
#include "core\GameObject.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "hud\HUDElement.h"
#include "hud\HUDCanvas.h"
#include "..\Hub.h"
#include "FunctionPtrButton.h"
#include "../GameManager.h"

class HubDroneBinder : public FunctionPtrBinder
{
public:
	HubDroneBinder(Hub *hub) : hub(hub) {};
	void Call() {
		hub->CreateDrone();
	}
private:
	Hub * hub;
};
HubHUD * HubHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, Hub * hub, ResourceManager * resourceManager)
{
	HubHUD * hh = new HubHUD();
	hh->root = root;
	hh->hub = hub;
	hh->resourceManager = resourceManager;

	gameObject->AddComponent(hh);

	return hh;
}

void HubHUD::Copy(GameObject * copy)
{
}

void HubHUD::OnLoad()
{
	wrapper = EHUD::WHUDContainer::Create(root, { 300, 100, 680, 500 }, "Game/Assets/Textures/black.jpg", true);
	inventoryBox = EHUD::WHUDContainer::Create(wrapper, { 10, 50, 300, 440 }, "Game/Assets/Textures/hub_containers.png", true);
	EHUD::TextWidget::Create(wrapper, { 10, 32, 0, 0 }, "Hub Panel", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 32, 1, vec3(1, 1, 1));

	auto droneContainer = EHUD::WHUDContainer::Create(wrapper, { 320, 50, 350, 120 }, "Game/Assets/Textures/hub_containers.png", true);
	EHUD::TextWidget::Create(droneContainer, { 10, 32, 0, 0 }, "Drones", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 32, 1, vec3(0, 0, 0));
	statBox = EHUD::WHUDContainer::Create(wrapper, { 320, 180, 350, 310 }, "Game/Assets/Textures/hub_containers.png", true);
	syncButton = FunctionPtrButton::Create(root, { 860, 160, 100, 100 }, "Game/Assets/Textures/building_selected.jpg", new HubDroneBinder(hub));
	droneCost = EHUD::TextWidget::Create(syncButton, { 5, 90, 0, 0 }, "1000", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 22, 1, vec3(1, 1, 1));
	EHUD::WHUDContainer::Create(syncButton, { 70, 70, 20, 20 }, "Game/Assets/Textures/gold_bars.png", true);
	EHUD::WHUDContainer::Create(syncButton, { 15, 10, 60, 60 }, "Game/Assets/Textures/building_list_icon.png", true);
	EHUD::WHUDContainer::Create(wrapper, { 540, 10, 30, 30 }, "Game/Assets/Textures/gold_bars.png", true);
	goldCounter = EHUD::TextWidget::Create(wrapper, { 580, 32, 0, 0 }, to_string(hub->GetGold()), "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 24, 1, vec3(1, 1, 1));
	buildingUpkeep = EHUD::TextWidget::Create(statBox, { 20, 30, 0, 0 }, "Building Upkeep: " + to_string(0), "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 24, 1, vec3(0));
	droneUpkeep = EHUD::TextWidget::Create(statBox, { 20, 60, 0, 0 }, "Drone Upkeep: " + to_string(0), "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 24, 1, vec3(0));
	playerDebtInterest = EHUD::TextWidget::Create(statBox, {20, 90, 0, 0}, "Debt Interest: " + to_string(0), "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 24, 1, vec3(0));
	totalUpkeep = EHUD::TextWidget::Create(statBox, { 20, 280, 0, 0 }, "Total Upkeep: " + to_string(0), "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 24, 1, vec3(0));

	WidgetToggleButton::Create(root, { 1170, 610, 100, 100 }, "Game/Assets/Textures/hub.png", wrapper);
	
	for (int i = 0; i < 24; i++)
	{
		CreateSlot();
	}
}

void HubHUD::Update()
{
	syncButton->SetActive(wrapper->IsActive());
	auto totalList = hub->GetNetworkResources();
	int size = totalList.size();

	if (inventoryDisplay.capacity() < size)
	{
		inventoryDisplay.reserve(size);
	}
	int i = 0;
	for (auto &iDisplay : inventoryDisplay)
	{
		iDisplay->SetIcon("");
		iDisplay->SetQuantity(0);
	}

	for (auto item : totalList)
	{
		Resource resource = *resourceManager->Find(item.resource);
		inventoryDisplay[i]->SetIcon(resource.GetResourceIcon());
		inventoryDisplay[i]->SetQuantity(item.quantity);

		i++;
	}

	goldCounter->text = to_string(hub->GetGold());
	droneCost->text = to_string(hub->GetDroneCost());
	buildingUpkeep->text = "Buildings Upkeep: " + to_string(hub->GetBuildingUpkeep());
	droneUpkeep->text = "Drones Upkeep: " + to_string(hub->GetDroneUpkeep());
	playerDebtInterest->text = "Debt Interest: " + to_string(GameManager::gameManager->playerEconManager.GetInterest());

	totalUpkeep->text = "Total Upkeep: " + to_string(hub->GetBuildingUpkeep() + hub->GetDroneUpkeep());
}

void HubHUD::CreateSlot()
{
	int x = 0, y = 0;
	float sizeX = 60, sizeY = 50;
	float incrementX = sizeX + 10, incrementY = sizeY + 10;

	if (inventoryDisplay.size() == 0) {
		int x = 0; y = 0;
	}
	else {
		y = inventoryDisplay.size() / 4;
		x = inventoryDisplay.size() % 4;
	}

	inventoryDisplay.push_back(
		HUDInventorySlot::Create(inventoryBox, { 10 + x * incrementX, 10 + y * incrementY, sizeX, sizeY }, "Game/Assets/Textures/black.jpg")
	);
}
