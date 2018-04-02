#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>
#include "../ResourceManager.h"

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

	static ContractHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class Contract* contract); 

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	void SetContract(Contract* contractToSet);
	void SetAllActive(bool state);
	class Contract* GetContract();

	void GenerateContractElements();
	void GenerateKSuffix();
private:
	class Contract* contract;
	EHUD::TextWidget* text,	*contractStatus, *fulfill, *resource, *resourceName, *reward, *contractIssueNumber, *contractID, *difficulty;
	EHUD::HUDElement* contractHUD;
	EHUD::WHUDContainer* resourceIcon;
	ResourceManager *resourceManager;

};
