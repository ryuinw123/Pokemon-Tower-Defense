#include "TowerVaporeon.h"

void TowerVaporeon::Movement(int CurrentVaporeonFrame)
{
	if (CurrentVaporeonFrame == 0)
	    this->Vaporeon.setTextureRect(IntRect(311, 0, 72, 61));
	if (CurrentVaporeonFrame == 1)
		this->Vaporeon.setTextureRect(IntRect(383, 0, 69, 61));
	if (CurrentVaporeonFrame == 2)
		this->Vaporeon.setTextureRect(IntRect(452, 0, 65, 61));
	if (CurrentVaporeonFrame == 3)
		this->Vaporeon.setTextureRect(IntRect(516, 0, 54, 61));
	if (CurrentVaporeonFrame == 4)
		this->Vaporeon.setTextureRect(IntRect(570, 0, 56, 61));
	if (CurrentVaporeonFrame == 5)
		this->Vaporeon.setTextureRect(IntRect(626, 0, 54, 61));
	if (CurrentVaporeonFrame ==6)
		this->Vaporeon.setTextureRect(IntRect(680, 0, 60, 61));
}

void TowerVaporeon::Upgrade()
{
	this->damage = this->damage * 1.8;
	this->price = this->price * 2;
}

void TowerVaporeon::SetNewPosition(Vector2f pos)
{
	this->Vaporeon.setPosition(pos.x, pos.y);
	this->Move.setPosition(Vaporeon.getPosition().x +8.f, Vaporeon.getPosition().y - 40.f);
	this->UpgradeText.setPosition(Vaporeon.getPosition().x - 40.f, Vaporeon.getPosition().y - 40.f);
	this->Remove.setPosition(Vaporeon.getPosition().x + 40.f, Vaporeon.getPosition().y - 40.f);
	this->shape.setPosition(Vaporeon.getPosition().x+20.f,Vaporeon.getPosition().y+20.f);
}

void TowerVaporeon::SetNewLevel(int price, int damage)
{
	this->damage = damage;
	this->price = price;
}
