#include "ProductionButton.h"
#include "hud\widgets\HUDContainer.h"
#include "..\Production.h"
#include "ProductionResourceButton.h"

void ProductionResourceButton::OnPointerEnter(EventData data)
{
}

void ProductionResourceButton::OnPointerExit(EventData data)
{
}

void ProductionResourceButton::OnPointerMouseDown(EventData data)
{
}

void ProductionResourceButton::EventRegistration()
{
}

void ProductionResourceButton::Start()
{
	StartChildWidgets();
	activeTexture = baseTexture;

	EventRegistration();
	RegisterToEvents();


}

void ProductionResourceButton::Input()
{
}

void ProductionResourceButton::Update()
{
}

void ProductionResourceButton::DeleteItems(V2 * inv)
{
}

ProductionResourceButton * ProductionResourceButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, Production * production)
{
	ProductionResourceButton * button = new ProductionResourceButton();
	button->rect = rect;
	button->baseTexture = baseTexture;
	//button->mouseEnterTexture = mouseOverTexture;
	//button->mouseDownTexture = mouseDownTexture;
	button->root = element;
	button->production = production;
	element->AttachWidget(button);

	return button;
}
