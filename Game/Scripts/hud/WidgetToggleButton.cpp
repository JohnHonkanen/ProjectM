#include "WidgetToggleButton.h"

WidgetToggleButton * WidgetToggleButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, HUDElement * group)
{
	WidgetToggleButton *wtb = new WidgetToggleButton();
	wtb->rect = rect;
	wtb->baseTexture = baseTexture;
	wtb->SetOriginalDimensions(rect.width, rect.height);
	wtb->group = group;
	group->SetActive(false);

	element->AttachWidget(wtb);
	return wtb;
}

void WidgetToggleButton::OnPointerMouseDownImplementation(EventData data)
{
	group->SetActive(!group->IsActive());
}
