#include "PlayerEconHUDElement.h"

PlayerEconHUDElement * PlayerEconHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, PlayerEconomy * playerEconomy)
{
	PlayerEconHUDElement *p = new PlayerEconHUDElement;
	p->rect = rect;
	p->playerEconomy = playerEconomy;

	element->AttachWidget(p);

	return p;
}

void PlayerEconHUDElement::Start()
{

	StartChildWidgets();
}

void PlayerEconHUDElement::Update()
{

}

void PlayerEconHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}
}

PlayerEconomy * PlayerEconHUDElement::GetPlayerEcon()
{
	return playerEconomy;
}
