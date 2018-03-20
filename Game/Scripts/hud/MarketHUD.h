#pragma once

#include "components\Behaviour.h"
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

class MarketHUD : public Behaviour {
public:
	static MarketHUD* Create(GameObject* gameObject, EHUD::HUDCanvas *root, class MarketManager* marketManager);

	EHUD::HUDElement* GetWrapper();
	void Copy(GameObject* copyObject);
	void OnLoad();
	void Start();
	void Update();

	void Input();

private:
	/*HUD Elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper;

	class MarketHUDElement *MHElement, *MHElement2, *MHElement3, *MHElement4, *MHElement5, *MHElement6;

	class MarketManager* marketManager;
	class LocalMarket *market1, *market2;
	bool keyReleased = true;


};