#include "Hub.h"
#include "Structure.h"
#include "task_system\TaskManager.h"
#include "components\MeshRenderer.h"
#include "InventoryWrapper.h"
#include "GameManager.h"
#include <queue>
#include "Drone.h"
#include "LightCycle.h"



Hub * Hub::Create(GameObject * gameObject, GameManager * gameManager)
{
	Hub *h = new Hub();
	gameObject->AddComponent(h);

	MeshRenderer::Create(gameObject, "Game/Assets/Models/mobajuice/Hub.DAE", DEFERRED);

	//Create Inventory Wrapper and Get Inventory
	h->inventory = &InventoryWrapper::Create(gameObject, &gameManager->resourceManager)->inventory;
	h->inventory->AddFilter(ResourceName::Gold);
	h->inventory->SetMode(v2::Inventory::WHITELIST);
	h->tileWidth = 10;
	gameManager->playerEconManager.SetHUBInventory(h->inventory);

	LightCycle::Create(gameObject);

	h->taskManager = v1::TaskSystem::TaskManager::Create(gameObject);

	return h;

}

void Hub::AddStructureToNetwork(StructureType type, Structure * structure, int x, int y)
{
	networkSlots[x][y] = structure;
}

void Hub::RemoveStructureFromNetwork(StructureType type, Structure * structure, int x, int y)
{
	networkSlots[x][y] = nullptr;
}

void Hub::AddStructureToList(StructureType type, Structure * structure, int x, int y)
{
	switch (type)
	{
	case PRODUCTION:
		networkList.push_back({ type, x, y, structure });
		break;
	case DOME:
		networkList.push_back({ type, x, y, structure });
		break;
	case WAREHOUSE:
		networkList.push_back({ type, x, y, structure });
		warehouseList.push_back({ type, x, y, structure });
		break;
	case FACTORY:
		networkList.push_back({ type, x, y, structure });
		break;
	default:
		networkList.push_back({ type, x, y, structure });
		break;
	}
}

void Hub::RemoveStructureFromList(StructureType type, Structure * structure, int x, int y, string structureName)
{
	switch (type)
	{
	case PRODUCTION:
		for (int i = 0; i < networkList.size(); i++)
		{
			if (networkList[i].structure->gameObject->name == structureName)
			{
				networkList.erase(networkList.begin() + i);
				break;
			}
		}
		break;
	case DOME:
		for (int i = 0; i < networkList.size(); i++)
		{
			if (networkList[i].structure->gameObject->name == structureName)
			{
				networkList.erase(networkList.begin() + i);
				break;
			}
		}
		break;
	case WAREHOUSE:
		for (int i = 0; i < networkList.size(); i++)
		{
			if (networkList[i].structure->gameObject->name == structureName)
			{
				networkList.erase(networkList.begin() + i);
				break;
			}
		}
		for (int i = 0; i < warehouseList.size(); i++)
		{
			if (warehouseList[i].structure->gameObject->name == structureName)
			{
				warehouseList.erase(warehouseList.begin() + i);
				break;
			}
		}
		break;
	case FACTORY:
		for (int i = 0; i < networkList.size(); i++)
		{
			if (networkList[i].structure->gameObject->name == structureName)
			{
				networkList.erase(networkList.begin() + i);
				break;
			}
		}
		break;
	default:
		for (int i = 0; i < networkList.size(); i++)
		{
			if (networkList[i].structure->gameObject->name == structureName)
			{
				networkList.erase(networkList.begin() + i);
				break;
			}
		}
		break;
	}
}

void Hub::RemoveBuildingFromLists(Structure * s, float x, float y, float width, string structureName)
{
	// Remove structure from networkList, warehouseList and networkSlots
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + width; j++)
		{
			RemoveStructureFromNetwork(s->GetType(), s, i, j);
		}
	}
	RemoveStructureFromList(s->GetType(), s, x, y, s->gameObject->name);
}

