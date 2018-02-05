#pragma once

#include "Resources.h"

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	void Init();
	void AddResource(Resources resource);
	Resources FindResource(int itemID);

private:
	int itemIndex = 0;
	Resources resource[5];

};