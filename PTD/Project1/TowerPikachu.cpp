#include "TowerPikachu.h"
#include <iostream>
void TowerPikachu::Movement(int CurrentPikachuFrame)
{
	if (CurrentPikachuFrame == 5)
	{
		this->PicTowerPikachu.setTextureRect(IntRect(39 * int(CurrentPikachuFrame)-4, 0, 37, 41));
	}
	else 
		this->PicTowerPikachu.setTextureRect(IntRect(39 * int(CurrentPikachuFrame), 0, 37, 41));
}

void TowerPikachu::Upgrade()
{
	this->damage = this->damage * 1.5;
	this->price = this->price * 2;
}

void TowerPikachu::SetNewPosition(Vector2f pos)
{
	this->Move.setPosition(pos.x - 12.f, pos.y - 40.f);
	this->UpgradeText.setPosition(pos.x - 60.f, pos.y - 40.f);
	this->Remove.setPosition(pos.x + 20.f, pos.y - 40.f);
	this->PicTowerPikachu.setPosition(pos.x, pos.y);
	this->shape.setPosition(pos);
}

void TowerPikachu::SetNewLevel(int price, int damage)
{
	this->damage = damage;
	this->price = price;
}
