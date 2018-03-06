#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "..\PlayerActions.h"
#include "ProductionHUDElement.h"
#include "..\Production.h"
#include "ProductionButton.h"


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
	title = HUD::TextWidget::Create(productionHUD, { 0,60,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	//Level = HUD::TextWidget::Create(productionHUD, { 0,60,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	//Producing = HUD::TextWidget::Create(productionHUD, { 0,60,0,0 }, " hi ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	pButton = ProductionButton::Create(productionHUD, { 240,10,50,50 }, "Game/Assets/Textures/ground.jpg", nullptr);
	
	StartChildWidgets();
}

void ProductionHUDElement::OnLoad()
{

}

void ProductionHUDElement::Update()
{
	if (prod != nullptr) {
		title->text = prod->GetName();
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
