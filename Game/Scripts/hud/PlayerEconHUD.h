#pragma once 

#include "components\Behaviour.h"
#include "../PlayerEconManager.h"
#include <vector>


// Forward Declarations

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TextWidget;
	}
}

namespace EHUD = Engine::HUD;

class PlayerEconHUD :public Behaviour {
public:
	static PlayerEconHUD* Create(GameObject* gameObject, EHUD::HUDCanvas* root, class PlayerEconManager* playerEconManager);

	void Copy(GameObject* gameObject);
	void OnLoad();
	void Start();
	void Update();

	void Input();

private:
	/*HUD Elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper;

	class PlayerEconHUD* PEElement;
	class PlayerEconManager* playerEconManager;
	bool keyReleased;
};
