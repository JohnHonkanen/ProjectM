#pragma once
#include "components\Behaviour.h"
#include <vector>
#include <map>
#include "InventoryV2.h"
#include "task_system\TaskManager.h"
#include "Resources.h"
#include "Structure.h"
#include "utility\Clock.h"

struct Slot
{
	StructureType type;
	int x, y;
	class Structure *structure;
};

class Hub : public Structure
{
public:
	static Hub *Create(GameObject* gameObject, class GameManager* gameManager);
	void AddStructureToNetwork(enum StructureType type, class Structure* structure, int x, int y);
	void RemoveStructureFromNetwork(StructureType type, Structure * structure, int x, int y);
	void AddStructureToList(enum StructureType type, class Structure* structure, int x, int y);
	void RemoveStructureFromList(StructureType type, Structure * structure, int x, int y, string structureName);
	// Removes a building from the network
	void RemoveBuildingFromLists(Structure * s, float x, float y, float width, string structureName);
	class Structure* GetStructure(int x, int y);
	class Structure* FindNearest(enum StructureType type, int x, int y);
	class Structure* FindNearestToDeposit(enum StructureType type, int x, int y, ResourceName resource);
	class Structure* FindNearestWithResource(enum StructureType type, int x, int y, ResourceName resource);

	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update(double dt);
	v2::Inventory * GetInventory() const;
	v1::TaskSystem::TaskManager * GetTaskManager() const;

	int CalculateUpkeep();
	vector<ResourceSlot> GetNetworkResources();
	int GetNumberOf(StructureType type);
	std::map<ResourceName, int> GetResourceInNetwork();
	void CreateDrone();
	int GetGold();
	int GetDroneCost();
	int GetDroneUpkeep();
	int GetBuildingUpkeep();

	int GetDebt();
	void SetDebt(int amount);
	void AdjustDebt(int amount);

	std::vector<Slot> GetAllBuildingInNetwork(); 
private:
	void TallyResource();
	std::vector<Slot> networkList;
	std::vector<Slot> warehouseList;
	std::map<int, std::map<int, class Structure*>> networkSlots;
	v2::Inventory * inventory;
	v1::TaskSystem::TaskManager * taskManager;

	vector<ResourceSlot> networkResource;
	vector<class Drone*> drones;

	GameObject dronePrefab;
	Drone * dronePrefabComp;

	Engine::Utility::Clock timer;

	int upkeepBuilding;
	int upkeepDrone;
	int debt = 0;
};