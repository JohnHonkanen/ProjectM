#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>
#include "../ResourceManager.h"
#include "../Contract.h"

//Namespace Alias 
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
		class WHUDContainer;
	}
}

class ContractHUDElement : public EHUD::HUDWidget {

public:
	static ContractHUDElement* Create(HUDElement* element, EHUD::HUDRect rect); 

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	void SetAllActive(bool state);
	Contract GetContract();

	void GenerateContractElements();
	void GenerateKSuffix();
	void GenerateDifficultyBackground(int difficulty);
	int GetContractDifficulty();

	void SetContract(Contract contractToSet);
private:
	Contract contract;
	EHUD::TextWidget* text,	*contractStatus, *fulfill, *resource, *resourceName, *reward, *contractIssueNumber, *contractID, *difficulty;
	EHUD::WHUDContainer* contractHUD;
	EHUD::WHUDContainer* resourceIcon;
	ResourceManager *resourceManager;

};
