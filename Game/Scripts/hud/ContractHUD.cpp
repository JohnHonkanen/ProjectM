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
	wrapper = EHUD::WHUDContainer::Create(root, { 950, 50, 300, 200 }, "Game/Assets/Textures/Cblack.jpg", true);
	wrapper->SetActive(false);

	


	Engine::GameEngine::manager.inputManager.AddKey("toggleContractHUD", "c");
}

void ContractHUD::Start()
{
	Contract* contract = contractManager->FindPersistentContract(1);
	CHElement = ContractHUDElement::Create(wrapper, { 25 , 25, 0, 0 }, contract);

	/*Contract* contract = contractManager->FindPersistentContract(1);
	CHElement = ContractHUDElement::Create(wrapper, { 25 , 25 * i, 0, 0 }, contract);*/
}

void ContractHUD::Update()
{
	//text->text = "word: " + to_string(count);
	//count++;
}

void ContractHUD::Input()
{
	int userInput = Engine::GameEngine::manager.inputManager.GetKey("toggleContractHUD");

	if (userInput == 1) {
		if (keyReleased == true) {
			keyReleased = false;
			
			wrapper->SetActive(!wrapper->IsActive());

			/*for (int i = 1; i < 2; i++) {
				Contract* contract = contractManager->FindPersistentContract(1);
				bool contractStatus = false;
				if (contractManager->FindPersistentContract(1)->GetStatus() == true) {
					CHElement = ContractHUDElement::Create(wrapper, { (float)25, (float)25, (float)0, (float)0 }, contract);
				}
				else {
					break;
				}
			}*/
			
			contractManager->NumberOfActiveContract();
				
		} 
	}
	else {
		if (userInput == 0) {
			keyReleased = true;
		}
	}
}
