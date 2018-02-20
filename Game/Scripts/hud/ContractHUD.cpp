#include "ContractHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud/widgets/HUDContainer.h"
#include "../ContractManager.h"
#include "hud\widgets\TextWidget.h"
#include "ContractHUDElement.h"

ContractHUD * ContractHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, ContractManager * contractManager)
{
	ContractHUD *contractHUD = new ContractHUD();
	contractHUD->contractManager = contractManager;
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
	wrapper = EHUD::WHUDContainer::Create(root, { 950, 50, 300, 550 }, "Game/Assets/Textures/blackG.jpg", true);
	wrapper->SetActive(false);

	Engine::GameEngine::manager.inputManager.AddKey("toggleContractHUD", "c");
}

void ContractHUD::Start()
{
	contract = contractManager->FindPersistentContract(1);
	CHElement = ContractHUDElement::Create(wrapper, { 25 , 25, 0, 0 }, contract);
	CHElement2 = ContractHUDElement::Create(wrapper, { 25 , (200), 0, 0 }, contract);
	CHElement3 = ContractHUDElement::Create(wrapper, { 25 , (375), 0, 0 }, contract);
}

void ContractHUD::Update()
{
	if (!CHElement->IsActive()) {
		// Set a new contract, activate CHelement

		//CHElement->SetContract();
		CHElement->SetActive(true);

	}
}

void ContractHUD::Input()
{
	int userInput = Engine::GameEngine::manager.inputManager.GetKey("toggleContractHUD");

	if (userInput == 1) {
		if (keyReleased == true) {
			keyReleased = false;
			
			

			wrapper->SetActive(!wrapper->IsActive());



		} 
	}
	else {
		if (userInput == 0) {
			keyReleased = true;
		}
	}
}
