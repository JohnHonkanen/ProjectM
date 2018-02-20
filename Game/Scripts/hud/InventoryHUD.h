/*
InventoryHUD class used at a HUD widget to display the inventories of buildings.
Dev: Jack Smith (B00308927)
*/
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

class InventoryHUD : public Behaviour
{
public:
	static InventoryHUD * Create(GameObject *gameObject,
		EHUD::HUDCanvas *root, class PlayerActions* pla, class ResourceManager* rManager);

	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update();
	void Input();
	void SetInventory(vector<class Inventory*> inventory) { this->inventory = inventory; };
private:
	/**HUD elements */
	class PlayerActions* pla;
	EHUD::HUDCanvas * root;
	EHUD::HUDElement* wrapper;
	/**/
	class InventoryHUDElement* IHElement;
	bool keyHeld = false;
	vector<class Inventory*> inventory;
	class ResourceManager* rManager;

};