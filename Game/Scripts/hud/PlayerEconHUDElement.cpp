#include "PlayerEconHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../PlayerEconomy.h"
#include "InventoryHUDElement.h"

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

	// Text
	playerEconHUD = EHUD::WHUDContainer::Create(this, { 0,0,250, 150 }, "Game/Assets/Textures/black.jpg", true);
	resourceIcon = EHUD::WHUDContainer::Create(this, { 163, 84, 14, 14 }, playerEconomy->GetGBIcon(), true);

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

	// Player Gold Amount


}

void PlayerEconHUDElement::SetPlayerEcon(PlayerEconomy* economyToSet)
{
	playerEconomy = economyToSet;
}

PlayerEconomy * PlayerEconHUDElement::GetPlayerEcon()
{
	return playerEconomy;
}
