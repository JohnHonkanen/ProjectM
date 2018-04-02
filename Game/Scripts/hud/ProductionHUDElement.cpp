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

	//p->rManager = rManager;
	p->rect = rect;
	p->prod = prod;
	p->productionHUD = element;
	element->AttachWidget(p);
	return p;
}

void ProductionHUDElement::Start()
{
	title = HUD::TextWidget::Create(productionHUD, { 20,40,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	level = HUD::TextWidget::Create(productionHUD, { 20,70,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	producing = HUD::TextWidget::Create(productionHUD, { 20,100,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	rButton = ProductionResourceButton::Create(productionHUD, { 150,75,30,30 }, "Game/Assets/Textures/Resource/missing-16.png", nullptr);//Resource
	storage1 = HUD::TextWidget::Create(productionHUD, { 20,130,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	storage2 = HUD::TextWidget::Create(productionHUD, { 20,160,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	ingredient = HUD::TextWidget::Create(productionHUD, { 20,190,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 24, 1, vec3(1, 1, 1));
	iButton = ProductionResourceButton::Create(productionHUD, { 150,165,30,30 }, "Game/Assets/Textures/Resource/missing-16.png", nullptr);//Ingredient
	aButton = ProductionResourceButton::Create(productionHUD, { 240,165,30,30 }, "Game/Assets/Textures/Resource/inactive-16.png", nullptr);//Active
	pButton = ProductionButton::Create(productionHUD, { 240,10,50,50 }, "Game/Assets/Textures/output_icon.png", nullptr);//Production
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
			title->text = "Building: " + prod->gameObject->name;
			level->text = "Level: " + to_string(prod->GetProductionEfficiency());
			producing->text = "Producing: ";
			if (prod->GetType() == DOME) {
				iButton->SetActive(false);
				ingredient->text = " ";
				storage1->text = "Storage: " + to_string(prod->GetOutputCount());
				storage2->text = " ";
			}
 			else if (prod->GetType() == FACTORY){
				iButton->SetActive(true);
				ingredient->text = "Needs: ";
				storage1->text = "Output: " + to_string(prod->GetOutputCount());
				storage2->text = "Input: " + to_string(prod->GetInputCount());
				if (prod->GetProducing()) {
					iButton->SetIcon(IconName(GetIngredient()));
				}
			}
			if (prod->GetProducing() == true) {
				ResourceName res = prod->GetProduction();
				rButton->SetIcon(IconName(res));
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
	if (prod->GetActive() == false) {
		aButton->SetIcon("Game/Assets/Textures/Resource/inactive-16.png");
	}
	if (prod->GetActive() == true) {
		aButton->SetIcon("Game/Assets/Textures/Resource/active-16.png");
	}

}

void ProductionHUDElement::ChangeActive()
{
	if (prod->GetProducing()) {
		prod->SetActive(!prod->GetActive());
	}
}

void ProductionHUDElement::CloseProductionWindows()
{
	pButton->CloseProductionWindows();
}

string ProductionHUDElement::IconName(ResourceName res)
{
	return string(GameManager::gameManager->resourceManager.Find(res)->GetResourceIcon());
}

ResourceName ProductionHUDElement::GetIngredient()
{
	return ResourceName(GameManager::gameManager->recipeManager.GetInput(prod->GetProduction()));
}
