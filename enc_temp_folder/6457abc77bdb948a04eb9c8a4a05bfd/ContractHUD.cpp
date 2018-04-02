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
	/*vectorOfContracts.push_back(&contractManager->FindContract(ContractName::Player_Contract, 0));
	CHElement.push_back(ContractHUDElement::Create(wrapper, { 25 , 25, 0, 0 }, vectorOfContracts[0]));*/

	for (int i = 0; i < contractManager->GetSizeOfListOfContract(); i++) {
		vectorOfContracts.push_back(&contractManager->FindContract(ContractName::Player_Contract, i));
		CHElement.push_back(ContractHUDElement::Create(wrapper, { 25 , (float)25 + 175 * i, 0, 0 }, vectorOfContracts[i]));
	}
	
	//contract0 = &contractManager->FindContract(ContractName::Player_Contract, 0);
	//contract1 = &contractManager->FindContract(ContractName::Player_Contract, 1);
	//contract2 = &contractManager->FindContract(ContractName::Player_Contract, 2);

	//CHElement = ContractHUDElement::Create(wrapper, { 25 , 25, 0, 0 }, contract0);
	//CHElement2 = ContractHUDElement::Create(wrapper, { 25 , (200), 0, 0 }, contract1);
	//CHElement3 = ContractHUDElement::Create(wrapper, { 25 , (375), 0, 0 }, contract2);
}

void ContractHUD::Update()
{

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
