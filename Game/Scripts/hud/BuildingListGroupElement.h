#pragma once
#include "hud\HUDWidget.h"
#include <vector>
namespace EHUD = Engine::HUD;
class BuildingListGroup : public EHUD::HUDWidget
{
public:
	static BuildingListGroup* Create(HUDElement* element, EHUD::HUDRect rect);

	void Start();
	void Update();
	void DrawWidget(unsigned int shader);

	void AddButtons(class AnimatedButton *button);
private:
	vector<class AnimatedButton*> buttons;
	HUDElement *parent;
};