#pragma once
#include "components\Behaviour.h"
#include <vector>
#include <map>
#include "InventoryV2.h"
#include "task_system\TaskManager.h"

struct Slot;

class Hub : public Behaviour
{
public:
	static Hub *Create(GameObject* gameObject, class GameManager* gameManager);
	void AddStructureToNetwork(enum StructureType type, class Structure* structure, int x, int y);
	class Structure* GetStructure(int x, int y);
	class Structure* FindNearest(enum StructureType type, int x, int y);

	void Copy(GameObject *copyObject);

	v2::Inventory * GetInventory() const;
	v1::TaskSystem::TaskManager * GetTaskManager() const;
private:
	std::vector<Slot> networkList;
	std::vector<Slot> warehouseList;
	std::map<int, std::map<int, class Structure*>> networkSlots;
	v2::Inventory * inventory;
	v1::TaskSystem::TaskManager * taskManager;
};