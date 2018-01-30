#pragma once

#include <string>
#include <iostream>

using namespace std;

class Resources
{
public:
	Resources();
	~Resources();

	int itemID, itemValue, itemQuality;
	string itemName;
private:
	

	int createItem(int itemID, string itemName, int itemValue, int itemQuality);

	int setItemID(int itemID);
	int getItemID(int itemID);

	string setItemName(string itemName);
	string getItemName(string itemName);

	int setItemValue(int itemID, int itemValue);
	int getItemValue();

	int setItemQuality(int itemID, int itemQuality);
	int getItemQuality(int itemID, int itemQuality); 
};

