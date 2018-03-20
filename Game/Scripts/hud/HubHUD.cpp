#include "HubHUD.h"
#include "core\GameObject.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "hud\HUDCanvas.h"

HubHUD * HubHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, Hub * hub)
{
	HubHUD * hh = new HubHUD();
	hh->root = root;
	hh->hub = hub;

	gameObject->AddComponent(hh);

	return hh;
}

void HubHUD::Copy(GameObject * copy)
{
}

void HubHUD::OnLoad()
{
	wrapper = EHUD::WHUDContainer::Create(root, { 300, 100, 680, 500 }, "Game/Assets/Textures/black.jpg", true);
	EHUD::WHUDContainer::Create(wrapper, { 10, 50, 300, 440 }, "Game/Assets/Textures/hub_containers.png", true);
	EHUD::TextWidget::Create(wrapper, { 10, 32, 0, 0 }, "Hub Panel", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 32, 1, vec3(1, 1, 1));
}
