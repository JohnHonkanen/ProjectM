#pragma once

#include "hud\HUDWidget.h"
#include "hud\HUDRect.h"
#include "../ResourceManager.h"
#include <string>

//namespace Alias
namespace EHUD = Engine::HUD;
namespace Engine {
	namespace HUD {
		class TextWidget;
	}
}

class ProductionHUDElement : public EHUD::HUDWidget {
public:
	ProductionHUDElement();
	~ProductionHUDElement();
	static ProductionHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class PlayerActions* pla);
	void Start();
	void Update();
	void DrawWidget(unsigned int shader);
	void Input();


private:
	EHUD::TextWidget* title;
	vector<EHUD::TextWidget*> text;
	class PlayerActions* pla;
	EHUD::HUDElement* productionHUD;


};