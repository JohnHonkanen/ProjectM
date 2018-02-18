#include "BuildingHUD.h"
#include "core\GameObject.h"
BuildingHUD * BuildingHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root, BuildingManager * buildingManager, BuildingController * buildingController)
{
	BuildingHUD *bh = new BuildingHUD();
	bh->buildingManager = buildingManager;
	bh->buildingController = buildingController;
	bh->root = root;

	gameObject->AddComponent(bh);

	return bh;
}

void BuildingHUD::Copy(GameObject * copyObject)
{
	//Does Nothing.
}
