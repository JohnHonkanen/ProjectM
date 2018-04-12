#pragma once
#include "ButtonWidget.h"
#include "hud\HUDRect.h"
#include <vector>
#include "../Structure.h"

namespace Engine {
	namespace HUD {
		class HUDCanvas;
		class HUDElement;
		class TestWidget;
	}
}

namespace EHUD = Engine::HUD;
class ProductionButton : public ButtonWidget {
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);						//Stops items under buttons being clicked while elemment is on screen
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);							//
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);					//Opens hud element to set building production
	void EventRegistration();
	void Start();												//Generates resource lists for factory and dome on start
	void Input();
	void Update();												//handles the opening of the hud element
	void SetProduction(class Production *production);			//Sets building production when a resource is clicked
	void SetIcon(string icon) { iconImage = icon; }				//Sets a resources icon 
	void CloseProductionWindows();								//Changes/closes hud element when another building is selected
	


	static ProductionButton * Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, class Production *production);


private:
	string iconImage;
	StructureType currentStructure = StructureType::HUB;

	class Production *production;
	class EHUD::HUDElement *root;
	class EHUD::HUDElement *containerDome, *containerFactory;

	vector<class ProductionSetterButton*> resourceListDome, resourceListFactory;

	void ConfigureResources();									//Defines which items are displayed in a resource window
	
};