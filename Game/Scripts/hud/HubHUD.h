#pragma once
#include "components\Behaviour.h"
#include "HUDInventorySlot.h"
#include <vector>
#include "../ResourceManager.h"
#include "WidgetToggleButton.h"
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

class HubHUD : public Behaviour
{
public:
	static HubHUD * Create(GameObject * gameObject, EHUD::HUDCanvas * root, class Hub* hub, ResourceManager *resourceManager);
	void Copy(GameObject *copy);

	void OnLoad();
	void Update();

	void CreateSlot();
private:
	class Hub* hub;
	ResourceManager *resourceManager;

	EHUD::HUDCanvas * root;
	EHUD::HUDElement *wrapper;
	EHUD::HUDElement *inventoryBox;
	EHUD::HUDElement *syncButton;
	EHUD::TextWidget *goldCounter;

	std::vector<HUDInventorySlot *> inventoryDisplay;


};