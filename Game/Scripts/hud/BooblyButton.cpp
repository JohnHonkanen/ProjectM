#include "BooblyButton.h"

void BooblyButton::OnPointerEnter(EventData data)
{
	OnPointerEnterAnim();
	OnPointerEnterImplementation(data);
}

void BooblyButton::OnPointerExit(EventData data)
{
	OnPointerExitAnim();
	OnPointerEnterImplementation(data);
}

void BooblyButton::OnPointerMouseDown(EventData data)
{
	OnPointerMouseDownAnim();
	OnPointerMouseDownImplementation(data);
}

void BooblyButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

void BooblyButton::OnPointerEnterAnim()
{
}

void BooblyButton::OnPointerExitAnim()
{
}

void BooblyButton::OnPointerMouseDownAnim()
{
}
