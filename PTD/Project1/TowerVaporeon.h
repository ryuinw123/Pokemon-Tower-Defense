#ifndef TOWERVAPOREON
#define TOWERVAPOREON
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
#include "Bullet.h"
using namespace sf;
using namespace std;
class TowerVaporeon
{
public:
	Clock clock;
	Sprite Vaporeon;
	Texture* texture;
	CircleShape shape;
	int price;
	Text UpgradeText, Remove, Move;
	Text StandMoney;
	vector<bullet> bullets;
	int damage;
	bool clickTower;
	TowerVaporeon(Texture* texture, Vector2f pos, Font* font)
	{
		this->StandMoney.setFont(*font);
		this->StandMoney.setCharacterSize(12);
		this->StandMoney.setString("1000");
		this->StandMoney.setFillColor(Color::Yellow);
		this->StandMoney.setStyle(Text::Bold);
		//this->texture = texture;
		this->clickTower = false;
		//this->texture = texture;
		this->Move.setFont(*font);
		this->Move.setCharacterSize(10);
		this->Move.setString("Move");
		this->Move.setFillColor(Color::Yellow);
		this->Move.setStyle(Text::Bold);
		this->Move.setPosition(pos.x - 12.f, pos.y - 60.f);
		this->UpgradeText.setFont(*font);
		this->UpgradeText.setCharacterSize(10);
		this->UpgradeText.setString("Upgrade");
		this->UpgradeText.setFillColor(Color::Yellow);
		this->UpgradeText.setStyle(Text::Bold);
		this->UpgradeText.setPosition(pos.x - 60.f, pos.y - 60.f);
		this->Remove.setFont(*font);
		this->Remove.setCharacterSize(10);
		this->Remove.setString("Remove");
		this->Remove.setFillColor(Color::Black);
		this->Remove.setStyle(Text::Bold);
		this->Remove.setPosition(pos.x + 20.f, pos.y - 60.f);
		this->damage = 10;
		this->price = 1000;
		this->Vaporeon.setTexture(*texture);
		this->Vaporeon.setTextureRect(IntRect(311, 0, 72, 61));
		this->Vaporeon.setPosition(pos.x-10.f,pos.y -20.f);
		this->Vaporeon.setOrigin(72.f / 2.f, 61.f / 2.f);
		this->shape.setRadius(100.f);
		this->shape.setFillColor(Color(65, 105, 225, 100));
		this->shape.setPosition(pos);
		this->shape.setOrigin(shape.getRadius(), shape.getRadius());
	}
	~TowerVaporeon() {};
	void Movement(int CurrentVaporeonFrame);
	void Upgrade();
	void SetNewPosition(Vector2f pos);
	void SetNewLevel(int price, int damage);

};
#endif
