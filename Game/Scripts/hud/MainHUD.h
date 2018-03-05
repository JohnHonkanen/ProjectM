#pragma once
#include "components\Behaviour.h"
#include <vector>

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
	static MainHUD * Create(GameObject *gameObject, EHUD::HUDCanvas *root);
	void Copy(GameObject *copyObject);

	void OnLoad();

private:

	/**HUD elements */
	EHUD::HUDCanvas * root;
	EHUD::HUDElement* wrapper;
	/**/
};
