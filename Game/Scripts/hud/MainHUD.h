#pragma once
#include "components\Behaviour.h"
#include <vector>
#include "../BuildingController.h"
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

class MainHUD : public Behaviour
{
public:
	static MainHUD * Create(GameObject *gameObject, EHUD::HUDCanvas *root, BuildingController * buildingController, class ContractHUD* contractHUD);
	void Copy(GameObject *copyObject);

	void OnLoad();

private:

	/**HUD elements */
	EHUD::HUDCanvas * root;
	EHUD::HUDElement* wrapper;
	/**/

	BuildingController * buildingController;
	class ContractHUD* contractHUD;
	class MarketHUD* marketHUD;
};
