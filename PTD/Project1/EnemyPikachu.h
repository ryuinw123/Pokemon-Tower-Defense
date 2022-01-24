#ifndef ENEMYPIKACHU_H
#define ENEMYPIKACHU_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"

using namespace sf;
using namespace std;
class EnemyPikachu
{
public:
	Clock clock,DamageClock;
	Sprite PicTowerPikachu;
	Texture* texture;
	RectangleShape shape;
	Font font;
	Text ShowDamage;
	float damageclock;
	float hp;
	float maxhp;
	EnemyPikachu(Texture* texture, float posy,int Healthclock)
	{
		this->maxhp = Healthclock / 10;
		this->hp = this->maxhp;
		this->PicTowerPikachu.setTexture(*texture);
		this->PicTowerPikachu.setTextureRect(IntRect(46 * 0 + 236, 41, 46, 38));
		this->PicTowerPikachu.setPosition(0, posy + 20.f);
		this->PicTowerPikachu.setOrigin(46.f / 2.f, 38.f / 2.f); 
		this->shape.setSize(Vector2f(35.f, 10.f));
		this->shape.setOutlineColor(Color::Black);
		this->shape.setOutlineThickness(2.f);
		this->shape.setFillColor(Color::Green);
		this->shape.setPosition(0, 0);
		this->shape.setOrigin(12.5f, 12.5f);
		damageclock = 3;
	}
	~EnemyPikachu() {};
	void Movement(int CurrentPikachuFrame);
	void HPAnimation(Vector2f pos);
	void ShootText(Vector2f pos, string damage,Font *font);
	void UpdateClock(Vector2f pos);
};
#endif
