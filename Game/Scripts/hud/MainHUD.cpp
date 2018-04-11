#include "MainHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "WidgetToggleButton.h"
#include "BuildingListGroupElement.h"
#include "ContractHUD.h"
#include "SellHUD.h"

MainHUD * MainHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, BuildingController * buildingController, ContractHUD* contractHUD, SellHUD* sellHUD)
{
	MainHUD * mh = new MainHUD();
	mh->root = root;
	mh->buildingController = buildingController;
	mh->contractHUD = contractHUD;
	mh->sellHUD = sellHUD;
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
	
	WidgetToggleButton::Create(wrapper, { 105 ,567 , 60,60 }, "Game/Assets/Textures/contract_button.png",
		contractHUD->GetWrapper()
	);

	WidgetToggleButton::Create(wrapper, { 1100 , 630 , 60,60 }, "Game/Assets/Textures/sell_icon.png",
		sellHUD->GetWrapper()
	);
}