Structure * Hub::GetStructure(int x, int y)
{
	if (networkSlots.find(x) != networkSlots.end())
	{
		//Found
		std::map<int, Structure*> netSlotsY = networkSlots[x];
		if (netSlotsY.find(y) != netSlotsY.end())
		{
			return netSlotsY[y];
		}
	}

	return nullptr;
}

Structure * Hub::FindNearest(StructureType type, int x, int y)
{
	int distance = 1000000000;
	Structure * s = nullptr;

	for (int i = 0; i < networkList.size(); i++)
	{
		//Not the type we are looking for
		if (networkList[i].type != type)
		{
			continue;
		}

		int dx, dy;
		dx = (networkList[i].x - x);
		dy = abs(networkList[i].y - y);
		int dist = (dx*dx) + (dy*dy);
		if (dist < distance)
		{
			distance = dist;
			s = networkList[i].structure;
		}
		
	}

	return s;
}
struct PQueue
{
	int dist;
	int i;
};

struct PQComparator
{
	bool operator()(const PQueue &t1, const PQueue &t2) const
	{
		return t1.dist > t2.dist;
	}
};
Structure * Hub::FindNearestToDeposit(StructureType type, int x, int y, ResourceName resource)
{
	int distance = 1000000000;
	Structure * s = nullptr;

	std::priority_queue<PQueue, vector<PQueue>, PQComparator> queue;
	for (int i = 0; i < networkList.size(); i++)
	{
		//Not the type we are looking for
		if (networkList[i].type != type)
		{
			continue;
		}

		int dx, dy;
		dx = (networkList[i].x - x);
		dy = abs(networkList[i].y - y);
		int dist = (dx*dx) + (dy*dy);

		queue.push({ dist, i });

	}

	bool find = false;

	if (queue.empty())
	{
		return nullptr;
	}
	while (!find)
	{
		int i = queue.top().i;
		s = networkList[i].structure;
		if (s->GetInventory().CheckStorageFull(resource) != 0)
		{
			return s;
		}

		queue.pop();

		if (queue.empty())
		{
			return nullptr;
		}
	}

	return nullptr;
}

Structure * Hub::FindNearestWithResource(StructureType type, int x, int y, ResourceName resource)
{
	int distance = 1000000000;
	Structure * s = nullptr;

	std::priority_queue<PQueue, vector<PQueue>, PQComparator> queue;
	for (int i = 0; i < networkList.size(); i++)
	{
		//Not the type we are looking for
		if (networkList[i].type != type)
		{
			continue;
		}

		int dx, dy;
		dx = (networkList[i].x - x);
		dy = abs(networkList[i].y - y);
		int dist = (dx*dx) + (dy*dy);

		queue.push({ dist, i });
	}

	bool find = false;

	if (queue.empty())
	{
		return nullptr;
	}
	while (!find)
	{
		int i = queue.top().i;
		s = networkList[i].structure;
		if (s->GetInventory().Contains(resource))
		{
			return s;
		}

		queue.pop();

		if (queue.empty())
		{
			return nullptr;
		}
	}

	return nullptr;
}

void Hub::Copy(GameObject * copyObject)
{
	//TO Be Filled in
}

void Hub::OnLoad()
{	
	//Setup droneprefab
	dronePrefabComp = Drone::Create(&dronePrefab, this, inventory->GetResourceManager());

	timer.StartClock();
	timer.SetDelay(3000);
	
}

void Hub::Start()
{
	inventory->AddItem(ResourceName::Gold, 3000);
	gameObject->GetComponent<LightCycle>()->ActivateLight();
}

void Hub::Update(double dt)
{
	TallyResource();

	timer.UpdateClock();

	if (timer.Alarm())
	{
		int goldAmount = inventory->Contains(ResourceName::Gold);
		int upkeep = CalculateUpkeep();
		int difference = 0;

		if (upkeep > goldAmount) {
			difference = upkeep - goldAmount;
			AdjustDebt(difference);
		}

		if (goldAmount > 0) {
			inventory->Remove(ResourceName::Gold, upkeep);
			SetDebt(0);
		}
		
		timer.ResetClock();
	}
}

