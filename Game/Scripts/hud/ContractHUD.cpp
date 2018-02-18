#include "ContractHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud/widgets/HUDContainer.h"

ContractHUD * ContractHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, ContractManager * contractManager)
{
	ContractHUD *contractHUD = new ContractHUD();
	contractHUD->contractManager;
	contractHUD->root = root;

	gameObject->AddComponent(contractHUD);

	return contractHUD;
}

void ContractHUD::Copy(GameObject * copyObject)
{
	//Does nothing
}

void ContractHUD::OnLoad()
{
	// Create HUD elements based on contracts in the ContractManager
	wrapper = EHUD::WHUDContainer::Create(root, { 950, 50, 300, 200 }, "Game/Assets/Textures/black.jpg", true);
	wrapper->SetActive(true);

}
