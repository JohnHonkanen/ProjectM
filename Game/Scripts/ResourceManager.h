#pragma once

#include "Resources.h"

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	Resources AddResource(int itemID, string itemName, string SKU, int itemPrice, int itemStock);
	Resources FindResource(int itemID);

private:
	int itemIndex = 0;
	Resources resource[64];
	Resources resources;
};