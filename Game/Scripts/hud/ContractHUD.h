#pragma once

#include "components\Behaviour.h"
#include <vector>

//Forward Declarations

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TextWidget;
	}
}

namespace EHUD = Engine::HUD;

class ContractHUD : public Behaviour {
public:

	static ContractHUD* Create(GameObject* gameObject, EHUD::HUDCanvas* root, class ContractManager* contractManager);

	EHUD::HUDElement* GetWrapper();
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update();

	void Input();
	void GenerateTitleOfHUD();

private:
	/*HUD elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper;
	EHUD::TextWidget* contractTitle;

	//class ContractHUDElement* CHElement, *CHElement2, *CHElement3;
	int count = 0;

	class ContractManager* contractManager;
	class Contract* contract0, *contract1, *contract2;
	bool keyReleased = true;

	vector <Contract*> vectorOfContracts;
	vector <class ContractHUDElement*> CHElement;
	int sizeOfContractList = 0;
};
