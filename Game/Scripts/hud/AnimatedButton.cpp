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

void AnimatedButton::Update(double dt)
{
	switch (state)
	{
	case AnimatedButton::STABLE:
		//Do nothing
		break;
	case AnimatedButton::GROW:
		Grow(dt);
		break;
	case AnimatedButton::SHRINK:
		Shrink(dt);
		break;
	default:
		break;
	}
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
	//state = GROW;
}

void AnimatedButton::OnPointerExitAnimation()
{
	//state = SHRINK;
}

void AnimatedButton::OnPointerMouseDownAnimation()
{
}

void AnimatedButton::SetOriginalDimensions(float x, float y)
{
	originalRect.sizeX = x;
	originalRect.sizeY = y;
}

void AnimatedButton::Grow(double dt)
{
	rect.width += 1;
	rect.height += 1;
}

void AnimatedButton::Shrink(double dt)
{
}

void AnimatedButton::Stable()
{
}
