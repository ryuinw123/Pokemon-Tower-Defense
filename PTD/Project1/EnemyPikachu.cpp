#include "EnemyPikachu.h"
#include "iostream"

void EnemyPikachu::Movement(int CurrentPikachuFrame)
{
	this->PicTowerPikachu.setTextureRect(IntRect(46 * int(CurrentPikachuFrame) + 236, 41, 45, 38));
}

void EnemyPikachu::HPAnimation(Vector2f pos)
{
	if (this->maxhp > 0) 
	{
		this->shape.setSize(Vector2f(this->hp / this->maxhp *35, 10));
		if (this->hp / this->maxhp < 0.20)
		{
			this->shape.setFillColor(Color::Red);
		}
		else
			this->shape.setFillColor(Color::Green);
	}
	this->shape.setOutlineColor(Color::Black);
	this->shape.setOutlineThickness(1.f);
	this->shape.setPosition(pos.x,pos.y-25.f);
	this->shape.setOrigin(12.5f, 12.5f);
}

void EnemyPikachu::ShootText(Vector2f pos, string damage,Font *font)
{
	this->DamageClock.restart().asSeconds();
	ShowDamage.setFont(*font);
	ShowDamage.setString(damage);
	ShowDamage.setCharacterSize(10);
	ShowDamage.setFillColor(Color::Red);
	ShowDamage.setPosition(Vector2f(350, 300));
}

void EnemyPikachu::UpdateClock(Vector2f pos)
{
	this->damageclock = this->DamageClock.getElapsedTime().asSeconds();
	this->ShowDamage.setPosition(pos.x,pos.y-30.f);
}
