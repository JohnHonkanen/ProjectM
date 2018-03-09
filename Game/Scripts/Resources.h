#pragma once

#include <string>
#include <iostream>


using namespace std;


enum class ResourceName {
	Gold,
	SpaceCow_Beef,
	SpaceCow_Milk,
	SpaceCow_Cheese, // Recipe: Use SpaceCow_Milk to produce
	Sheep_Wool, // Factory Only
	Sheep_Meat, // Factory Only
	Chicken_Egg,
	Chicken_Meat, // Factory Only
	Kittain, // Dome only (Pets)
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
	Resources(ResourceName resName, string itemName, string sku, int basePrice, int itemStock, string resourceIcon);
	~Resources();
	
	string GetName(); // Get item name
	string GetSKU(); // SKU = Stock-keeping Unit

	int GetItemID(); // Get the item ID
	int GetItemAmount(); // Get amount of item in stock
	int GetBasePrice(); // Get current base price of items

	void IncreaseItemAmount(int itemStock); // Increase the amount of item in stock
	void ReduceItemAmount(int itemStock); // Decrease the amount of item in stock
	void SetItemAmount(int itemStock); // Set the amount of item in stock
	void IncreaseItemPrice(float modifier); // Increase the base price of the item
	void DecreaseItemPrice(float modifier); // Decrease the base price of item
	void SetItemPrice(int basePrice); // Set the base price of item
	
	void SetItemName(string itemName); // Set the item name
	void SetItemSKU(string itemSKU); // Set the item SKU
	void SetItemID(int itemID); // Set the item ID

	void update(); //Increase/Decrease price if item purchase/sold is detected (based on key input).

	string GetResourceIcon(); // Get Resource icon
	void SetResourceIcon(string resourceIcon); // Set a resource icon
private:
	int itemID, itemValue, itemQuality;
	int itemStock = 0;
	int basePrice; // Standard price
	float mood; // The modifier
	float baseModifier = 5.0;
	string itemName, sku, resourceIcon;

	bool purchase = false;
	bool sold = false;
	bool keyReleased = true;

};

using Resource = Resources;

