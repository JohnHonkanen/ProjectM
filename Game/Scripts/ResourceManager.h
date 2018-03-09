#pragma once

#include "Resources.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"

class ResourceManager : public Behaviour
{
public:

	ResourceManager();
	~ResourceManager();

	Resources AddResource(ResourceName resName, string itemName, string SKU, int itemPrice, int itemStock, string resourceIcon);
	Resources FindResource(int itemID);

	static ResourceManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();

	void OnLoad();

	int NumberOfActiveResources(); // Returns number of active contract added to resourceList.
	int RandomResources(); // Generate Random Resource ID
	static const int sizeOfList = 1280;

private:
	int itemIndex = 0;
	
	Resources resourceList[sizeOfList];
	Resources resources;
};