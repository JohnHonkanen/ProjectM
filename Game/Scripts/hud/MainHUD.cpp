#include "MainHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "WidgetToggleButton.h"
#include "BuildingListGroupElement.h"

MainHUD * MainHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, BuildingController * buildingController)
{
	MainHUD * mh = new MainHUD();
	mh->root = root;
	mh->buildingController = buildingController;

	gameObject->AddComponent(mh);

	return mh;

}

void MainHUD::Copy(GameObject * copyObject)
{
}

void MainHUD::OnLoad()
{
	wrapper = EHUD::WHUDContainer::Create(root, { 0 , 0, 1280, 720 }, "Game/Assets/Textures/size_test.png", true);

	WidgetToggleButton::Create(wrapper, {35,500 , 60,60}, "Game/Assets/Textures/building_list_icon.png",
		BuildingListGroup::Create(wrapper, { 0, 0, 0, 0 }, buildingController)
		);
	

}
