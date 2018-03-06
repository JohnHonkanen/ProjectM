#include "BuildingSelectorButton.h"

BuildingSelectorButton * BuildingSelectorButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture)
{
	BuildingSelectorButton * bsb = new BuildingSelectorButton();
	bsb->rect = rect;
	bsb->baseTexture = baseTexture;
	bsb->activeTexture = baseTexture;

	element->AttachWidget(bsb);

	return bsb;
}
