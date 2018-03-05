#include "ContractHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Contract.h"
#include "InventoryHUDElement.h"


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
	resourceIcon = EHUD::WHUDContainer::Create(this, { 163, 84, 14, 14 }, contract->GetResourceIcon(), true);

	// Contract Issue Number
	contractIssueNumber = EHUD::TextWidget::Create(contractHUD, { 10, 16, 0, 0 }, "Contract Issue Number: " + to_string(contract->GetContractIndex()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract ID
	contractID = EHUD::TextWidget::Create(contractHUD, { 10, 32, 0, 0 }, "Contract ID: " + to_string(contract->GetContractID()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Difficulty
	difficulty = EHUD::TextWidget::Create(contractHUD, { 10, 48, 0, 0 }, "Difficulty Level: " + to_string(contract->GetDifficulty()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Amount to FulFill
	fulfill = EHUD::TextWidget::Create(contractHUD, { 10, 64, 0, 0 }, "Amount to FulFill: " + to_string(contract->GetCurrent()) + "/" + to_string(contract->GetAmount()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Reward
	reward = EHUD::TextWidget::Create(contractHUD, { 10, 80, 0, 0 }, "Reward: " + to_string(contract->GetPayment()) + " Gold", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Resource Name
	resource = EHUD::TextWidget::Create(contractHUD, { 10, 96, 0, 0 }, "Resource to Deliver:(   ) ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	resourceName = EHUD::TextWidget::Create(contractHUD, { 184, 96, 0, 0 }, contract->GetResource().GetName(), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Status (Complete/!Complete)
	contractStatus = EHUD::TextWidget::Create(contractHUD, { 10, 112, 0, 0 }, "Status (Active/!Active): " + to_string(contract->GetStatus()), "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	text = EHUD::TextWidget::Create(contractHUD, { 10, 128, 0, 0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
	
	StartChildWidgets();
}

void ContractHUDElement::Update()
{
	if (!active) {
		return;
	}


	// Contract Issue Number
	contractIssueNumber->text = "Contract Issue Number: " + to_string(contract->GetContractIndex());
	
	// Contract ID
	contractID->text = "Contract ID: " + to_string(contract->GetContractID());

	// Contract Difficulty
	difficulty->text = "Difficulty Level: " + to_string(contract->GetDifficulty());

	// Contract Amount to FulFill
	fulfill->text = "Amount to FulFill: " + to_string(contract->GetCurrent()) + "/" + to_string(contract->GetAmount());
	
	// Contract Reward
	reward->text = "Reward: " + to_string(contract->GetPayment()) + " Gold";

	// Contract Resource Name
	resource->text = "Resource to Deliver:(   ) ", "Game/Assets/Fonts/MavenPro-Regular.ttf";
	resourceName->text = contract->GetResource().GetName();

	// Contract Status (Complete/!Complete)
	contractStatus->text = "Status (Active/!Active): " + to_string(contract->GetStatus());

	// Contract time left
	text->text = "Time Left: " + to_string((int)contract->GetTime() / 1000) + "s";

	if (contract->GetStatus() == 0) {
		SetAllActive(false);
	}
}

void ContractHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}

}

void ContractHUDElement::SetContract(Contract * contractToSet)
{
	contract = contractToSet;
}

void ContractHUDElement::SetAllActive(bool state)
{
	active = state;
	contractHUD->SetActive(state);
	resourceIcon->SetActive(state);
}

Contract * ContractHUDElement::GetContract()
{
	return contract;
}

