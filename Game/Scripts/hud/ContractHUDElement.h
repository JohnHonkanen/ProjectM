#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include <string>

//Namespace Alias 
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
	}
}

class ContractHUDElement : public EHUD::HUDWidget {

public:

	static ContractHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class Contract* contract); 

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);

private:
	class Contract* contract;
	EHUD::TextWidget* text;
	EHUD::HUDElement* contractHUD;

};
