#include "TowerCharizard.h"

void TowerCharizard::Movement(int CurrentVaporeonFrame)
{
	if (CurrentVaporeonFrame == 0)
		this->PicTowerCharizard.setTextureRect(IntRect(0, 500, 105, 85));
	if (CurrentVaporeonFrame == 1)
		this->PicTowerCharizard.setTextureRect(IntRect(107, 500, 95, 85));
	if (CurrentVaporeonFrame == 2)
		this->PicTowerCharizard.setTextureRect(IntRect(202, 500, 92, 85));
	if (CurrentVaporeonFrame == 3)
		this->PicTowerCharizard.setTextureRect(IntRect(295, 500, 90, 85));
	if (CurrentVaporeonFrame == 4)
		this->PicTowerCharizard.setTextureRect(IntRect(385, 500, 105, 85));
	if (CurrentVaporeonFrame == 5)
		this->PicTowerCharizard.setTextureRect(IntRect(492,500, 118, 85));
	if (CurrentVaporeonFrame == 6)
		this->PicTowerCharizard.setTextureRect(IntRect(608, 500, 124, 85));
}

void TowerCharizard::Upgrade()
{
	this->damage = this->damage * 2;
	this->price = this->price * 2;
}

void TowerCharizard::SetNewPosition(Vector2f pos)
{
	this->StandMoney.setPosition(pos.x - 12.f, pos.y - 50.f);
	this->PicTowerCharizard.setPosition(pos.x, pos.y);
	this->Move.setPosition(pos.x - 12.f, pos.y - 50.f);
	this->UpgradeText.setPosition(pos.x - 60.f, pos.y - 50.f);
	this->Remove.setPosition(pos.x + 20.f, pos.y - 50.f);
	this->shape.setPosition(PicTowerCharizard.getPosition().x,PicTowerCharizard.getPosition().y+30.f);
}

void TowerCharizard::SetNewLevel(int price, int damage)
{
	this->damage = damage;
	this->price = price;
}
