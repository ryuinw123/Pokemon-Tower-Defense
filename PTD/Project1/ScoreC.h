#ifndef SCOREC_H
#define SCOREC_H
#include "sfml\graphics.hpp"
#include "sfml\window.hpp"
#include "sfml\system.hpp"
#include <sstream>
using namespace sf;
using namespace std;
class ScoreC
{
public:
	Text ShowName;
	Text ShowScore;
	String RealScore;
	int SCORE;
	ScoreC(String Name,int SCORE,Font *font)
	{
		stringstream Score;
		this->SCORE = SCORE;
		Score << SCORE;
		RealScore = Score.str();
		ShowName.setFont(*font);
		ShowName.setString(Name);
		ShowName.setCharacterSize(24);
		ShowName.setFillColor(Color::Red);
		ShowName.setStyle(Text::Bold);
		ShowName.setOrigin(ShowName.getGlobalBounds().width / 2.f, ShowName.getGlobalBounds().height / 2.f);
		ShowScore.setFont(*font);
		ShowScore.setString(RealScore);
		ShowScore.setCharacterSize(24);
		ShowScore.setFillColor(Color::Red);
		ShowScore.setStyle(Text::Bold);
		ShowScore.setOrigin(ShowScore.getGlobalBounds().width / 2.f, ShowScore.getGlobalBounds().height / 2.f);

	}
	~ScoreC(){}
};

#endif