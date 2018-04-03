#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "..\PlayerActions.h"
#include "ProductionHUDElement.h"
#include "..\Production.h"
#include "ProductionButton.h"
#include "ProductionResourceButton.h"
#include "../GameManager.h"
#include "FunctionPtrButton.h"


class ActivateButtonHud : public FunctionPtrBinder
{
public:
	ActivateButtonHud() {};
	void Call() {
		production->SetActive(!production->GetActive());
		production->SetProductionEfficiency(1);
		production->SetUpkeep(production->GetInitialUpkeep());
	}
	void SetProduction(Production * p) { production = p; };
private:
	Production * production;
};
class IncreaseButtonHud : public FunctionPtrBinder
{
public:
	IncreaseButtonHud() {};
	void Call() {
		production->IncreaseLevel();
	}
	void SetProduction(Production * p) { production = p; };
private:
	Production * production;
};
class DecreaseButtonHud : public FunctionPtrBinder
{
public:
	DecreaseButtonHud() {};
	void Call() {
		production->DecreaseLevel();
	}
	void SetProduction(Production * p) { production = p; };

private:
	Production * production;
};

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
	activateButtonBinder = new ActivateButtonHud();
	increaseButtonBinder = new IncreaseButtonHud();
	decreaseButtonBinder = new DecreaseButtonHud();
	title = HUD::TextWidget::Create(productionHUD, { 20,30,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	level = HUD::TextWidget::Create(productionHUD, { 20,55,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	upkeep = HUD::TextWidget::Create(productionHUD, { 20,80,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	producing = HUD::TextWidget::Create(productionHUD, { 20,105,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	rButton = ProductionResourceButton::Create(productionHUD, { 120,88,25,25 }, "Game/Assets/Textures/Resource/missing-16.png", nullptr);//Resource icon
	storage1 = HUD::TextWidget::Create(productionHUD, { 20,130,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	storage2 = HUD::TextWidget::Create(productionHUD, { 20,155,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	ingredient = HUD::TextWidget::Create(productionHUD, { 20,180,0,0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 20, 1, vec3(1, 1, 1));
	aButton = FunctionPtrButton::Create(productionHUD, { 240,165,30,30 }, "Game/Assets/Textures/Resource/inactive-16.png", activateButtonBinder);//active button
	uButton = FunctionPtrButton::Create(productionHUD, { 200,165,30,30 }, "Game/Assets/Textures/Resource/increase-16.png", increaseButtonBinder);//increase level button
	dButton = FunctionPtrButton::Create(productionHUD, { 170,165,30,30 }, "Game/Assets/Textures/Resource/decrease-16.png", decreaseButtonBinder);//decrease level button
	iButton = ProductionResourceButton::Create(productionHUD, { 120,160,25,25 }, "Game/Assets/Textures/Resource/missing-16.png", nullptr);//Ingredient icon
	pButton = ProductionButton::Create(productionHUD, { 240,10,50,50 }, "Game/Assets/Textures/output_icon.png", nullptr);//Production
	StartChildWidgets();
}

void ProductionHUDElement::OnLoad()
{

}

void ProductionHUDElement::Update()
{

		if (prod != nullptr) {
			activateButtonBinder->SetProduction(prod);
			increaseButtonBinder->SetProduction(prod);
			decreaseButtonBinder->SetProduction(prod);
			if (prod->GetActive()) {
				aButton->SetBaseTexture("Game/Assets/Textures/Resource/active-16.png");
			}
			else {
				aButton->SetBaseTexture("Game/Assets/Textures/Resource/inactive-16.png");
			}
			v2::Inventory inv = prod->GetInventory();
			title->text = "Building: " + prod->gameObject->name;
			level->text = "Level: " + to_string(prod->GetProductionEfficiency());
			upkeep->text = "Upkeep: " + to_string(prod->GetUpkeep());
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
