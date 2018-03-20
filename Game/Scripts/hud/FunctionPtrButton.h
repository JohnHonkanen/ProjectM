#pragma once
#include "ButtonWidget.h"
class FunctionPtrBinder {
public:
	virtual void Call() = 0;
};
class FunctionPtrButton : public ButtonWidget {
public:
	static FunctionPtrButton *Create(HUDElement * element, EHUD::HUDRect rect, std::string baseTexture, FunctionPtrBinder * binder);

	virtual void OnPointerMouseDown(EventData data);
	virtual void EventRegistration();
	virtual void Update(double dt);

	~FunctionPtrButton();
private:
	FunctionPtrBinder * binder;
};