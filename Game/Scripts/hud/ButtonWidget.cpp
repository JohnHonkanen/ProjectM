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
		IPointerEnter::RegisterToEvents(&rect);
	}

	if (registerExit)
	{
		IPointerExit::RegisterToEvents(&rect);
	}

	if (registerMouseDown)
	{
		IPointerMouseDown::RegisterToEvents(&rect);
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
