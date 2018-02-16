#pragma once

#include "Resources.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"

class ResourceManager : public Behaviour
{
public:

	ResourceManager();
	~ResourceManager();

	Resources AddResource(int itemID, string itemName, string SKU, int itemPrice, int itemStock);
	Resources FindResource(int itemID);

	static ResourceManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();

	void Start();

	static const int sizeOfList = 64;
private:
	int itemIndex = 0;
	
	Resources resourceList[sizeOfList];
	Resources resources;
};