#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "..\PlayerActions.h"
#include "ProductionHUDElement.h"

ProductionHUDElement::ProductionHUDElement()
{
}

ProductionHUDElement::~ProductionHUDElement()
{
}

ProductionHUDElement * ProductionHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, PlayerActions * pla)
{
	ProductionHUDElement *p = new ProductionHUDElement();

	p->rect = rect;
	p->pla = pla;
	element->AttachWidget(p);

	return p;
	
}

void ProductionHUDElement::Start()
{
}

void ProductionHUDElement::Update()
{
}

void ProductionHUDElement::DrawWidget(unsigned int shader)
{

}

void ProductionHUDElement::Input()
{
}
