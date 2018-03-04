#include "PlayerEconHUD.h"

PlayerEconHUD * PlayerEconHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, PlayerEconManager * playerEconManager)
{
	PlayerEconHUD* playerEconHUD = new PlayerEconHUD();
	playerEconHUD->playerEconManager = playerEconManager;
	playerEconHUD->root = root;

	return playerEconHUD;
}

void PlayerEconHUD::Copy(GameObject * gameObject)
{
	// Does nothing
}

void PlayerEconHUD::OnLoad()
{
}

void PlayerEconHUD::Start()
{
}

void PlayerEconHUD::Update()
{
}

void PlayerEconHUD::Input()
{
}
