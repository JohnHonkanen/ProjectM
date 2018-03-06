#include "ProductionSetterButton.h"
#include "..\Production.h"

void ProductionSetterButton::OnPointerEnter(EventData data)
{
}

void ProductionSetterButton::OnPointerExit(EventData data)
{
}

void ProductionSetterButton::OnPointerMouseDown(EventData data)
{
	/*if (!active || production==nullptr) {
		return;
	}*/
	if (data.mouseButton0 == 1) {
		production->SetProduction(resource);
	}
	cout << "testing button" << endl;
}

void ProductionSetterButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

void ProductionSetterButton::Start()
{
	StartChildWidgets();
	activeTexture = baseTexture;

	EventRegistration();
	RegisterToEvents();
}

void ProductionSetterButton::SetProduction(Production * production)
{
	this->production = production;
}

void ProductionSetterButton::SetResource(int resource)
{
	this->resource = resource;
}

void ProductionSetterButton::SetIcon(std::string icon)
{
	baseTexture = icon;
	activeTexture = baseTexture;
}

ProductionSetterButton * ProductionSetterButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string icon, Production * production, int resource)
{
	ProductionSetterButton * button = new ProductionSetterButton();
	button->rect = rect;
	button->baseTexture = icon;
	//button->mouseEnterTexture = mouseOverTexture;
	//button->mouseDownTexture = mouseDownTexture;
	button->root = element;
	button->production = production;
	button->resource = resource;
	element->AttachWidget(button);

	return button;
}
