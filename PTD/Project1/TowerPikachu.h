#ifndef TOWERPIKACHU_H
#define TOWERPIKACHU_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
#include "Bullet.h"
using namespace sf;
using namespace std;
class TowerPikachu
{
public:
	Clock clock;
	Sprite PicTowerPikachu;
	Texture* texture;
	Text UpgradeText , Remove,Move;
	CircleShape shape;
	vector<bullet> bullets;
	Text StandMoney;
	int damage;
	int price;
	bool clickTower;
	TowerPikachu(Texture* texture, Vector2f pos, Font *font)
	{
		this->StandMoney.setFont(*font);
		this->StandMoney.setCharacterSize(12);
		this->StandMoney.setString("5");
		this->StandMoney.setFillColor(Color::Yellow);
		this->StandMoney.setStyle(Text::Bold);
		this->StandMoney.setPosition(pos.x-140.f, pos.y - 40.f);
		this->clickTower = false;
		//this->texture = texture;
		this->Move.setFont(*font);
		this->Move.setCharacterSize(10);
		this->Move.setString("Move");
		this->Move.setFillColor(Color::Yellow);
		this->Move.setStyle(Text::Bold);
		this->Move.setPosition(pos.x-12.f, pos.y - 40.f);
		this->UpgradeText.setFont(*font);
		this->UpgradeText.setCharacterSize(10);
		this->UpgradeText.setString("Upgrade");
		this->UpgradeText.setFillColor(Color::Yellow);
		this->UpgradeText.setStyle(Text::Bold);
		this->UpgradeText.setPosition(pos.x -60.f,pos.y -40.f);
		this->Remove.setFont(*font);
		this->Remove.setCharacterSize(10);
		this->Remove.setString("Remove");
		this->Remove.setFillColor(Color::Black);
		this->Remove.setStyle(Text::Bold);
		this->Remove.setPosition(pos.x + 20.f, pos.y - 40.f);
		this->price = 5;
		this->PicTowerPikachu.setTexture(*texture);
		this->PicTowerPikachu.setTextureRect(IntRect(39 * 0, 0, 37, 41));
		this->PicTowerPikachu.setPosition(pos.x+5.f,pos.y-5.f);
		this->PicTowerPikachu.setOrigin(38.f / 2.f, 41.f / 2.f);
		this->damage = 3;
		this->shape.setRadius(100.f);
		this->shape.setFillColor(Color(65, 105, 225, 100));
		this->shape.setPosition(pos);
		this->shape.setOrigin(shape.getRadius(), shape.getRadius());
	}
	~TowerPikachu() {}
	void Movement(int CurrentPikachuFrame);
	void Upgrade();
	void SetNewPosition(Vector2f pos);
	void SetNewLevel(int price,int damage);
};
#endif

