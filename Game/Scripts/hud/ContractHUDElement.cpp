#include "ContractHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Contract.h"


ContractHUDElement * ContractHUDElement::Create(HUDElement * element, EHUD::HUDRect rect, Contract* contract)
{
	ContractHUDElement *c = new ContractHUDElement();
	c->rect = rect;
	c->contract = contract;

	element->AttachWidget(c);

	return c;
}

void ContractHUDElement::Start()
{
	// Text
	contractHUD = EHUD::WHUDContainer::Create(this, { 0, 0, 250, 150 }, "Game/Assets/Textures/black.jpg", true);

	// Contract Issue Number
	EHUD::TextWidget::Create(contractHUD, { 10, 16, 0, 0 }, "Contract Issue Number: " + to_string(contract->GetContractIndex()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract ID
	EHUD::TextWidget::Create(contractHUD, { 10, 32, 0, 0 }, "Contract ID: " + to_string(contract->GetContractID()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Difficulty
	EHUD::TextWidget::Create(contractHUD, { 10, 48, 0, 0 }, "Difficulty Level: " + to_string(contract->GetDifficulty()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Amount to FulFill
	fulfill = EHUD::TextWidget::Create(contractHUD, { 10, 64, 0, 0 }, "Amount to FulFill: " + to_string(contract->GetCurrent()) + "/" + to_string(contract->GetAmount()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Reward
	EHUD::TextWidget::Create(contractHUD, { 10, 80, 0, 0 }, "Reward: " + to_string(contract->GetPayment()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Time Left
	EHUD::TextWidget::Create(contractHUD, { 10, 96, 0, 0 }, "Resource to Deliver: " + to_string(contract->GetResourceID()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Status (Complete/!Complete)
	contractStatus = EHUD::TextWidget::Create(contractHUD, { 10, 112, 0, 0 }, "Status (Active/!Active): " + to_string(contract->GetStatus()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	text = EHUD::TextWidget::Create(contractHUD, { 10, 128, 0, 0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	
	StartChildWidgets();
}

void ContractHUDElement::Update()
{
	//text->text = contract->GetTime(); //<---- Update not implemented yet
}

void ContractHUDElement::DrawWidget(unsigned int shader)
{
	text->text = "Time Left: " + to_string((int)contract->GetTime() / 1000) + "s";
	contractStatus->text = "Status (Active/!Active): " + to_string(contract->GetStatus());
	fulfill->text = "Amount to FulFill: " + to_string(contract->GetCurrent()) + "/" + to_string(contract->GetAmount());
}
