#pragma once

#include <string>
#include <iostream>


using namespace std;

class Resources
{
public:
	Resources();
	Resources(int itemID, string itemName, string sku, int basePrice, int itemStock);
	~Resources();
	
	string GetName();
	string GetSKU(); // SKU = Stock-keeping Unit

	int GetItemID();
	int GetItemAmount();
	int GetBasePrice();

	void IncreaseItemAmount(int itemStock);
	void ReduceItemAmount(int itemStock);
	void SetItemAmount(int itemStock);
	void IncreaseItemPrice(float modifier);
	void DecreaseItemPrice(float modifier);
	void SetItemPrice(int basePrice);
	
	void SetItemName(string itemName);
	void SetItemSKU(string itemSKU);
	void SetItemID(int itemID);

	void update(); //Increase/Decrease price if item purchase/sold is detected (based on key input).

private:
	int itemID, itemValue, itemQuality, itemStock;
	int basePrice; // Standard price
	float mood; // The modifier
	string itemName, sku;

	bool purchase = false;
	bool sold = false;

};

