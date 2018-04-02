/*
	Button widget for ui buttons, abstract class. Contains event registration
*/
#pragma once
#include "hud\HUDWidget.h"
#include "events\IPointerEnter.h"
#include "events\IPointerExit.h"
#include "events\IPointerMouseDown.h"

#include <string>

//Namespace alias
namespace EHUD = Engine::HUD;

class ButtonWidget : public EHUD::HUDWidget, 
	public IPointerEnter, 
	public IPointerExit, 
	public IPointerMouseDown
{
public:
	/** Pointer Enter Bounds Event*/
	virtual void OnPointerEnter(EventData data) {};
	/** Pointer Exit Bounds Event*/
	virtual void OnPointerExit(EventData data) {};
	/** Pointer Click Event*/
	virtual void OnPointerMouseDown(EventData data) {};
	/** Used to set the register event bool (registerEnter, registerExit and registerMouseDown)*/
	virtual void EventRegistration() = 0;

	virtual void Start();
	virtual void Update();
	virtual void Input();
	virtual void DrawWidget(unsigned int shader);

	void RegisterToEvents();
	//Set Textures
	virtual void SetBaseTexture(std::string texture);
	void SetMouseEnterTexture(std::string texture);
	void SetMouseDownTexture(std::string texture);

protected:
	std::string activeTexture;
	std::string baseTexture, mouseEnterTexture, mouseDownTexture;
	std::string icon;
	bool registerEnter, registerExit, registerMouseDown;

};