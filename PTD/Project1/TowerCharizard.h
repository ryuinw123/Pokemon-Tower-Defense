#ifndef TOWERCHARIZARD_H
#define TOWERCHARIZARD_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
#include "Bullet.h"
using namespace sf;
using namespace std;
class TowerCharizard
{
public:
	Clock clock;
	Sprite PicTowerCharizard;
	Texture* texture;
	CircleShape shape;
	vector<bullet> bullets;
	Text UpgradeText, Remove, Move;
	Text StandMoney;
	int damage;
	int price;
	bool clickTower;
	TowerCharizard(Texture* texture, Vector2f pos, Font* font)
	{
		this->StandMoney.setFont(*font);
		this->StandMoney.setCharacterSize(12);
		this->StandMoney.setString("2000");
		this->StandMoney.setFillColor(Color::Yellow);
		this->StandMoney.setStyle(Text::Bold);
		this->StandMoney.setPosition(pos.x -260.f,pos.y - 80.f);
		//this->texture = texture;
		this->clickTower = false;
		//this->texture = texture;
		this->Move.setFont(*font);
		this->Move.setCharacterSize(10);
		this->Move.setString("Move");
		this->Move.setFillColor(Color::Yellow);
		this->Move.setStyle(Text::Bold);
		this->Move.setPosition(pos.x - 12.f, pos.y - 80.f);
		this->UpgradeText.setFont(*font);
		this->UpgradeText.setCharacterSize(10);
		this->UpgradeText.setString("Upgrade");
		this->UpgradeText.setFillColor(Color::Yellow);
		this->UpgradeText.setStyle(Text::Bold);
		this->UpgradeText.setPosition(pos.x - 60.f, pos.y - 80.f);
		this->Remove.setFont(*font);
		this->Remove.setCharacterSize(10);
		this->Remove.setString("Remove");
		this->Remove.setFillColor(Color::Black);
		this->Remove.setStyle(Text::Bold);
		this->Remove.setPosition(pos.x + 20.f, pos.y - 80.f);
		this->price = 2000;
		this->PicTowerCharizard.setTexture(*texture);
		this->PicTowerCharizard.setTextureRect(IntRect(0, 500, 105, 85));
		this->PicTowerCharizard.setPosition(pos.x+10.f,pos.y -30.f);
		this->PicTowerCharizard.setOrigin(105.f / 2.f, 85.f / 2.f);
		this->damage = 15;
		this->shape.setRadius(100.f);
		this->shape.setFillColor(Color(65, 105, 225, 100));
		this->shape.setPosition(pos);
		this->shape.setOrigin(shape.getRadius(), shape.getRadius());
	}
	~TowerCharizard() {};
	void Movement(int CurrentCharizardFrame);
	void Upgrade();
	void SetNewPosition(Vector2f pos);
	void SetNewLevel(int price, int damage);
};
#endif