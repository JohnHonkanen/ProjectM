#include "ContractHUDElement.h"
#include "hud\widgets\TextWidget.h"
#include "hud\widgets\HUDContainer.h"
#include "../Contract.h"
#include "InventoryHUDElement.h"
#include <sstream>
#include <iomanip>

ContractHUDElement * ContractHUDElement::Create(HUDElement * element, EHUD::HUDRect rect)
{
	ContractHUDElement *c = new ContractHUDElement();
	c->rect = rect;

	element->AttachWidget(c);

	return c;
}

void ContractHUDElement::Start()
{
	GenerateContractElements();
	StartChildWidgets();
}

void ContractHUDElement::Update()
{
	if (!active) {
		return;
	}

	// Contract ID
	contractID->text = "# " + to_string(contract.GetContractID());

	// Contract Amount to FulFill
	fulfill->text = to_string(contract.GetCurrent()) + "/" + to_string(contract.GetAmount());
	
	// Contract Resource Icon
	resourceIcon->ChangeImage(contract.GetResourceIcon());

	// Contract time left
	text->text = "Time Left: " + to_string((int)contract.GetTime() / 1000) + "s";

	GenerateKSuffix();
	if (contract.GetStatus() == 0) {
		SetAllActive(false);
	}
}

void ContractHUDElement::DrawWidget(unsigned int shader)
{
	if (!active) {
		return;
	}

}

void ContractHUDElement::SetContract(Contract contractToSet)
{
	this->contract = contractToSet;
	SetAllActive(true);
}

void ContractHUDElement::SetAllActive(bool state)
{
	active = state;
	contractHUD->SetActive(state);
	resourceIcon->SetActive(state);
}

Contract ContractHUDElement::GetContract()
{
	return contract;
}

void ContractHUDElement::GenerateContractElements()
{
	// Background
	contractHUD = EHUD::WHUDContainer::Create(this, { 0, 0, 280, 50 }, "Game/Assets/Textures/black.jpg", true);

	// Contract ID
	contractID = EHUD::TextWidget::Create(contractHUD, { 10, 12, 0, 0 }, "", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Resource Icon
	resourceIcon = EHUD::WHUDContainer::Create(this, { 10, 15, 32, 32 }, contract.GetResourceIcon(), true);

	// Contract Amount to FulFill
	fulfill = EHUD::TextWidget::Create(contractHUD, { 55, 35, 0, 0 }, "", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Contract Reward
	reward = EHUD::TextWidget::Create(contractHUD, { 110, 20, 0, 0 }, "", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));

	// Time left
	text = EHUD::TextWidget::Create(contractHUD, { 110, 40, 0, 0 }, " ", "Game/Assets/Fonts/MavenPro-Regular.ttf", 16, 1, vec3(1, 1, 1));
}

void ContractHUDElement::GenerateKSuffix()
{
	// Check if reward of current contract item price is greater or equal to 1000, then add "K" to it.
	if (contract.GetPayment() >= 1000) {
		float q = contract.GetPayment() / 1000.0f;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << q;
		reward->text = "Reward: " + ss.str() + "K Gold";
	}
}

