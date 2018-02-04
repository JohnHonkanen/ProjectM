#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Resources
{
public:
	Resources();
	~Resources();
	
	void CreateItem(int itemID, string itemName, int itemValue, int itemQuality);

	int GetItemID(int itemID);
	string GetItemName(string itemName);

	int SetItemValue(int itemID, int itemValue, float mood);
	int GetItemValue(int itemID, int itemValue, float mood);

	int SetItemQuality(int itemID, int itemQuality);
	int GetItemQuality(int itemID, int itemQuality); 

	//Resources *resource;
	vector<int> ResourceList;
	
private:
	int itemID, itemValue, itemQuality;
	float mood;
	string itemName;

};

