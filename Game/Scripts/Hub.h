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
	/** Add a Structure to the network slots (Grid Tile position)*/
	void AddStructureToNetwork(enum StructureType type, class Structure* structure, int x, int y);
	/** Remove a Structure from the network slots (Grid Tile Position)*/
	void RemoveStructureFromNetwork(StructureType type, Structure * structure, int x, int y);
	/** Add a Structure to list of structures*/
	void AddStructureToList(enum StructureType type, class Structure* structure, int x, int y);
	/** Remove the structure from the list of structures*/
	void RemoveStructureFromList(StructureType type, Structure * structure, int x, int y, string structureName);
	// Removes a building from the network
	void RemoveBuildingFromLists(Structure * s, float x, float y, float width, string structureName);
	/** Get a structure*/
	class Structure* GetStructure(int x, int y);
	/** Find the nearest structure for a position */
	class Structure* FindNearest(enum StructureType type, int x, int y);
	/** Find the nearest structure that has enough inventory space for this resource*/
	class Structure* FindNearestToDeposit(enum StructureType type, int x, int y, ResourceName resource);
	/** Find the nearest structure that has this resource*/
	class Structure* FindNearestWithResource(enum StructureType type, int x, int y, ResourceName resource);

	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update(double dt);

	v2::Inventory * GetInventory() const;

	v1::TaskSystem::TaskManager * GetTaskManager() const;

	/** Calculate the entire upkeep of the network*/
	int CalculateUpkeep();
	/** Get Resources in network */
	vector<ResourceSlot> GetNetworkResources();
	/** Get count of a structure type in the network*/
	int GetNumberOf(StructureType type);
	/** Get the number of resources in the network. Includes a map with all resources, where count 0 = not in network*/
	std::map<ResourceName, int> GetResourceInNetwork();
	/** Create a Drone */
	void CreateDrone();
	/** Get Total Gold in the hub*/
	int GetGold();
	/** Get the current cost of gold */
	int GetDroneCost();
	/** Get the calculated upkeep of the drones */
	int GetDroneUpkeep();
	/** Get the calculated upkeep of the buildings */
	int GetBuildingUpkeep();

	/** Get the Debt amount that the player is in */
	int GetDebt();
	/** Set the debt of the player */
	void SetDebt(int amount);
	/** Adjust the debt by an amount */
	void AdjustDebt(int amount);

	/** Get a list of all the buildings in the network*/
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