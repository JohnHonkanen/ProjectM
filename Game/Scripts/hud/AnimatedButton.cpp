#include "AnimatedButton.h"

void AnimatedButton::OnPointerEnter(EventData data)
{
	OnPointerEnterAnimation();
	OnPointerEnterImplementation(data);
}

void AnimatedButton::OnPointerExit(EventData data)
{
	OnPointerExitAnimation();
	OnPointerExitImplementation(data);
}

void AnimatedButton::OnPointerMouseDown(EventData data)
{
	OnPointerMouseDownAnimation();
	OnPointerMouseDownImplementation(data);
}

void AnimatedButton::EventRegistration()
{
	registerEnter = true;
	registerExit = true;
	registerMouseDown = true;
}

void AnimatedButton::OnPointerEnterImplementation(EventData data)
{
}

void AnimatedButton::OnPointerExitImplementation(EventData data)
{
}

void AnimatedButton::OnPointerMouseDownImplementation(EventData data)
{
}

void AnimatedButton::OnPointerEnterAnimation()
{
}

void AnimatedButton::OnPointerExitAnimation()
{
}

void AnimatedButton::OnPointerMouseDownAnimation()
{
}
