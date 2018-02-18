#pragma once
#include "components\Behaviour.h"
#include <vector>
//Forward Declaration
namespace Engine
{
	namespace HUD
	{
		class HUDCanvas;
		class HUDElement;
		class TextWidget;
	}
}

//Namespace alias
namespace EHUD = Engine::HUD;

class BuildingHUD: public Behaviour
{
public:
	static BuildingHUD * Create(GameObject *gameObject,
								EHUD::HUDCanvas *root,
								class BuildingManager *buildingManager, 
								class BuildingController * buildingController);

	void Copy(GameObject *copyObject);

	void OnLoad();

	void Input();

	class BuildingController * GetController();
private:
	/**HUD elements */
	EHUD::HUDCanvas * root;
	EHUD::HUDElement* wrapper;
	/**/

	class BuildingManager * buildingManager;
	class BuildingController * buildingController;

	bool keyHeld = false;


};