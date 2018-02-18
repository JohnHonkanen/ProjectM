#include "ContractHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Contract.h"


ContractHUDElement * ContractHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, Contract* contract)
{
	ContractHUDElement *c = new ContractHUDElement();
	c->rect = rect;
	c->contract = contract;

	element->AttachWidget(c);

	return c;
}

void ContractHUDElement::Start()
{
	// Text
	contractHUD = EHUD::WHUDContainer::Create(this, { 0, 0, 250, 150 }, "Game/Assets/Textures/black.jpg", true);
	text = EHUD::TextWidget::Create(contractHUD, { 10, 25, 100, 100 }, " 123", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	StartChildWidgets();
}

void ContractHUDElement::Update()
{
	//text->text = contract->GetTime(); //<---- Update not implemented yet
}

void ContractHUDElement::DrawWidget(unsigned int shader)
{
	text->text = to_string((int)contract->GetTime() / 1000) + "s";
	cout << text->text << endl << endl;
}
