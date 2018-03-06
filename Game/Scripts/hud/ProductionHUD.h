/*
ProductionHUD class used a HUD widget to display the properties of buildings and change production type.
Dev: Greg Smith (B00308929)
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
									class PlayerActions *pla);
	void Copy(GameObject* gameObject);
	void OnLoad();
	void Start();
	void Update();
	void Input();


private:
	class PlayerActions* pla;
	EHUD::HUDCanvas * root;
	EHUD::HUDElement * wrapper;
	class ProductionHUDElement* PHElement;
};