v2::Inventory * Hub::GetInventory() const
{
	return inventory;
}

v1::TaskSystem::TaskManager * Hub::GetTaskManager() const
{
	return taskManager;
}

int Hub::CalculateUpkeep()
{
	int droneUpkeep = 0;

	for (auto i : drones)
	{
		droneUpkeep += i->GetUpkeep();
	}

	droneUpkeep += drones.size() * 2;
	int buildingUpkeep = 0;

	for (auto i : networkList)
	{
		buildingUpkeep += i.structure->GetUpkeep();
	}

	upkeepBuilding = buildingUpkeep;
	upkeepDrone = droneUpkeep;
	return droneUpkeep + buildingUpkeep;
}

vector<ResourceSlot> Hub::GetNetworkResources()
{
	return networkResource;
}

int Hub::GetNumberOf(StructureType type)
{
	int count = 0;

	for (auto s : networkList)
	{
		if (s.type == type)
		{
			count++;
		}
	}

	return count;
}

std::map<ResourceName, int> Hub::GetResourceInNetwork()
{
	std::map<ResourceName, int> resources;

	for (unsigned int i = static_cast<unsigned int>(ResourceName::Null_Resource); i != static_cast<unsigned int>(ResourceName::Electronic_Component); i++)
	{
		resources[static_cast<ResourceName>(i)] = 0;
	}

	for (auto structure : warehouseList)
	{
		auto inventory = structure.structure->GetInventory();
		auto list = inventory.Contains();

		for (auto i : list)
		{
			resources[i.resource] += i.quantity;
		}
	}

	return resources;
}

void Hub::CreateDrone()
{
	if (inventory->Contains(ResourceName::Gold) >= dronePrefabComp->GetCost())
	{
		inventory->Remove(ResourceName::Gold, dronePrefabComp->GetCost());
		GameObject *drone = dronePrefab.Instantiate();
		drone->transform->SetPosition(transform->GetPosition());
		drone->transform->Scale(vec3(15));
		Drone *component = drone->GetComponent<Drone>();
		component->SetUpkeep(dronePrefabComp->GetUpkeep());
		drones.push_back(component);

		dronePrefabComp->IncreaseCost(dronePrefabComp->GetCost() * drones.size() * 0.05);
		dronePrefabComp->IncreaseUpkeep(1);
	}
}

int Hub::GetGold()
{
	return inventory->Contains(ResourceName::Gold) - GetDebt();
}

int Hub::GetDroneCost()
{
	return dronePrefabComp->GetCost();
}

int Hub::GetDroneUpkeep()
{
	return upkeepDrone;
}

int Hub::GetBuildingUpkeep()
{
	return upkeepBuilding;
}

int Hub::GetDebt()
{
	return this->debt;
}

void Hub::SetDebt(int amount)
{
	this->debt = amount;
}

void Hub::AdjustDebt(int amount)
{
	this->debt += amount;
}

std::vector<Slot> Hub::GetAllBuildingInNetwork()
{
	return networkList;
}

void Hub::TallyResource()
{
	map<ResourceName, ResourceSlot> tempList;

	for (auto structure : warehouseList)
	{
		auto inventory = structure.structure->GetInventory();
		auto list = inventory.Contains();

		for (auto i : list)
		{
			if (tempList.find(i.resource) == tempList.end())
			{
				tempList[i.resource] = ResourceSlot();
				tempList[i.resource].resource = i.resource;
				tempList[i.resource].quantity = 0;;

			}

			tempList[i.resource].quantity += i.quantity;
		}
	}

	networkResource.clear();
	for (auto item : tempList)
	{
		networkResource.push_back(item.second);
	}
}
