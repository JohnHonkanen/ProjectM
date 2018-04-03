#include "PlayerEconManager.h"
#include "GameManager.h"
#include "core\GameEngine.h"


PlayerEconManager::PlayerEconManager()
{
}

PlayerEconManager::~PlayerEconManager()
{
}

PlayerEconomy PlayerEconManager::AddEconomy(EconName econName, string nameOfEconomy)
{
	PlayerEconomy playerEconomy = PlayerEconomy(resourceManager, this, econName, nameOfEconomy);
	Resources resource = resourceManager->FindResource(ResourceName::Gold); // Add gold as a resource to player economy

	switch (econName) {
	case EconName::Player_Econ:
		this->econList[PLAYER_ECON] = playerEconomy;
		break;

	default:
		cout << "No Economy found" << endl;
		break;
	}

	return playerEconomy;
}

PlayerEconomy* PlayerEconManager::FindPlayerEcon(EconName econName)
{
	switch (econName) {
	case EconName::Player_Econ:
		return &econList[PLAYER_ECON];

	default:
		return nullptr;
	}
}


void PlayerEconManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

PlayerEconManager * PlayerEconManager::Create(GameObject * gameObject)
{
	PlayerEconManager *p = new PlayerEconManager();
	gameObject->AddComponent(p);
	return p;
}

void PlayerEconManager::Copy(GameObject * copyObject)
{
	// Does nothing
}

void PlayerEconManager::OnLoad()
{
	
}

void PlayerEconManager::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {
		GetCurrentGoldAmountIn(GetHUBInventory());
		CheckIfPlayerInDebt();

		clock.ResetClock();
	}
}

void PlayerEconManager::Start()
{
	clock.SetDelay(1000);
	clock.StartClock();
	econList.resize(1);
	AddEconomy(EconName::Player_Econ, "playerEcon");
}

void PlayerEconManager::SetHUBInventory(v2::Inventory * HUBInventory)
{
	this->HUBInventory = HUBInventory;
}

Inventory* PlayerEconManager::GetHUBInventory()
{
	return this->HUBInventory;
}

int PlayerEconManager::GetCurrentGoldAmountIn(v2::Inventory * inventory)
{
	return GetHUBInventory()->Contains(ResourceName::Gold);
}

int PlayerEconManager::GetCurrentDebtAmount()
{
	return GameManager::gameManager->GetHub()->GetDebt();
}

void PlayerEconManager::AddInterestToDebt(int amount)
{
	return GameManager::gameManager->GetHub()->AdjustDebt(amount);
}

void PlayerEconManager::CheckIfPlayerInDebt()
{
	// Check if in debt first
	IsInDebt();

	if (IsInDebt() == true) {
		AdjustInterest(CalculateInterest());
		AddInterestToDebt(GetInterest());
	}

	if (IsInDebt() == false) {
		SetInterest(0);
	}
}

bool PlayerEconManager::IsInDebt()
{
	// If in debt
	if (GetCurrentGoldAmountIn(GetHUBInventory()) < 0 || GetCurrentDebtAmount() > 0) {
		return this->inDept = true;
	}

	if (GetCurrentDebtAmount() < 0) {
		return this->inDept = false;
	}
}

void PlayerEconManager::AdjustInterest(int amount)
{
	this->interestAmount = amount;
	cout << "Interest Amount: " + to_string(GetInterest()) << endl;
}

int PlayerEconManager::CalculateInterest()
{
	int calculatedInterest = GetCurrentDebtAmount() * defaultInterestPercentage;

	if (GetCurrentDebtAmount() >= 1000) {
		return calculatedInterest;
	}
	return 0;
}

int PlayerEconManager::GetInterest()
{
	return this->interestAmount;
}

void PlayerEconManager::SetInterest(int amount)
{
	this->interestAmount = amount;
}

vector<PlayerEconomy*> PlayerEconManager::GetList() const
{
	return vector<PlayerEconomy*>();
}
