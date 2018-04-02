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

EHUD::HUDElement * ContractHUD::GetWrapper()
{
	return wrapper;
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
	contract = contractManager->FindContract(ContractName::Player_Contract, 0);
	contract2 = contractManager->FindContract(ContractName::Player_Contract, 1);
	contract3 = contractManager->FindContract(ContractName::Player_Contract, 2);

	//contract = contractManager->FindPersistentContract(1);
	//contract2 = contractManager->FindPersistentContract(2);
	//contract3 = contractManager->FindPersistentContract(3);

	CHElement = ContractHUDElement::Create(wrapper, { 25 , 25, 0, 0 }, contract);
	CHElement2 = ContractHUDElement::Create(wrapper, { 25 , (200), 0, 0 }, contract2);
	CHElement3 = ContractHUDElement::Create(wrapper, { 25 , (375), 0, 0 }, contract3);
}

void ContractHUD::Update()
{
	auto contractList = contractManager->GetList();
	//int i = 0;

	for (Contract* c : contractList) {

		ContractHUDElement* cHUD = nullptr;

		// Determines the slot of the contract HUD and index.
		// 1 = top, 2 = middle, 0 = bottom
		int index = c->GetContractIndex() % 3;

		switch (index) {
		case 1:
			cHUD = CHElement;
			break;

		case 2:
			cHUD = CHElement2;
			break;

		case 0:
			cHUD = CHElement3;
			break;

		default:
			break;
		}

		if (cHUD != nullptr && !cHUD->IsActive()) 
		{
			cHUD->SetContract(c);
			cHUD->SetAllActive(true);
		}
		//i++;
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
