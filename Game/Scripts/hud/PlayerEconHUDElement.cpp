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
	playerEconHUD = EHUD::WHUDContainer::Create(this, { 0,0, 225, 24 }, "Game/Assets/Textures/black.jpg", true);
	resourceIcon = EHUD::WHUDContainer::Create(this, { 200, 5, 14, 14 }, playerEconomy->GetGBIcon(), true);

	// Player gold amount
	playerGold = EHUD::TextWidget::Create(playerEconHUD, { 10, 16, 0, 0 }, "Player Gold Amount: " + to_string(playerEconomy->GetGBAmount(100)), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	
	text = EHUD::TextWidget::Create(playerEconHUD, { 10, 128, 0, 0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	StartChildWidgets();
}

void PlayerEconHUDElement::Update()
{
	playerGold->text = "Player Gold Amount: " + to_string(playerEconomy->GetGBAmount(100));
}

void PlayerEconHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}


}

void PlayerEconHUDElement::SetPlayerEcon(PlayerEconomy* economyToSet)
{
	playerEconomy = economyToSet;
}

PlayerEconomy * PlayerEconHUDElement::GetPlayerEcon()
{
	return playerEconomy;
}
