#pragma once

#include "components\Behaviour.h"
#include <vector>

//Forward Declarations

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
	}
}

namespace EHUD = Engine::HUD;

class ContractHUD : public Behaviour {
public:

	static ContractHUD* Create(GameObject* gameObject, EHUD::HUDCanvas* root, class ContractManager* contractManager);

	void Copy(GameObject *copyObject);
	void OnLoad();

	void Input();

private:
	/*HUD elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper;

	class ContractManager* contractManager;
	bool keyReleased = true;

};
