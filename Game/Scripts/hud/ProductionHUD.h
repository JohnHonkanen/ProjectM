/*
ProductionHUD class used a HUD widget to display the properties of buildings and change production type.
*/
#pragma once
#include "components\Behaviour.h"
#include <vector>
//Forward Declaration
namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TestWidget;
	}
}

//Namespace alias
namespace EHUD = Engine::HUD;

class ProductionHUD : public Behaviour {
public:
	static ProductionHUD * Create(	GameObject *gameObject,
									EHUD::HUDCanvas *root,
									class PlayerActions *pla,
									class ResourceManager* rManager);
	void Copy(GameObject* gameObject);
	void OnLoad();												//calss hud wrapped
	void Start();
	void Update();												//Creates the main production building HUD when a dome or factory is selected
	void Input();


private:
	class PlayerActions* pla;
	EHUD::HUDCanvas * root;
	EHUD::HUDElement * wrapper;
	class ProductionHUDElement* PHElement;
	class ProductionHUDElement* RHElement;
	class ProductionHUDElement* AHElement;

	class ResourceManager* rManager;

};