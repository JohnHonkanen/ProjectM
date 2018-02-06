#pragma once

#include "Resources.h"

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	Resources AddResource(Resources resource, int itemID);
	Resources FindResource(int itemID);

private:
	int itemIndex = 0;
	Resources resource[5];

};