#include "ProductionButton.h"
#include "hud\widgets\HUDContainer.h"


void ProductionButton::OnPointerEnter(EventData data)
{
}

void ProductionButton::OnPointerExit(EventData data)
{
}

void ProductionButton::OnPointerMouseDown(EventData data)
{
	cout << "hi" << endl;
	if (data.mouseButton0 == 1) {
		container->SetActive(true);
	}
	if (data.mouseButton1 == 1) {
		container->SetActive(false);
	}
}

void ProductionButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

void ProductionButton::Start()
{
	container = EHUD::WHUDContainer::Create(root, { 310,0,300,200 }, "Game/Assets/Textures/cBlack.jpg", true);
	container->SetActive(false);
}

ProductionButton * ProductionButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture)
{
	ProductionButton * button = new ProductionButton();
	button->rect = rect;
	button->baseTexture = baseTexture;
	//button->mouseEnterTexture = mouseOverTexture;
	//button->mouseDownTexture = mouseDownTexture;
	button->root = element;
	element->AttachWidget(button);

	return button;
}
