#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "..\PlayerActions.h"
#include "ProductionHUDElement.h"
#include "..\Production.h"
#include "ProductionButton.h"
#include "ProductionResourceButton.h"
#include "../GameManager.h"


/*ToDo:
Button to turn building on and off manually
*/
ProductionHUDElement::ProductionHUDElement()
{
}

ProductionHUDElement::~ProductionHUDElement()
{
}

ProductionHUDElement * ProductionHUDElement::Create(HUDElement * element, EHUD::HUDRect rect,  Production *prod, ResourceManager* rManager)
{
	ProductionHUDElement *p = new ProductionHUDElement();

	p->rManager = rManager;
	p->rect = rect;
	p->prod = prod;
	p->productionHUD = element;
	element->AttachWidget(p);
	return p;
}

void ProductionHUDElement::Start()
{
	title = HUD::TextWidget::Create(productionHUD, { 20,40,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	level = HUD::TextWidget::Create(productionHUD, { 20,70,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	producing = HUD::TextWidget::Create(productionHUD, { 20,100,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	rButton = ProductionResourceButton::Create(productionHUD, { 150,75,30,30 }, "Game/Assets/Textures/Resource/missing-16.png", nullptr);
	storage1 = HUD::TextWidget::Create(productionHUD, { 20,130,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	storage2 = HUD::TextWidget::Create(productionHUD, { 20,160,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	aButton = ProductionResourceButton::Create(productionHUD, { 240,150,30,30 }, "Game/Assets/Textures/active-16.png", nullptr);
	pButton = ProductionButton::Create(productionHUD, { 240,10,50,50 }, "Game/Assets/Textures/output_icon.png", nullptr);
	StartChildWidgets();
}

void ProductionHUDElement::OnLoad()
{

}

void ProductionHUDElement::Update()
{
	//if (prod->GetProduction()) {
		if (prod != nullptr) {
			v2::Inventory inv = prod->GetInventory();
			title->text = "Building: " + prod->GetName();
			level->text = "Level: " + to_string(prod->GetProductionEfficiency());
			producing->text = "Producing: ";
			if (prod->GetType() == DOME) {
				storage1->text = "Storage: " + to_string(inv.At(0).quantity);
			}
			else if (prod->GetType() == FACTORY){
				storage1->text = "Output: " + to_string(inv.At(0).quantity);
				storage2->text = "Input: " + to_string(inv.At(1).quantity);
			}
			if (prod->GetProducing() == true && inv.At(0).quantity > 0) {
				ResourceName res = inv.At(0).resource->GetResouceID();
				rButton->SetIcon(GameManager::gameManager->resourceManager.Find(res)->GetResourceIcon());
			}
			else {
				rButton->SetIcon("Game/Assets/Textures/Resource/missing-16.png");
			}
		}
	//}
}

void ProductionHUDElement::DrawWidget(unsigned int shader)
{
}

void ProductionHUDElement::Input()
{
}

void ProductionHUDElement::SetProduction(Production * prod)
{
	this->prod = prod;
	pButton->SetProduction(prod);
}

void ProductionHUDElement::DeleteItems()
{
	v2::Inventory inventory = prod->GetInventory();

	if (prod->GetProducing() && inventory.At(0).quantity < 0) {
		Resource res = *inventory.At(0).resource;
		inventory.Remove(res.GetResouceID(), inventory.At(0).quantity);
	}
}

void ProductionHUDElement::ChangeActive()
{
	if (prod->GetProducing()) {
		prod->SetActive(!prod->GetActive());
	}
}