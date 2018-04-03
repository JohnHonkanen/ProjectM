#pragma once

#include "components\Behaviour.h"
#include <vector>

// Forward Declarations
namespace Engine {
	namespace HUD {
		class HUDCavas;
		class HUDElement;
		class TestWidget;
	}
}

// namespace alias
namespace EHUD = Engine::HUD;

class DockHUD : public Behaviour {
public:
	static DockHUD * Create(GameObject *gameObject, EHUD::HUDCavas *root, class PlayerAction *playerAction, class ResourceManager *resourceManager);

	void Copy(GameObject *gameObject);
	void OnLoad();
	void Start();
	void Update();

private:
	class PlayerActions* playerAction;
	class DockHUDElement* DHElement;

	class ResourceManager* resourceManager;


};