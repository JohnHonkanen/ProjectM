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
	static ProductionHUDElement* Create(HUDElement* element, EHUD::HUDRect rect,  class Production *prod, class ResourceManager* rManager);
	void Start();
	void OnLoad();
	void Update();
	void DrawWidget(unsigned int shader);
	void Input();
	void SetProduction(class Production *prod);
	void DeleteItems();
	void ChangeActive();
	void CloseProductionWindows();


private:
	EHUD::TextWidget* title;
	EHUD::TextWidget* level;
	EHUD::TextWidget* producing;
	EHUD::TextWidget* storage1;
	EHUD::TextWidget* storage2;


	vector<EHUD::TextWidget*> text;
	class Production * prod;

	class ProductionButton * pButton;		//Set Production button

	class ProductionResourceButton * rButton;		//Producing Resource Button
	class ProductionResourceButton * aButton;		//Active Building Button

	EHUD::HUDElement* productionHUD;
	class ResourceManager* rManager;


};