#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>


using namespace std;

class Resources
{
public:
	Resources();
	Resources(int itemID, string itemName, string sku, int basePrice);
	~Resources();
	
	string GetName();
	string GetSKU(); // SKU = Stock-keeping Unit

	int GetItemID();
	int GetItemAmount();
	int GetBasePrice();

	void IncreaseItemAmount(int itemStock);
	void ReduceItemAmount(int itemStock);
	void SetItemAmount(int itemStock);

	
private:
	int itemID, itemValue, itemQuality, itemStock;
	int basePrice = 0; // Standard price
	float mood = 0; // The modifier
	string itemName, sku;

};

