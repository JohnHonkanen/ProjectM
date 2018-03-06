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

private:
	/*HUD elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper;

	class ContractHUDElement* CHElement, *CHElement2, *CHElement3;
	int count = 0;

	class ContractManager* contractManager;
	class Contract* contract, *contract2, *contract3;
	bool keyReleased = true;

};
