#pragma once
#include "components\Behaviour.h"
#include <vector>
#include <map>
#include "InventoryV2.h"
#include "task_system\TaskManager.h"
#include "Resources.h"

struct Slot;

class Hub : public Behaviour
{
public:
	static Hub *Create(GameObject* gameObject, class GameManager* gameManager);
	void AddStructureToNetwork(enum StructureType type, class Structure* structure, int x, int y);
	class Structure* GetStructure(int x, int y);
	class Structure* FindNearest(enum StructureType type, int x, int y);
	class Structure* FindNearestToDeposit(enum StructureType type, int x, int y, ResourceName resource);

	void Copy(GameObject *copyObject);
	void OnLoad();
	void Update(double dt);
	v2::Inventory * GetInventory() const;
	v1::TaskSystem::TaskManager * GetTaskManager() const;

	vector<ResourceSlot> GetNetworkResources();

	void CreateDrone();
	int GetGold();
private:
	void TallyResource();
	std::vector<Slot> networkList;
	std::vector<Slot> warehouseList;
	std::map<int, std::map<int, class Structure*>> networkSlots;
	v2::Inventory * inventory;
	v1::TaskSystem::TaskManager * taskManager;

	vector<ResourceSlot> networkResource;

	GameObject dronePrefab;
};