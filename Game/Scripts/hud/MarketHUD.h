#pragma once

#include "components\Behaviour.h"
#include <vector>
#include "WidgetToggleButton.h"

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

	void SellResource();
private:
	/*HUD Elements*/
	EHUD::HUDCanvas* root;
	EHUD::HUDElement* wrapper, *wrapper2, *wrapper3;
	EHUD::HUDElement *buyButton, *sellButton;

	class MarketHUDElement *MHElement, *MHElement2;

	class MarketManager* marketManager;
	class LocalMarket *market1, *market2;
	bool keyReleased = true;


};