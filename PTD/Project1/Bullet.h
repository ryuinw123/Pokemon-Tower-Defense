#ifndef BULLET_H
#define BULLET_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
using namespace sf;
using namespace std;
class bullet
{
public:
	Clock clock,ShootClock;
	Sprite shape;
	Vector2f currVelocity;
	float maxSpeed,TextAnimation;

	bullet(Texture *texture,int BULLET)
		: currVelocity(0.f, 0.f), maxSpeed(7.f)
	{
		this->shape.setTexture(*texture);
		if (BULLET == 1) {
			this->shape.setTextureRect(IntRect(64 * 0 + 312, 24, 64, 48));
			this->shape.setOrigin(64.f / 2.f, 48.f / 2.f);
		}
		if (BULLET == 2)
		{
			this->shape.setTextureRect(IntRect(590, 1898, 40, 40));
			this->shape.setOrigin(40.f / 2.f, 40.f / 2.f);
		}
		if (BULLET == 3)
		{
			this->shape.setTextureRect(IntRect(172, 86, 128, 78));
			this->shape.setOrigin(128.f / 2.f, 78.f / 2.f);
		}
	}
	~bullet() {};
};
#endif
