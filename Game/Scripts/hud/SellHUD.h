/*
SellHUD class used to allow the player to sell buildings
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

class SellHUD : public Behaviour
{
public:
	static SellHUD * Create(GameObject *gameObject,
		EHUD::HUDCanvas *root, class PlayerActions* pla, class ResourceManager* rManager);
	EHUD::HUDElement* GetWrapper();
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update();
	void Input();
private:
	/**HUD elements */
	class PlayerActions* pla;
	EHUD::HUDCanvas * root;
	EHUD::HUDElement* wrapper;
	/**/
	class SellHUDElement* SHElement;
	bool keyHeld = false;
	class ResourceManager* rManager;
};

