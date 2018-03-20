#include "Hub.h"
#include "Structure.h"
#include "task_system\TaskManager.h"
#include "components\MeshRenderer.h"
#include "InventoryWrapper.h"
#include "GameManager.h"
#include <queue>
#include "Drone.h"
struct Slot
{
	StructureType type;
	int x, y;
	class Structure *structure;
};

Hub * Hub::Create(GameObject * gameObject, GameManager * gameManager)
{
	Hub *h = new Hub();
	gameObject->AddComponent(h);

	MeshRenderer::Create(gameObject, "Game/Assets/Models/mobajuice/Hub.DAE", DEFERRED);

	//Create Inventory Wrapper and Get Inventory
	h->inventory = &InventoryWrapper::Create(gameObject, &gameManager->resourceManager)->inventory;
	h->inventory->AddFilter(ResourceName::Gold);
	h->inventory->SetMode(v2::Inventory::WHITELIST);
	gameManager->playerEconManager.SetHUBInventory(h->inventory);

	h->taskManager = v1::TaskSystem::TaskManager::Create(gameObject);

	return h;

}

void Hub::AddStructureToNetwork(StructureType type, Structure * structure, int x, int y)
{
	switch (type)
	{
	case PRODUCTION:
		networkList.push_back({type, x, y, structure});
		break;
	case WAREHOUSE:
		networkList.push_back({ type, x, y, structure });
		warehouseList.push_back({ type, x, y, structure });
		break;
	case FACTORY:
		networkList.push_back({ type, x, y, structure });
		break;
	default:
		break;
	}

	networkSlots[x][y] = structure;
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

void Hub::Copy(GameObject * copyObject)
{
	//TO Be Filled in
}

void Hub::OnLoad()
{
	
		//Setup droneprefab
		Drone::Create(&dronePrefab, this, inventory->GetResourceManager());

		CreateDrone();
	
}

void Hub::Update(double dt)
{
	TallyResource();
}

v2::Inventory * Hub::GetInventory() const
{
	return inventory;
}

v1::TaskSystem::TaskManager * Hub::GetTaskManager() const
{
	return taskManager;
}

vector<ResourceSlot> Hub::GetNetworkResources()
{
	return networkResource;
}

void Hub::CreateDrone()
{
	if (inventory->Contains(ResourceName::Gold) >= 1000)
	{
		inventory->Remove(ResourceName::Gold, 1000);
		GameObject *drone = dronePrefab.Instantiate();
		drone->transform->SetPosition(transform->GetPosition());
	}

}

int Hub::GetGold()
{
	return inventory->Contains(ResourceName::Gold);
}

void Hub::TallyResource()
{
	map<ResourceName, ResourceSlot> tempList;

	for (auto structure : networkList)
	{
		auto inventory = structure.structure->GetInventory();
		auto list = inventory.Contains();

		for (auto i : list)
		{
			if (tempList.find(i.resource) == tempList.end())
			{
				tempList[i.resource] = ResourceSlot();
				tempList[i.resource].resource = i.resource;
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
