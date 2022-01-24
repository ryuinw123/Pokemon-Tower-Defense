#ifndef LAND_H
#define LAND_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
using namespace sf;
using namespace std;
class Land
{
public:
	RectangleShape shape;
	bool CTower;
	Land(Vector2f (pos)) {
		this->shape.setSize(Vector2f(25.f, 25.f));
		this->shape.setOutlineColor(Color::Yellow); 
		this->shape.setOutlineThickness(2.f);
		this->shape.setFillColor(Color::Transparent);
		this->shape.setPosition(Vector2f(pos));
		this->shape.setOrigin(12.5f, 12.5f);
		this->CTower = false;
	}
	~Land() {}
};

#endif