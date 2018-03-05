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
	static ProductionHUDElement* Create(HUDElement* element, EHUD::HUDRect rect, class Production *prod);
	void Start();
	void OnLoad();
	void Update();
	void DrawWidget(unsigned int shader);
	void Input();
	void SetProduction(class Production *prod);

private:
	EHUD::TextWidget* title;
	EHUD::TextWidget* Level;
	EHUD::TextWidget* Producing;

	vector<EHUD::TextWidget*> text;
	class Production * prod;
	EHUD::HUDElement* productionHUD;
};