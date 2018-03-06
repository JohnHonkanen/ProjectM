/*
ProductionHUD class used a HUD widget to display the properties of buildings and change production type.
Dev: Greg Smith (B00308929)
*/
#include "ProductionHUD.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "BuildingButton.h"
#include "../PlayerActions.h"
#include "../Production.h"
#include "ProductionHUDElement.h"
#include "ProductionButton.h"


ProductionHUD * ProductionHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root, PlayerActions *pla) {

	ProductionHUD *ph = new ProductionHUD();
	ph->root = root;
	ph->pla = pla;
	gameObject->AddComponent(ph);
	return ph;
}
void ProductionHUD::Copy(GameObject* gameObject) {
	//Does Nothing
}
void ProductionHUD::OnLoad()
{
		wrapper = EHUD::WHUDContainer::Create(root, { 600,100,300,200 }, "Game/Assets/Textures/cBlack.jpg", true);
		wrapper->SetActive(true); //For testing purposes, set to false when key selection added
		HUD::TextWidget::Create(wrapper, { 10,30,50,50 }, "Production", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
		HUD::TextWidget::Create(wrapper, { 10,40,50,50 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
		PHElement = ProductionHUDElement::Create(wrapper, { 25,25,0,0 }, nullptr);
}

void ProductionHUD::Start()
{
}

void ProductionHUD::Update()
{
	if (pla->GetSelectedStructure() != nullptr && dynamic_cast<Production*>(pla->GetSelectedStructure()) != nullptr) {
		PHElement->SetProduction(dynamic_cast<Production*>(pla->GetSelectedStructure()));
		wrapper->SetActive(true);
	}
	else {
		wrapper->SetActive(false);
	}
}

void ProductionHUD::Input()
{
}
