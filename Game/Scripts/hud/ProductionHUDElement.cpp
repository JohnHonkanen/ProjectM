#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "..\PlayerActions.h"
#include "ProductionHUDElement.h"
#include "..\Production.h"
#include "ProductionButton.h"

/*ToDo:
Button to turn building on and off manually
*/
ProductionHUDElement::ProductionHUDElement()
{
}

ProductionHUDElement::~ProductionHUDElement()
{
}

ProductionHUDElement * ProductionHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, Production *prod)
{
	ProductionHUDElement *p = new ProductionHUDElement();
	p->rect = rect;
	p->prod = prod;
	p->productionHUD = element;
	element->AttachWidget(p);
	return p;
}

void ProductionHUDElement::Start()
{
	title = HUD::TextWidget::Create(productionHUD, { 10,60,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	level = HUD::TextWidget::Create(productionHUD, { 10,90,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	producing = HUD::TextWidget::Create(productionHUD, { 10,120,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 26, 1, vec3(1, 1, 1));
	pButton = ProductionButton::Create(productionHUD, { 240,10,50,50 }, "Game/Assets/Textures/ground.jpg", nullptr);
	StartChildWidgets();
}

void ProductionHUDElement::OnLoad()
{

}

void ProductionHUDElement::Update()
{
	if (prod != nullptr) {
		title->text = "Building: " + prod->GetName();
		level->text = " TestingLevel: " + prod->GetProductionEfficiency();
		producing->text = "Current Output: " + prod->GetProductionName();
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
