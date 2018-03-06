#pragma once
#include "ButtonWidget.h"

class AnimatedButton : public ButtonWidget
{
public:
	/** Pointer Enter Bounds Event*/
	virtual void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	virtual void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	virtual void OnPointerMouseDown(EventData data);
	/** Used to set the register event bool (registerEnter, registerExit and registerMouseDown)*/
	virtual void EventRegistration();

	virtual void Update(double dt);

protected:
	/** Pointer Enter Bounds Event Implementation */
	virtual void OnPointerEnterImplementation(EventData data);
	/** Pointer Exit Bounds Event Implementation */
	virtual void OnPointerExitImplementation(EventData data);
	/** Pointer Click Event Implementation */
	virtual void OnPointerMouseDownImplementation(EventData data);

	/** Pointer Enter Bounds Event Animation */
	virtual void OnPointerEnterAnimation();
	/** Pointer Exit Bounds Event Animation */
	virtual void OnPointerExitAnimation();
	/** Pointer Click Event Animation */
	virtual void OnPointerMouseDownAnimation();

	void SetOriginalDimensions(float x, float y);

private:

	void Grow(double dt);
	void Shrink(double dt);
	void Stable();

	enum ANIM_STATE
	{
		STABLE,
		GROW,
		SHRINK,
	};
	struct Rect {
		float sizeX, sizeY;
	};
	ANIM_STATE state;
	Rect originalRect;

	float increasedSize = 50;
	float decreaseSize = 10;
};