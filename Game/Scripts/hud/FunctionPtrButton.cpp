#include "FunctionPtrButton.h"

FunctionPtrButton * FunctionPtrButton::Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, FunctionPtrBinder *binder)
{
	FunctionPtrButton * fpb = new FunctionPtrButton();
	fpb->rect = rect;
	fpb->baseTexture = baseTexture;
	fpb->binder = binder;
	element->AttachWidget(fpb);
	return fpb;
}

void FunctionPtrButton::SetBaseTexture(std::string basetexture)
{
	baseTexture = basetexture;
	activeTexture = baseTexture;
}

void FunctionPtrButton::OnPointerMouseDown(EventData data)
{
	if (IsActive())
	{
		binder->Call();
	}
}

void FunctionPtrButton::EventRegistration()
{
	registerMouseDown = true;
}

void FunctionPtrButton::Update(double dt)
{
}

FunctionPtrButton::~FunctionPtrButton()
{
	delete binder;
}
