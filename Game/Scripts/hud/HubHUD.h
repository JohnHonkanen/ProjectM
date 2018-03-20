#pragma once
#include "components\Behaviour.h"

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
	static HubHUD * Create(GameObject * gameObject, EHUD::HUDCanvas * root, class Hub* hub);
	void Copy(GameObject *copy);

	void OnLoad();

private:
	class Hub* hub;
	EHUD::HUDCanvas * root;
	EHUD::HUDElement *wrapper;
};