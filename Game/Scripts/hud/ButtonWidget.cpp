#include "ButtonWidget.h"
#include "core\GameEngine.h"

void ButtonWidget::Start()
{
	StartChildWidgets();
	activeTexture = baseTexture;

	EventRegistration();
	RegisterToEvents();
}

void ButtonWidget::Update()
{
}

void ButtonWidget::Input()
{
}

void ButtonWidget::DrawWidget(unsigned int shader)
{
	if (activeTexture != "") {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Engine::GameEngine::manager.textureManager.getTexture(activeTexture));
		glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
	}
}

void ButtonWidget::RegisterToEvents()
{
	if (registerEnter)
	{
		if (!useWorldRect)
		{
			IPointerEnter::RegisterToEvents(&rect);
		}
		else {
			IPointerEnter::RegisterToEvents(&worldRect);
		}
		
	}

	if (registerExit)
	{
		if (!useWorldRect)
		{
			IPointerExit::RegisterToEvents(&rect);
		}
		else {
			IPointerExit::RegisterToEvents(&worldRect);
		}
		
	}

	if (registerMouseDown)
	{
		if (!useWorldRect)
		{
			IPointerMouseDown::RegisterToEvents(&rect);
		}
		else {
			IPointerMouseDown::RegisterToEvents(&worldRect);
		}
		
	}
	
}

void ButtonWidget::SetBaseTexture(std::string texture)
{
}

void ButtonWidget::SetMouseEnterTexture(std::string texture)
{
}

void ButtonWidget::SetMouseDownTexture(std::string texture)
{
}
