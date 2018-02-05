#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
//#include <sstream>

using namespace std;

class Resources
{
public:
	Resources();
	~Resources();
	
	void CreateItem(int itemID, string itemName, int itemValue, int itemQuality);

	int GetItemID() const;
	string GetItemName() const;

	int SetItemValue(int itemID, int itemValue, float mood);
	int GetItemValue(int itemID, int itemValue, float mood);

	int SetItemQuality(int itemID, int itemQuality);
	int GetItemQuality(int itemID, int itemQuality); 

	//Resources *resource;
	vector<int> ResourceList;
	//map<int, >
	
private:
	int itemID, itemValue, itemQuality;
	int basePrice = 0; // Standard price
	float mood = 0; // The modifier
	string itemName, sku;

};

