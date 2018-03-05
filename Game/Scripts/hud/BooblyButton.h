#pragma once
#include "ButtonWidget.h"

class BooblyButton : public ButtonWidget
{
public:
	/** Pointer Enter Bounds Event*/
	void OnPointerEnter(EventData data);
	/** Pointer Exit Bounds Event*/
	void OnPointerExit(EventData data);
	/** Pointer Click Event*/
	void OnPointerMouseDown(EventData data);
	void EventRegistration();
protected:
	virtual void OnPointerEnterImplementation(EventData data) {};
	virtual void OnPointerExitImplementation(EventData data) {};
	virtual void OnPointerMouseDownImplementation(EventData data) {};

private:
	void OnPointerEnterAnim();
	void OnPointerExitAnim();
	void OnPointerMouseDownAnim();
};