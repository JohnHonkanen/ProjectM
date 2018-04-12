#pragma once

#include <string>
#include <iostream>


using namespace std;

// Add new resource in between SpaceCow and Electronic_Component
enum class ResourceName : unsigned int {
	Null_Resource,
	Gold,
	SpaceCow, // Dome Only
	SpaceCow_Beef,
	SpaceCow_Milk,
	SpaceCow_Cheese, // Recipe: Use SpaceCow_Milk to produce
	Sheep, // Dome Only
	Sheep_Wool, // Factory Only
	Sheep_Meat, // Factory Only
	Chicken, // Dome only
	Chicken_Egg,
	Chicken_Meat, // Factory Only
	Kittain, // Dome only (Pets)
	Doggo, // Dome only (Pets)
	Steel_Cotton, // Building material
	Mandrake,
	Grape,
	Wine,
	Unilateralis,
	Electronic_Component // Recipe: Use Unilateralis to produce in factory
};

class Resources
{
public:
	Resources();
	Resources(ResourceName resName, string itemName, string sku, int basePrice, int itemStock, string resourceIcon, int stackLimit, int demand, int productionRate, int productionTimer,
		int productionCost);
	Resources(const Resources &copyRes);
	~Resources();
	
	string GetName(); // Get item name
	string GetSKU(); // SKU = Stock-keeping Unit

	int GetItemID() const; // Get the item ID
	int GetItemAmount(); // Get amount of item in stock

	int GetBasePrice(); // Get current base price of items
	void SetBasePrice(int basePrice); // Set current base price of items
	void IncreaseItemBasePrice(int amount); // Increase current base price of item
	void DecreaseItemBasePrice(int amount); // Decrease current base price of item

	void IncreaseItemAmount(int itemStock); // Increase the amount of item in stock
	void ReduceItemAmount(int itemStock); // Decrease the amount of item in stock
	void SetItemAmount(int itemStock); // Set the amount of item in stock

	void IncreaseItemPrice(float modifier); // Increase the base price of the item
	void DecreaseItemPrice(float modifier); // Decrease the base price of item
	void SetItemPrice(int basePrice); // Set the base price of item
	
	void SetItemName(string itemName); // Set the item name
	void SetItemSKU(string itemSKU); // Set the item SKU
	void SetItemID(int itemID); // Set the item ID

	void SetStackLimit(int stackLimit); // Set the stack limit
	int GetStackLimit() const; // Get Stack limit

	void SetDemand(int demand); // Set resource demand
	int GetDemand(); // Get resource demand
	void IncreaseDemand(int demand); // Increase resource demand
	void DecreaseDemand(int demand); // Decrease resource demand

	int GetProductionRate(); // Get resource production rate. (How many resource is made per sec)
	void IncreaseProductionRate(int amountToIncreaseBy); // Increase resource production rate (Example: Due to building upgrades)
	void DecreaseProductionRate(int amountToDecreaseBy); // Decrease resource production rate (Example: Due to power shortage)

	int GetProductionTimer(); // Get the resource production speed
	void IncreaseProductionTimer(int amountToIncreaseBy); // Increase the resource production speed
	void DecreaseProductionTimer(int amountToDecreaseBy); // Decrease the resource production speed

	int GetProductionCost(); // Get the resource production cost for resources made in domes.
	void AdjustProductionCost(int amount); // Adjust resource production cost made in domes.

	void update(); //Increase/Decrease price if item purchase/sold is detected (based on key input).

	string GetResourceIcon(); // Get Resource icon
	void SetResourceIcon(string resourceIcon); // Set a resource icon

	ResourceName GetResouceID(); // Returns the ResourceName of the resource
private:
	int itemID, itemValue, itemQuality, stackLimit, demand, productionTimer;
	int productionCost = 0;
	int itemStock = 0;
	int basePrice; // Standard price
	float baseModifier = 5.0;
	int productionRate = 0.0;
	string itemName, sku, resourceIcon;

	ResourceName resourceName;
	bool purchase = false;
	bool sold = false;
	bool keyReleased = true;

};

using Resource = Resources;

