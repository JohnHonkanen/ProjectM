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
	void ChangeActive();
	void CloseProductionWindows();


private:
	EHUD::TextWidget* title;
	EHUD::TextWidget* level;
	EHUD::TextWidget* producing;
	EHUD::TextWidget* ingredient;
	EHUD::TextWidget* storage1;
	EHUD::TextWidget* storage2;

	string IconName(ResourceName res);			//Returns the resource string from the resource manager
	ResourceName GetIngredient();				//Returns the ResourceName input from the recipe manager


	vector<EHUD::TextWidget*> text;
	class Production * prod;

	class ProductionButton * pButton;		//Set Production button

	class ProductionResourceButton * rButton;		//Producing Resource Button
	class ProductionResourceButton * iButton;		//Ingredient Resource Button
	class FunctionPtrButton * aButton;				//Active Building Button
	class FunctionPtrButton * uButton;				//Increase building level
	class FunctionPtrButton * dButton;				//Decrease building level


	EHUD::HUDElement* productionHUD;
	class ResourceManager* rManager;

	class ActivateButtonHud * activateButtonBinder;
};