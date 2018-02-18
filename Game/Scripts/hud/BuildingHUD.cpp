#include "BuildingHUD.h"
#include "core\GameObject.h"
#include "..\BuildingController.h"
#include "..\BuildingManager.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"

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

void BuildingHUD::OnLoad()
{
	//Create our HUD elements based on buildings in Building Manager
	wrapper = EHUD::WHUDContainer::Create(root, { 100 , 100, 100, 100 }, "Game/Assets/Textures/ground.jpg", true),
}
