#include<iostream>
#include"sfml\graphics.hpp"
#include"sfml\window.hpp"
#include"sfml\system.hpp"
#include<math.h>
#include<vector>
#include<cstdlib>
#include "TowerPikachu.h"
#include "TowerCharizard.h"
#include "Bullet.h"
#include "EnemyPikachu.h"
#include "TowerVaporeon.h"
#include <sstream>
#include "Land.h"
#include "ScoreC.h"
#include <stdlib.h>
#include <time.h>
#include "SFML\Audio.hpp"
//length of vector: |v| = sqrt(v.x^2 + v.y^2)
//normalize vector: u = v / |v|

using namespace sf;
using namespace std;



int main()
{
	srand(time(NULL));
	Clock spawnClock,LevelClock,UpgradeTime,TextClock,ClockMouse,TextMoneyDelay;
	float spawnTime, shootPTime, shootVTime, shootCTime, CurrentPikachuFrame1 = 0, CurrentPikachuFrame2 = 0, Levelclock, TowerVaporeonMovement = 0, TowerCharizardMovement = 0, TowerPikachuMovement = 0,UpgradeDebounce,ClockText,MouseClock,CurrentPikachuattackframe = 0, TextMoney = 0;
	int HP = 0, Score = 0, Money = 10, Lifepoint = 10;
	SoundBuffer PikachuBuf, CharizardBuf, VaporeonBuf, BackGroundBuf;
	VaporeonBuf.loadFromFile("Sound/VaporeonCry.wav");
	CharizardBuf.loadFromFile("Sound/Charizard.wav");
	PikachuBuf.loadFromFile("Sound/pikachu.wav");
	BackGroundBuf.loadFromFile("Sound/PokemonFight.wav");
	Sound PikachuSound, CharizardSound, VaporeonSound, BackGroundSound;
	PikachuSound.setBuffer(PikachuBuf);
	CharizardSound.setBuffer(CharizardBuf);
	VaporeonSound.setBuffer(VaporeonBuf);
	BackGroundSound.setBuffer(BackGroundBuf);
	BackGroundSound.setVolume(25.f);
	RenderWindow window(VideoMode(800, 600), "Tower Defense", Style::Default);
	window.setFramerateLimit(60);
	//Font
	Font font,Seri;
	Seri.loadFromFile("Font/Serithai-Regular.ttf");
	font.loadFromFile("Font/SOV_BaanHook.ttf");
	Text ShowScore,ShowMoney,ScoreText,MoneyText,EnterName,NotEnouchMoney,ShowLifePoint,typeLife,SHOWNAME,SHOWSCORE;
	String name,realscore;
	typeLife.setFont(font);
	typeLife.setString("HP :");
	typeLife.setCharacterSize(24);
	typeLife.setFillColor(Color::Red);
	typeLife.setStyle(Text::Bold);
	typeLife.setPosition(650, 540.f);
	name = "SATOSHI";
	NotEnouchMoney.setFont(Seri);
	NotEnouchMoney.setCharacterSize(33);
	NotEnouchMoney.setFillColor(Color::Black);
	NotEnouchMoney.setPosition(Vector2f(396, 150));
	NotEnouchMoney.setString("Not Enough Money To Use This Function");
	NotEnouchMoney.setOrigin(NotEnouchMoney.getGlobalBounds().width / 2.f, NotEnouchMoney.getGlobalBounds().height / 2.f);
	SHOWNAME.setFont(Seri);
	SHOWNAME.setCharacterSize(33);
	SHOWNAME.setFillColor(Color::White);
	SHOWNAME.setPosition(Vector2f(350, 300));
	SHOWNAME.setString(name);
	SHOWNAME.setOrigin(SHOWNAME.getGlobalBounds().width / 2.f, SHOWNAME.getGlobalBounds().height / 2.f);
	SHOWSCORE.setFont(Seri);
	SHOWSCORE.setCharacterSize(33);
	SHOWSCORE.setFillColor(Color::White);
	SHOWSCORE.setPosition(Vector2f(450, 289));
	SHOWSCORE.setOrigin(SHOWSCORE.getGlobalBounds().width / 2.f, SHOWSCORE.getGlobalBounds().height / 2.f);
	EnterName.setFont(Seri);
	EnterName.setCharacterSize(33);
	EnterName.setFillColor(Color::Black);
	EnterName.setPosition(Vector2f(396, 247));
	EnterName.setString(name);
	EnterName.setOrigin(EnterName.getGlobalBounds().width / 2.f, EnterName.getGlobalBounds().height / 2.f);
	ShowLifePoint.setFont(font);
	ShowLifePoint.setCharacterSize(24);
	ShowLifePoint.setFillColor(Color::Red);
	ShowLifePoint.setStyle(Text::Bold);
	ShowLifePoint.setPosition(720, 540.f);
	ShowScore.setFont(font);
	ShowScore.setCharacterSize(24);
	ShowScore.setFillColor(Color::Yellow);
	ShowScore.setStyle(Text::Bold);
	ShowScore.setPosition(720.f, 41.f);
	ShowMoney.setFont(font);
	ShowMoney.setCharacterSize(24);
	ShowMoney.setFillColor(Color::Yellow);
	ShowMoney.setStyle(Text::Bold);
	ShowMoney.setPosition(720.f, 83.f);
	ScoreText.setFont(font);
	ScoreText.setCharacterSize(24);
	ScoreText.setFillColor(Color::Yellow);
	ScoreText.setStyle(Text::Bold);
	ScoreText.setPosition(600.f, 41.f);
	ScoreText.setString("SCORE:");
	MoneyText.setFont(font);
	MoneyText.setCharacterSize(24);
	MoneyText.setFillColor(Color::Yellow);
	MoneyText.setStyle(Text::Bold);
	MoneyText.setPosition(610.f, 83.f);
	MoneyText.setString("Money:");
	//Sprite
	Texture Pikachu, Background,Pikachu2,Pikachulightning,Vaporeon,Charizard,Background2,MainMenu,Blackscreen,ADDBUTTON,NEWGAMEBUTTON,ChooseProfileButton,NAMEBUTTON,OKBUTTON,CANCELBUTTON,ChallengeBUTTON,CHARIZARDSHOOT,VAPOREONSHOOT,EXITBUTTON,MENUBUTTON,GAMEOVERBUTTON,ShowScoreTexture,ProfilePic,WhiteBackground;
	ProfilePic.loadFromFile("Texture/Profile.PNG");
	WhiteBackground.loadFromFile("Texture/BackGroundWhite.jpg");
	ChallengeBUTTON.loadFromFile("Texture/CHOOSECHALENGELEVEL.PNG");
	ShowScoreTexture.loadFromFile("Texture/PLAYERSCORE.png");
	GAMEOVERBUTTON.loadFromFile("Texture/GAMEOVER.PNG");
	MENUBUTTON.loadFromFile("Texture/MENU.PNG");
	EXITBUTTON.loadFromFile("Texture/EXIT.PNG");
	CHARIZARDSHOOT.loadFromFile("Texture/SHOOT.png");
	VAPOREONSHOOT.loadFromFile("Texture/ATTACKEFFECT.png");
	NEWGAMEBUTTON.loadFromFile("Texture/ASS.PNG");
	NAMEBUTTON.loadFromFile("Texture/Name.PNG");
	OKBUTTON.loadFromFile("Texture/OK.PNG");
	CANCELBUTTON.loadFromFile("Texture/CANCEL.PNG");
	ADDBUTTON.loadFromFile("Texture/ADD.PNG");
	ChooseProfileButton.loadFromFile("Texture/ADS.PNG");
	Blackscreen.loadFromFile("Texture/BackGroundback.jpg");
	MainMenu.loadFromFile("Texture/title_screen_final_5.png");
	Charizard.loadFromFile("Texture/Charizard.png");
	Vaporeon.loadFromFile("Texture/Vaporeon.png");
	Pikachulightning.loadFromFile("Texture/SHOOT.png");
	Pikachu2.loadFromFile("Texture/pikachu2.png");
	Background.loadFromFile("Texture/Background.png");
	Pikachu.loadFromFile("Texture/pikachu.png");
	Background2.loadFromFile("Texture/Background2.png");
	Sprite BackgroundGame,BACK,NEWGAME,CHOOSE,NAME,OK,CANCEL,STATEPLAIN,STATEDESSERT,CHALLENGE,EXIT,RETURN,MeNu,PicGameOver,ShowScoreTexure,GOBACK,Profile,ProfileBack;
	Profile.setTexture(ProfilePic);
	Profile.setPosition(Vector2f(400.f, 250.f));
	Profile.setOrigin(Vector2f(Profile.getTextureRect().width / 2.f, Profile.getTextureRect().height / 2.f));
	ProfileBack.setTexture(ADDBUTTON);
	ProfileBack.setPosition(Vector2f(200.f, 520.f));
	ProfileBack.setOrigin(Vector2f(ProfileBack.getTextureRect().width / 2.f, ProfileBack.getTextureRect().height / 2.f));
	GOBACK.setTexture(ADDBUTTON);
	GOBACK.setPosition(Vector2f(100.f,550.f));
	GOBACK.setOrigin(Vector2f(GOBACK.getTextureRect().width / 2.f, GOBACK.getTextureRect().height / 2.f));
	ShowScoreTexure.setTexture(ShowScoreTexture);
	ShowScoreTexure.setPosition(Vector2f(400.f, 140.f));
	ShowScoreTexure.setOrigin(Vector2f(ShowScoreTexure.getTextureRect().width / 2.f, ShowScoreTexure.getTextureRect().height / 2.f));
	PicGameOver.setTexture(GAMEOVERBUTTON);
	PicGameOver.setPosition(Vector2f(390.f, 240.f));
	PicGameOver.setScale(0.5f, 0.5f);
	PicGameOver.setOrigin(Vector2f(PicGameOver.getTextureRect().width / 2.f, PicGameOver.getTextureRect().height / 2.f));
	MeNu.setTexture(MENUBUTTON);
	MeNu.setPosition(Vector2f(400.f, 365.f));
	MeNu.setOrigin(Vector2f(MeNu.getTextureRect().width / 2.f, MeNu.getTextureRect().height / 2.f));
	RETURN.setTexture(ADDBUTTON);
	RETURN.setPosition(Vector2f(450.f, 302.f));
	RETURN.setOrigin(Vector2f(RETURN.getTextureRect().width / 2.f, RETURN.getTextureRect().height / 2.f));
	EXIT.setTexture(EXITBUTTON);
	EXIT.setPosition(Vector2f(310.f,302.f));
	EXIT.setOrigin(Vector2f(EXIT.getTextureRect().width / 2.f, EXIT.getTextureRect().height / 2.f));
	CHALLENGE.setTexture(ChallengeBUTTON);
	CHALLENGE.setPosition(Vector2f(383,162));
	CHALLENGE.setOrigin(Vector2f(CHALLENGE.getTextureRect().width / 2.f, CHALLENGE.getTextureRect().height / 2.f));
	STATEPLAIN.setTexture(Background);
	STATEPLAIN.setPosition(Vector2f(200,400));
	STATEPLAIN.setScale(0.25f,0.25f);
	STATEPLAIN.setOrigin(Vector2f(STATEPLAIN.getTextureRect().width / 2.f, STATEPLAIN.getTextureRect().height / 2.f));
	STATEDESSERT.setTexture(Background2);
	STATEDESSERT.setPosition(Vector2f(600,400));
	STATEDESSERT.setScale(0.25f,0.25f);
	STATEDESSERT.setOrigin(Vector2f(STATEDESSERT.getTextureRect().width / 2.f, STATEDESSERT.getTextureRect().height / 2.f));
	NAME.setTexture(NAMEBUTTON);
	NAME.setPosition(Vector2f(101.f, 542.f));
	NAME.setOrigin(Vector2f(NAME.getTextureRect().width / 2.f, NAME.getTextureRect().height / 2.f));
	OK.setTexture(OKBUTTON);
	OK.setPosition(Vector2f(101.f, 542.f));
	OK.setOrigin(Vector2f(OK.getTextureRect().width / 2.f, OK.getTextureRect().height / 2.f));
	CANCEL.setTexture(CANCELBUTTON);
	CANCEL.setPosition(Vector2f(101.f, 542.f));
	CANCEL.setOrigin(Vector2f(CANCEL.getTextureRect().width / 2.f, CANCEL.getTextureRect().height / 2.f));
	BackgroundGame.setTexture(MainMenu);
	BACK.setTexture(ADDBUTTON);
	BACK.setPosition(Vector2f(200.f,450.f));
	BACK.setOrigin(Vector2f(BACK.getTextureRect().width / 2.f, BACK.getTextureRect().height / 2.f));
	NEWGAME.setTexture(NEWGAMEBUTTON);
	NEWGAME.setPosition(Vector2f(396.f, 295.f));
	NEWGAME.setOrigin(100.f, 30.f);
	CHOOSE.setTexture(ChooseProfileButton);
	CHOOSE.setPosition(Vector2f(397.f, 170.f));
	CHOOSE.setOrigin(Vector2f(CHOOSE.getTextureRect().width / 2.f, CHOOSE.getTextureRect().height / 2.f));
	RectangleShape Newgame;
	Newgame.setPosition(Vector2f(396.f, 295.f));
	Newgame.setSize(Vector2f(400.f, 300.f));
	Newgame.setFillColor(Color::Black);
	Newgame.setOutlineThickness(2);
	Newgame.setOutlineColor(Color(105, 105, 105, 255));
	Newgame.setOrigin(Vector2f(Newgame.getSize().x / 2.f, Newgame.getSize().y / 2.f));
	RectangleShape Pause;
	Pause.setPosition(Vector2f(440.f, 400.f));
	Pause.setSize(Vector2f(300.f, 100.f));
	Pause.setFillColor(Color(0, 0, 0, 100));
	Pause.setOutlineThickness(2);
	Pause.setOutlineColor(Color(105, 105, 105, 255));
	Pause.setOrigin(Vector2f(Newgame.getSize().x / 2.f, Newgame.getSize().y / 2.f));
	RectangleShape SetName;
	SetName.setSize(Vector2f(350.f,60.f));
	SetName.setOutlineThickness(2);
	SetName.setOutlineColor(Color::Yellow);
	SetName.setFillColor(Color(252, 123, 3, 255));
	SetName.setPosition(Vector2f(396, 260));
	SetName.setOrigin(Vector2f(SetName.getSize().x/2.f,SetName.getSize().y/2.f));
	RectangleShape ENDSCORE;
	ENDSCORE.setPosition(Vector2f(440.f, 350.f));
	ENDSCORE.setSize(Vector2f(300.f, 200.f));
	ENDSCORE.setFillColor(Color::Black);
	ENDSCORE.setOutlineThickness(2);
	ENDSCORE.setOutlineColor(Color(105, 105, 105, 255));
	ENDSCORE.setOrigin(Vector2f(Newgame.getSize().x / 2.f, Newgame.getSize().y / 2.f));
	//SwapScore
	ScoreC SWAP("SATOSHI", 0, &Seri);
	//Createbuy stand
	TowerVaporeon StandVaporeon(&Vaporeon, Vector2f(400.f, 107.f), &Seri);
	TowerCharizard StandCharizard(&Charizard, Vector2f(524.f,116.f), &Seri);
	TowerPikachu StandPikachu(&Pikachu, Vector2f(273.f,96.f),&Seri);
	
	//Create Mouse Stand
	TowerVaporeon TowerMouse1(&Vaporeon, Vector2f(Mouse::getPosition().x, Mouse::getPosition().y), &Seri);
	TowerCharizard TowerMouse2(&Charizard, Vector2f(Mouse::getPosition().x, Mouse::getPosition().y), &Seri);
	TowerPikachu TowerMouse3(&Pikachu, Vector2f(Mouse::getPosition().x, Mouse::getPosition().y),&Seri);
	
	//CREATE COPY TOWER
	TowerPikachu PC1(&Pikachu, Vector2f(900, 600), &Seri);
	TowerCharizard CC1(&Charizard, Vector2f(900, 600), &Seri);
	TowerVaporeon VC1(&Vaporeon, Vector2f(900, 600), &Seri);
	
	//Mouse
	CircleShape MouseW(5.f);
	MouseW.setFillColor(Color::Transparent);
	MouseW.setOrigin(5.f, 5.f);
	
	//Create Copy Tower Placement
	CircleShape C1(15.f,15.f);
	C1.setPosition(Vector2f(20.f, 20.f));
	C1.setFillColor(Color::Transparent);
	C1.setOrigin(C1.getRadius(), C1.getRadius());
	
	//Menu
	RectangleShape M1,M2,M3;
	M1.setSize(Vector2f(80.f, 43.f));
	M1.setFillColor(Color::Transparent);
	M1.setPosition(Vector2f(51.f, 562.f));
	M1.setOrigin(Vector2f(M1.getSize().x / 2.f, M1.getSize().y / 2.f));
	M1.setOutlineColor(Color::Black);
	M1.setOutlineThickness(2.f);
	M2.setSize(Vector2f(100.f, 43.f));
	M2.setFillColor(Color::Transparent);
	M2.setPosition(Vector2f(160.f, 562.f));
	M2.setOrigin(Vector2f(M1.getSize().x / 2.f, M1.getSize().y / 2.f));
	M2.setOutlineColor(Color::Black);
	M2.setOutlineThickness(2.f);
	M3.setSize(Vector2f(140.f, 43.f));
	M3.setFillColor(Color::Transparent);
	M3.setPosition(Vector2f(303.f, 562.f));
	M3.setOrigin(Vector2f(M1.getSize().x / 2.f, M1.getSize().y / 2.f));
	M3.setOutlineColor(Color::Black);
	M3.setOutlineThickness(2.f);
	
	//Tower setland
	std::vector <Land> Lands;
	//Bool Map
	bool Map1 = false, Map2 = false;

	//MouseClick
	bool Mouse = false;
	bool specificMouse = false;

	//CreateBool && Animation
	bool CREATEPIKACHU = false,CREATECHARIZARD = false, CREATEVAPOREON = false;
	bool MPIKACHU = false, MCHARIZARD = false, MVAPOREON = false;
	bool Title = true,Menu = false,STATESELECT = false, STATEP = false,SETSTATEP = false,SETSTATED = false,STATED = false;
	bool CREATENAME = false, GAMEPAUSE = false, TextMoneyNotEnough = false, ScoreScreen = false, GameEnd = false, SCORE1LOOP = false, FeedBack = false;

	
	//bullets
	bullet b1(&Pikachulightning,1);
	bullet b2(&VAPOREONSHOOT,2);
	bullet b3(&CHARIZARDSHOOT,3);
	std::vector<bullet> bullets;
	//Towers
	std::vector<TowerPikachu> TowerPikachus;
	std::vector<TowerCharizard> TowerCharizards;
	std::vector<TowerVaporeon> TowerVaporeons;

	//Score
	std::vector<ScoreC>Scores;
	Scores.push_back(ScoreC("SATOSHI", 0,&Seri));
	Scores.push_back(ScoreC("SATOSHI", 0, &Seri));
	Scores.push_back(ScoreC("SATOSHI", 0, &Seri));
	Scores.push_back(ScoreC("SATOSHI", 0, &Seri));
	Scores.push_back(ScoreC("SATOSHI", 0, &Seri));
	//enemy
	int spawncounter = 20;

	std::vector<EnemyPikachu> enemiesPikachu;

	//vectors
	Vector2f TowerCenter;
	Vector2f towerAimDir;
	Vector2f enemyPoswindow;
	Vector2f TowerAimDirNorm;
	Vector2f MouseClick;
	Vector2f MouseRelease;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
			{
				window.close();
			}break;
			//save mouse button released
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MouseRelease = Vector2f(Mouse::getPosition(window));
					Mouse = false;

				}
			}break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MouseClick = Vector2f(Mouse::getPosition(window));
					Mouse = true;
				}
				// we don't process other types of events
			default:
				break;
			}
		}

		//update
		MouseClock = ClockMouse.getElapsedTime().asSeconds();
		//Mouse pos
		MouseW.setPosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
		//TITLE
		if (Title == true)
		{
			BackgroundGame.setTexture(MainMenu);
		}
		if (MouseW.getGlobalBounds().intersects(M1.getGlobalBounds()) && Mouse && Title == true && MouseClock > 0.5f)
		{
			ClockMouse.restart().asSeconds();
			Title = false;
			BackgroundGame.setTexture(MainMenu);
			Menu = true;
		}
		if (Menu == true)
		{
			BackgroundGame.setTexture(Blackscreen);
		}
		if (Menu == true && Mouse && MouseW.getGlobalBounds().intersects(NEWGAME.getGlobalBounds()) && MouseClock > 0.2f)
		{
			ClockMouse.restart().asSeconds();
			CREATENAME = true;
		}
		if (Menu == true && Mouse && MouseW.getGlobalBounds().intersects(BACK.getGlobalBounds()) && MouseClock > 0.2f)
		{
			ClockMouse.restart().asSeconds();
			Title = true;
			Menu = false;
		}
		if (CREATENAME)
		{
			BackgroundGame.setTexture(Blackscreen);
			NAME.setPosition(Vector2f(396, 185));
			OK.setPosition(Vector2f(305, 360));
			CANCEL.setPosition(Vector2f(485, 358));
		}
		ClockText = TextClock.getElapsedTime().asSeconds();
		if (Keyboard::isKeyPressed(Keyboard::BackSpace) && CREATENAME && ClockText > 0.2f)
		{
			TextClock.restart().asSeconds();
			if (name.getSize()>=1)
				name.erase(name.getSize()-1, 1);
			EnterName.setString(name);
			EnterName.setOrigin(EnterName.getGlobalBounds().width / 2.f, EnterName.getGlobalBounds().height / 2.f);
		}
		if (event.type == sf::Event::TextEntered && CREATENAME && ClockText > 0.2f && event.text.unicode != 8)
		{
			TextClock.restart().asSeconds();
			name += event.text.unicode;
			EnterName.setString(name);
			EnterName.setOrigin(EnterName.getGlobalBounds().width / 2.f, EnterName.getGlobalBounds().height / 2.f);
		}
		if (CREATENAME && OK.getGlobalBounds().intersects(MouseW.getGlobalBounds()) && Mouse && MouseClock > 0.2f)
		{
			ClockMouse.restart().asSeconds();
			CREATENAME = false;
			STATESELECT = true;
			Menu = false;
		}
		if (CREATENAME && CANCEL.getGlobalBounds().intersects(MouseW.getGlobalBounds()) && Mouse && MouseClock > 0.2f)
		{
			ClockMouse.restart().asSeconds();
			CREATENAME = false;
			Menu = true;
			name = "SATOSHI";
			EnterName.setString(name);
			EnterName.setOrigin(EnterName.getGlobalBounds().width / 2.f, EnterName.getGlobalBounds().height / 2.f);
		}
		if (STATESELECT)
		{
			BackgroundGame.setTexture(Blackscreen);
		}
		if (STATESELECT && Mouse && MouseW.getGlobalBounds().intersects(STATEPLAIN.getGlobalBounds()) && MouseClock > 1.f)
		{
			ClockMouse.restart().asSeconds();
			BackgroundGame.setTexture(Background);
			STATEP = true;
			SETSTATEP = true;
			STATESELECT = false;
		}
		if (STATESELECT && Mouse && MouseW.getGlobalBounds().intersects(STATEDESSERT.getGlobalBounds()) && MouseClock > 0.5f)
		{
			ClockMouse.restart().asSeconds();
			BackgroundGame.setTexture(Background2);
			STATED = true;
			SETSTATED = true;
			STATESELECT = false;
		}
		if (SETSTATEP == true)
		{
			SETSTATEP = false;
			HP = 0;
			Score = 0;
			Money = 10;
			Lifepoint = 10;
			Levelclock = 0;
			Lands.clear();
			Lands.push_back(Land(Vector2f(97.f, 260.f)));
			Lands.push_back(Land(Vector2f(210.f, 260.f)));
			Lands.push_back(Land(Vector2f(307.f, 260.f)));
			Lands.push_back(Land(Vector2f(403.f, 260.f)));
			Lands.push_back(Land(Vector2f(497.f, 260.f)));
			Lands.push_back(Land(Vector2f(690.f, 260.f)));
			Lands.push_back(Land(Vector2f(100.f, 404.f)));
			Lands.push_back(Land(Vector2f(210.f, 404.f)));
			Lands.push_back(Land(Vector2f(306.f, 404.f)));
			Lands.push_back(Land(Vector2f(403.f, 404.f)));
			Lands.push_back(Land(Vector2f(498.f, 404.f)));
			Lands.push_back(Land(Vector2f(594.f, 404.f)));
			Lands.push_back(Land(Vector2f(690.f, 404.f)));
			Lands.push_back(Land(Vector2f(594.f, 260.f)));
			StandPikachu.PicTowerPikachu.setPosition(Vector2f(273.f, 96.f));
			StandCharizard.PicTowerCharizard.setPosition(Vector2f(524.f, 80.f));
			StandVaporeon.Vaporeon.setPosition(Vector2f(380.f, 90.f));
			StandVaporeon.StandMoney.setPosition(Vector2f(365.f, 50.f));
			StandCharizard.StandMoney.setPosition(Vector2f(489.f, 40.f));
			StandPikachu.StandMoney.setPosition(Vector2f(263.f, 60.f));
			TowerPikachus.clear();
			TowerCharizards.clear();
			TowerVaporeons.clear();
			enemiesPikachu.clear();
			BackGroundSound.play();
		}
		if (SETSTATED == true)
		{
			SETSTATED = false;
			HP = 0;
			Score = 0;
			Money = 10;
			Lifepoint = 10;
			Levelclock = 0;
			Lands.clear();
			Lands.push_back(Land(Vector2f(305.f, 276.f)));
			Lands.push_back(Land(Vector2f(98.f, 436.f)));
			Lands.push_back(Land(Vector2f(224.f, 404.f)));
			Lands.push_back(Land(Vector2f(480.f, 276.f)));
			Lands.push_back(Land(Vector2f(530.f, 403.f)));
			Lands.push_back(Land(Vector2f(690.f, 147.f)));
			Lands.push_back(Land(Vector2f(738.f, 274.f)));
			Lands.push_back(Land(Vector2f(147.f, 561.f)));
			StandPikachu.PicTowerPikachu.setPosition(Vector2f(145.f, 96.f));
			StandCharizard.PicTowerCharizard.setPosition(Vector2f(300.f, 80.f));
			StandVaporeon.Vaporeon.setPosition(Vector2f(430.f, 90.f));
			StandVaporeon.StandMoney.setPosition(Vector2f(415.f,50.f));
			StandCharizard.StandMoney.setPosition(Vector2f(265.f, 40.f));
			StandPikachu.StandMoney.setPosition(Vector2f(135.f, 60.f));
			TowerPikachus.clear();
			TowerCharizards.clear();
			TowerVaporeons.clear();
			enemiesPikachu.clear();
			BackGroundSound.play();
		}
		if (GAMEPAUSE)
		{
			BackGroundSound.pause();
			if (MouseW.getGlobalBounds().intersects(RETURN.getGlobalBounds()) && Mouse)
			{
				GAMEPAUSE = false;
				BackGroundSound.play();
			}
			if (MouseW.getGlobalBounds().intersects(EXIT.getGlobalBounds()) && Mouse)
			{
				GAMEPAUSE = false;
				Title = true;
				STATED = false;
				STATEP = false;
				BackGroundSound.stop();
			}
		}
		if (Title && MouseW.getGlobalBounds().intersects(M2.getGlobalBounds()) && Mouse && MouseClock > 0.5f )
		{
			ClockMouse.restart().asSeconds();
			Title = false;
			ScoreScreen = true;
		}
		if (ScoreScreen)
		{
			BackgroundGame.setTexture(Blackscreen);
			if (Scores.size() > 5)
			{
				int max;
				for (size_t i = 0; i < Scores.size() - 1; i++)
				{
					max = i;
					for (int j = i + 1; j < Scores.size(); j++)
						if (Scores[j].SCORE > Scores[max].SCORE)
							max = j;
					SWAP = Scores[i];
					Scores[i] = Scores[max];
					Scores[max] = SWAP;
				}
				Scores.erase(Scores.end()-1);
			}
			Scores[0].ShowName.setPosition(Vector2f(300.f, 300.f));
			Scores[1].ShowName.setPosition(Vector2f(300.f, 350.f));
			Scores[2].ShowName.setPosition(Vector2f(300.f, 400.f));
			Scores[3].ShowName.setPosition(Vector2f(300.f, 450.f));
			Scores[4].ShowName.setPosition(Vector2f(300.f, 500.f));
			Scores[0].ShowScore.setPosition(Vector2f(500.f,300.f));
			Scores[1].ShowScore.setPosition(Vector2f(500.f,350.f));
			Scores[2].ShowScore.setPosition(Vector2f(500.f,400.f));
			Scores[3].ShowScore.setPosition(Vector2f(500.f,450.f));
			Scores[4].ShowScore.setPosition(Vector2f(500.f,500.f));
			if (Mouse && MouseW.getGlobalBounds().intersects(GOBACK.getGlobalBounds()) && MouseClock > 1.f)
			{
				ClockMouse.restart().asSeconds();
				ScoreScreen = false;
				Title = true;
			}

		}
		if (GameEnd)
		{
			if (SCORE1LOOP)
			{
				SHOWSCORE.setString(realscore);
				BackGroundSound.stop();
				SCORE1LOOP = false;
			}
			STATEP = false;
			STATED = false;
			if (Mouse && MouseW.getGlobalBounds().intersects(MeNu.getGlobalBounds()))
			{
				GameEnd = false;
				Title = true;
				Scores.push_back(ScoreC(name, Score, &Seri));
			}
		}
		if (Title == true && MouseW.getGlobalBounds().intersects(M3.getGlobalBounds()) && Mouse && MouseClock > 0.5f)
		{
			FeedBack = true;
			Title = false;
		}
		if (FeedBack)
		{
			BackgroundGame.setTexture(WhiteBackground);
			if (Mouse && MouseW.getGlobalBounds().intersects(ProfileBack.getGlobalBounds()) && MouseClock > 0.5f)
			{
				ClockMouse.restart().asSeconds();
				FeedBack = false;
				Title = true;
			}
		}


		/*cout << "Mouse pos.x" << Mouse::getPosition(window).x << "\n";
		cout << "Mouse pos.y" << Mouse::getPosition(window).y << "\n";*/

		//SystemUpdate
		//Clock level
		if (STATEP || STATED)
			if (GAMEPAUSE == false)
			{
				Levelclock = LevelClock.getElapsedTime().asSeconds();
				if (Levelclock > 1)
				{
					Levelclock = 0;
					LevelClock.restart().asSeconds();
					HP = HP + 2;
				}

				//PAUSE game
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					GAMEPAUSE = true;
				}

				//enemiesPikachu
				spawnTime = spawnClock.getElapsedTime().asSeconds();
				if (spawncounter < 20)
					spawncounter++;
				if (spawncounter >= 20 && enemiesPikachu.size() < 20 && spawnTime > 1.5f && STATEP)
				{
					spawnTime = spawnClock.restart().asMilliseconds();
					EnemyPikachu p1(&Pikachu2, window.getSize().y / 2.f, HP);
					enemiesPikachu.push_back(EnemyPikachu(p1));
					//cout << HP << "\n";
					spawncounter = 0;
				}
				if (spawncounter >= 20 && enemiesPikachu.size() < 20 && spawnTime > 1.2f && STATED)
				{
					spawnTime = spawnClock.restart().asMilliseconds();
					EnemyPikachu p1(&Pikachu2, window.getSize().y / 2.f, HP);
					p1.PicTowerPikachu.setPosition(Vector2f(0.f, 500.f));
					enemiesPikachu.push_back(EnemyPikachu(p1));
					spawncounter = 0;
				}

				//enemiesPikachu moving && Health animation STATE P กับ D ต่างกัน
				if (STATEP)
				{
					for (size_t i = 0; i < enemiesPikachu.size(); i++)
					{
						enemiesPikachu[i].HPAnimation(Vector2f(enemiesPikachu[i].PicTowerPikachu.getPosition().x, enemiesPikachu[i].PicTowerPikachu.getPosition().y));
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x < 1000)
							enemiesPikachu[i].PicTowerPikachu.move(1.f, 0.f);
					}
				}
				if (STATED)
				{
					for (size_t i = 0; i < enemiesPikachu.size(); i++)
					{
						enemiesPikachu[i].HPAnimation(Vector2f(enemiesPikachu[i].PicTowerPikachu.getPosition().x, enemiesPikachu[i].PicTowerPikachu.getPosition().y));
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x < 155)
							enemiesPikachu[i].PicTowerPikachu.move(1.f, 0.f);
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x >140 && enemiesPikachu[i].PicTowerPikachu.getPosition().x <160 && enemiesPikachu[i].PicTowerPikachu.getPosition().y > 345.f)
							enemiesPikachu[i].PicTowerPikachu.move(0.f, -1.f);
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x < 640 && enemiesPikachu[i].PicTowerPikachu.getPosition().y < 350.f)
							enemiesPikachu[i].PicTowerPikachu.move(1.f, 0.f);
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x > 630 && enemiesPikachu[i].PicTowerPikachu.getPosition().x < 660 && enemiesPikachu[i].PicTowerPikachu.getPosition().y > 200.f)
							enemiesPikachu[i].PicTowerPikachu.move(0.f, -1.f);
						if (enemiesPikachu[i].PicTowerPikachu.getPosition().x < 1000 && enemiesPikachu[i].PicTowerPikachu.getPosition().y >190.f && enemiesPikachu[i].PicTowerPikachu.getPosition().y < 210.f)
							enemiesPikachu[i].PicTowerPikachu.move(1.f, 0.f);
					}
				}

				//PikachuTower Detection && shooting
				for (size_t k = 0; k < enemiesPikachu.size(); k++)
				{
					for (size_t i = 0; i < TowerPikachus.size(); i++)
					{
						if (TowerPikachus[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{
							enemyPoswindow = Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition());
							TowerCenter = Vector2f(TowerPikachus[i].shape.getPosition());
							towerAimDir = enemyPoswindow - TowerCenter;
							TowerAimDirNorm = towerAimDir / sqrt(pow(towerAimDir.x, 2) + pow(towerAimDir.y, 2));
						}


						shootPTime = TowerPikachus[i].clock.getElapsedTime().asSeconds();

						if (shootPTime > 2.f && TowerPikachus[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{

							shootPTime = TowerPikachus[i].clock.restart().asMilliseconds();
							b1.shape.setPosition(Vector2f(TowerPikachus[i].shape.getPosition()));
							b1.currVelocity = TowerAimDirNorm * b1.maxSpeed;
							TowerPikachus[i].bullets.push_back(bullet(b1));
						}
					}
				}

				for (size_t j = 0; j < TowerPikachus.size(); j++)
					for (size_t i = 0; i < TowerPikachus[j].bullets.size(); i++)
					{
						{
							TowerPikachus[j].bullets[i].shape.move(TowerPikachus[j].bullets[i].currVelocity);

							//Out of bounds
							if (TowerPikachus[j].bullets[i].shape.getPosition().x < 0 || TowerPikachus[j].bullets[i].shape.getPosition().x > window.getSize().x || TowerPikachus[j].bullets[i].shape.getPosition().y < 0 || TowerPikachus[j].bullets[i].shape.getPosition().y > window.getSize().y)
							{
								TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);

							}
							else
							{
								//Pikachu Tower shoot Enemy collision
								for (size_t k = 0; k < enemiesPikachu.size(); k++)
								{
									if (TowerPikachus[j].bullets[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
									{
										int v1;
										v1 = rand() % 10;
										if (v1 == 1)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *1.2);
											break;
										}
										if (v1 == 2)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 1.4;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *1.4);
											break;
										}
										if (v1 == 3)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 1.6;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *1.6);
											break;
										}
										if (v1 == 4)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 0.9;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *0.9);
											break;
										}
										if (v1 == 5)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage *0.7;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *0.7);
											break;
										}
										if (v1 == 6)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage *0.5;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *0.5);
											break;
										}
										if (v1 == 7)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 1.1;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *1.1);
											break;
										}
										if (v1 == 8)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage *1.2);
											break;
										}
										if (v1 == 9)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerPikachus[j].damage * 10;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage,&Seri);
											TowerPikachus[j].bullets.erase(TowerPikachus[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerPikachus[j].damage*10);
											break;
										}
									}
								}
							}
						}
					}
				//VAPOREON Detection && shooting
				for (size_t k = 0; k < enemiesPikachu.size(); k++)
				{
					for (size_t i = 0; i < TowerVaporeons.size(); i++)
					{
						if (TowerVaporeons[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{
							enemyPoswindow = Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition());
							TowerCenter = Vector2f(TowerVaporeons[i].shape.getPosition());
							towerAimDir = enemyPoswindow - TowerCenter;
							TowerAimDirNorm = towerAimDir / sqrt(pow(towerAimDir.x, 2) + pow(towerAimDir.y, 2));
						}


						shootVTime = TowerVaporeons[i].clock.getElapsedTime().asSeconds();

						if (shootVTime > 1.5f && TowerVaporeons[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{

							shootVTime = TowerVaporeons[i].clock.restart().asMilliseconds();
							b2.shape.setPosition(Vector2f(TowerVaporeons[i].shape.getPosition()));
							b2.currVelocity = TowerAimDirNorm * b2.maxSpeed;
							TowerVaporeons[i].bullets.push_back(bullet(b2));
						}
					}
				}

				for (size_t j = 0; j < TowerVaporeons.size(); j++)
					for (size_t i = 0; i < TowerVaporeons[j].bullets.size(); i++)
					{
						{
							TowerVaporeons[j].bullets[i].shape.move(TowerVaporeons[j].bullets[i].currVelocity);

							//Out of bounds
							if (TowerVaporeons[j].bullets[i].shape.getPosition().x < 0 || TowerVaporeons[j].bullets[i].shape.getPosition().x > window.getSize().x || TowerVaporeons[j].bullets[i].shape.getPosition().y < 0 || TowerVaporeons[j].bullets[i].shape.getPosition().y > window.getSize().y)
							{
								TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);

							}
							else
							{
								//Vaporeon Tower shoot Enemy collision
								for (size_t k = 0; k < enemiesPikachu.size(); k++)
								{
									if (TowerVaporeons[j].bullets[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
									{
										//ใส่โค้ดลดเลือด
										int v1;
										v1 = rand() % 10;
										if (v1 == 1)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 1.2);
											break;
										}
										if (v1 == 2)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 1.4;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 1.4);
											break;
										}
										if (v1 == 3)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 1.6;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 1.6);
											break;
										}
										if (v1 == 4)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 0.9;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 0.9);
											break;
										}
										if (v1 == 5)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 0.7;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 0.7);
											break;
										}
										if (v1 == 6)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 0.5;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 0.5);
											break;
										}
										if (v1 == 7)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 1.1;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 1.1);
											break;
										}
										if (v1 == 8)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 1.2);
											break;
										}
										if (v1 == 9)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerVaporeons[j].damage * 10;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerVaporeons[j].bullets.erase(TowerVaporeons[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerVaporeons[j].damage * 10);
											break;
										}
									}
								}
							}
						}
					}
				//CHARIZARD Detection && shooting
				for (size_t k = 0; k < enemiesPikachu.size(); k++)
				{
					for (size_t i = 0; i < TowerCharizards.size(); i++)
					{
						if (TowerCharizards[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{
							enemyPoswindow = Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition());
							TowerCenter = Vector2f(TowerCharizards[i].shape.getPosition());
							towerAimDir = enemyPoswindow - TowerCenter;
							TowerAimDirNorm = towerAimDir / sqrt(pow(towerAimDir.x, 2) + pow(towerAimDir.y, 2));
						}


						shootCTime = TowerCharizards[i].clock.getElapsedTime().asSeconds();

						if (shootCTime > 0.5f && TowerCharizards[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
						{

							shootCTime = TowerCharizards[i].clock.restart().asMilliseconds();
							b3.shape.setPosition(Vector2f(TowerCharizards[i].shape.getPosition()));
							b3.currVelocity = TowerAimDirNorm * b3.maxSpeed;
							TowerCharizards[i].bullets.push_back(bullet(b3));
						}
					}
				}

				for (size_t j = 0; j < TowerCharizards.size(); j++)
					for (size_t i = 0; i < TowerCharizards[j].bullets.size(); i++)
					{
						{
							TowerCharizards[j].bullets[i].shape.move(TowerCharizards[j].bullets[i].currVelocity);

							//Out of bounds
							if (TowerCharizards[j].bullets[i].shape.getPosition().x < 0 || TowerCharizards[j].bullets[i].shape.getPosition().x > window.getSize().x || TowerCharizards[j].bullets[i].shape.getPosition().y < 0 || TowerCharizards[j].bullets[i].shape.getPosition().y > window.getSize().y)
							{
								TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);

							}
							else
							{
								//Charizard Tower shoot Enemy collision
								for (size_t k = 0; k < enemiesPikachu.size(); k++)
								{
									if (TowerCharizards[j].bullets[i].shape.getGlobalBounds().intersects(enemiesPikachu[k].PicTowerPikachu.getGlobalBounds()))
									{
										//ใส่โค้ดลดเลือด
										int v1;
										v1 = rand() % 10;
										if (v1 == 1)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 1.2);
											break;
										}
										if (v1 == 2)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 1.4;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 1.4);
											break;
										}
										if (v1 == 3)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 1.6;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 1.6);
											break;
										}
										if (v1 == 4)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 0.9;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 0.9);
											break;
										}
										if (v1 == 5)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 0.7;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 0.7);
											break;
										}
										if (v1 == 6)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 0.5;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 0.5);
											break;
										}
										if (v1 == 7)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 1.1;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 1.1);
											break;
										}
										if (v1 == 8)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 1.2;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 1.2);
											break;
										}
										if (v1 == 9)
										{
											stringstream Sdamage;
											string Damage;
											Sdamage << TowerCharizards[j].damage * 10;
											Damage = Sdamage.str();
											enemiesPikachu[k].ShootText(Vector2f(enemiesPikachu[k].PicTowerPikachu.getPosition()), Damage, &Seri);
											TowerCharizards[j].bullets.erase(TowerCharizards[j].bullets.begin() + i);
											enemiesPikachu[k].hp = enemiesPikachu[k].hp - (TowerCharizards[j].damage * 10);
											break;
										}
									}
								}
							}
						}
					}
				for (size_t i = 0; i < enemiesPikachu.size(); i++)
				{
					if (enemiesPikachu[i].hp <= 0)
					{
						Score = Score + enemiesPikachu[i].maxhp;
						Money = Money + enemiesPikachu[i].maxhp;
						enemiesPikachu.erase(enemiesPikachu.begin() + i);
					}
				}

				//TowerCreation
				//Create land 
				for (size_t i = 0; i < Lands.size(); i++) 
				{
					TowerPikachu p1(&Pikachu, Vector2f(Lands[i].shape.getPosition()), &Seri);
					TowerCharizard c1(&Charizard, Vector2f(Lands[i].shape.getPosition()), &Seri);
					TowerVaporeon v1(&Vaporeon, Vector2f(Lands[i].shape.getPosition()), &Seri);
					if (Lands[i].CTower == false && CREATEPIKACHU == true && MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false)
					{
						if (Money - p1.price >= 0 )
						{
							PikachuSound.play();
							Money = Money - p1.price;
							CREATEPIKACHU == false;
							Lands[i].CTower = true;
							TowerPikachus.push_back(p1);
						}
						if (Money - p1.price < 0)
							TextMoneyNotEnough = true;
					}
					if (Lands[i].CTower == false && CREATECHARIZARD == true && MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false)
					{
						if (Money - c1.price >= 0)
						{
							CharizardSound.play();
							Money = Money - c1.price;
							CREATECHARIZARD == false;
							Lands[i].CTower = true;
							TowerCharizards.push_back(c1);
						}
						if (Money - c1.price < 0)
							TextMoneyNotEnough = true;
					}
					if (Lands[i].CTower == false && CREATEVAPOREON == true && MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false)
					{
						if (Money - v1.price >= 0)
						{
							VaporeonSound.play();
							TowerVaporeon v1(&Vaporeon, Vector2f(Lands[i].shape.getPosition()), &Seri);
							Money = Money - v1.price;
							CREATEVAPOREON == false;
							Lands[i].CTower = true;
							TowerVaporeons.push_back(v1);
						}
						if (Money - v1.price < 0)
							TextMoneyNotEnough = true;
					}
				}
				TextMoney = TextMoneyDelay.getElapsedTime().asSeconds();
				if (TextMoneyNotEnough)
				{
					TextMoney = TextMoneyDelay.restart().asSeconds();
					TextMoneyNotEnough = false;
				}
				//delete Pikachu
				for (size_t i = 0; i < enemiesPikachu.size(); i++)
				{
					if (enemiesPikachu[i].PicTowerPikachu.getPosition().x > window.getSize().x)
					{
						enemiesPikachu.erase(enemiesPikachu.begin() + i);
						Lifepoint--;
					}
				}

				//Move PTower
				for (size_t i = 0; i < TowerPikachus.size(); i++)
					if (MouseW.getGlobalBounds().intersects(TowerPikachus[i].Move.getGlobalBounds()) && Mouse == true && TowerPikachus[i].clickTower == true)
					{
						MPIKACHU = true;
						PC1.SetNewLevel(TowerPikachus[i].price, TowerPikachus[i].damage);
						PC1.SetNewPosition(Vector2f(TowerPikachus[i].PicTowerPikachu.getPosition()));
						TowerPikachus.erase(TowerPikachus.begin() + i);
						break;
					}
				for (size_t i = 0; i < Lands.size(); i++)
					for (size_t k = 0; k < Lands.size(); k++)
						if (MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false && Lands[i].CTower == false && MPIKACHU == true && PC1.PicTowerPikachu.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							Lands[k].CTower = false;
							MPIKACHU == false;
							PC1.SetNewPosition(Vector2f(Lands[i].shape.getPosition().x + 5.f, Lands[i].shape.getPosition().y - 5.f));
							TowerPikachus.push_back(PC1);
							Lands[i].CTower = true;
							PC1.SetNewPosition(Vector2f(C1.getPosition()));
							break;
						}
				for (size_t i = 0; i < Lands.size(); i++)
					if (MPIKACHU == false && !PC1.PicTowerPikachu.getGlobalBounds().intersects(C1.getGlobalBounds()))
					{
						TowerPikachus.push_back(PC1);
						PC1.SetNewPosition(Vector2f(C1.getPosition()));
						break;
					}
				//Move CTower
				for (size_t i = 0; i < TowerCharizards.size(); i++)
					if (MouseW.getGlobalBounds().intersects(TowerCharizards[i].Move.getGlobalBounds()) && Mouse == true && TowerCharizards[i].clickTower == true)
					{
						MCHARIZARD = true;
						CC1.SetNewLevel(TowerCharizards[i].price, TowerCharizards[i].damage);
						CC1.SetNewPosition(Vector2f(TowerCharizards[i].PicTowerCharizard.getPosition()));
						TowerCharizards.erase(TowerCharizards.begin() + i);
						break;
					}
				for (size_t i = 0; i < Lands.size(); i++)
					for (size_t k = 0; k < Lands.size(); k++)
						if (MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false && Lands[i].CTower == false && MCHARIZARD == true && CC1.PicTowerCharizard.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							Lands[k].CTower = false;
							MCHARIZARD == false;
							CC1.SetNewPosition(Vector2f(Lands[i].shape.getPosition().x + 15.f, Lands[i].shape.getPosition().y - 28.f));
							TowerCharizards.push_back(CC1);
							Lands[i].CTower = true;
							PC1.SetNewPosition(Vector2f(C1.getPosition()));
							break;
						}
				for (size_t i = 0; i < Lands.size(); i++)
					if (MCHARIZARD == false && !CC1.PicTowerCharizard.getGlobalBounds().intersects(C1.getGlobalBounds()))
					{
						TowerCharizards.push_back(CC1);
						CC1.SetNewPosition(Vector2f(C1.getPosition()));
						break;
					}
				//Move VTower
				for (size_t i = 0; i < TowerVaporeons.size(); i++)
					if (MouseW.getGlobalBounds().intersects(TowerVaporeons[i].Move.getGlobalBounds()) && Mouse == true && TowerVaporeons[i].clickTower == true)
					{
						MVAPOREON = true;
						VC1.SetNewLevel(TowerVaporeons[i].price, TowerVaporeons[i].damage);
						VC1.SetNewPosition(Vector2f(TowerVaporeons[i].Vaporeon.getPosition()));
						TowerVaporeons.erase(TowerVaporeons.begin() + i);
						break;
					}
				for (size_t i = 0; i < Lands.size(); i++)
					for (size_t k = 0; k < Lands.size(); k++)
						if (MouseW.getGlobalBounds().intersects(Lands[i].shape.getGlobalBounds()) && Mouse == false && Lands[i].CTower == false && MVAPOREON == true && VC1.Vaporeon.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							Lands[k].CTower = false;
							MVAPOREON == false;
							VC1.SetNewPosition(Vector2f(Lands[i].shape.getPosition().x - 10.f, Lands[i].shape.getPosition().y - 20.f));
							TowerVaporeons.push_back(VC1);
							Lands[i].CTower = true;
							VC1.SetNewPosition(Vector2f(C1.getPosition()));
							break;
						}
				for (size_t i = 0; i < Lands.size(); i++)
					if (MVAPOREON == false && !VC1.Vaporeon.getGlobalBounds().intersects(C1.getGlobalBounds()))
					{
						TowerVaporeons.push_back(VC1);
						VC1.SetNewPosition(Vector2f(C1.getPosition()));
						break;
					}
				//Upgrade destroy tower
				UpgradeDebounce = UpgradeTime.getElapsedTime().asSeconds();
				for (size_t i = 0; i < TowerPikachus.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerPikachus[i].UpgradeText.getGlobalBounds()) && Mouse == true && UpgradeDebounce > 1.f && TowerPikachus[i].clickTower == true)
					{
						if (Money - TowerPikachus[i].price >= 0)
						{
							Money = Money - TowerPikachus[i].price;
							UpgradeTime.restart().asSeconds();
							TowerPikachus[i].Upgrade();
						}
						if (Money - TowerPikachus[i].price < 0)
						{
							TextMoneyNotEnough = true;
						}
					}
					for (size_t k = 0; k < Lands.size(); k++)
					{
						if (MouseW.getGlobalBounds().intersects(TowerPikachus[i].Remove.getGlobalBounds()) && Mouse == true && TowerPikachus[i].clickTower == true && TowerPikachus[i].PicTowerPikachu.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							TowerPikachus.erase(TowerPikachus.begin() + i);
							Lands[k].CTower = false;
							break;
						}
					}
				}
				for (size_t i = 0; i < TowerVaporeons.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerVaporeons[i].UpgradeText.getGlobalBounds()) && Mouse == true && UpgradeDebounce > 1.f && TowerVaporeons[i].clickTower == true)
					{
						if (Money - TowerVaporeons[i].price >= 0)
						{
							Money = Money - TowerVaporeons[i].price;
							UpgradeTime.restart().asSeconds();
							TowerVaporeons[i].Upgrade();
						}
						if (Money - TowerVaporeons[i].price < 0)
						{
							TextMoneyNotEnough = true;
						}
					}
					for (size_t k = 0; k < Lands.size(); k++)
					{
						if (MouseW.getGlobalBounds().intersects(TowerVaporeons[i].Remove.getGlobalBounds()) && Mouse == true && TowerVaporeons[i].clickTower == true && TowerVaporeons[i].Vaporeon.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							TowerVaporeons.erase(TowerVaporeons.begin() + i);
							Lands[k].CTower = false;
							break;
						}
					}
				}
				for (size_t i = 0; i < TowerCharizards.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerCharizards[i].UpgradeText.getGlobalBounds()) && Mouse == true && UpgradeDebounce > 1.f && TowerCharizards[i].clickTower == true)
					{
						if (Money - TowerCharizards[i].price >= 0)
						{
							Money = Money - TowerCharizards[i].price;
							UpgradeTime.restart().asSeconds();
							TowerCharizards[i].Upgrade();
						}
						if (Money - TowerCharizards[i].price < 0)
						{
							TextMoneyNotEnough = true;
						}
					}
					for (size_t k = 0; k < Lands.size(); k++)
					{
						if (MouseW.getGlobalBounds().intersects(TowerCharizards[i].Remove.getGlobalBounds()) && Mouse == true && TowerCharizards[i].clickTower == true && TowerCharizards[i].PicTowerCharizard.getGlobalBounds().intersects(Lands[k].shape.getGlobalBounds()))
						{
							TowerCharizards.erase(TowerCharizards.begin() + i);
							Lands[k].CTower = false;
							break;
						}
					}
				}
				//GameEnd
				if (Lifepoint == 0)
				{
					GameEnd = true;
					SCORE1LOOP = true;
				}
				//Click Tower
				for (size_t i = 0; i < TowerPikachus.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerPikachus[i].PicTowerPikachu.getGlobalBounds()) && Mouse == true)
					{
						TowerPikachus[i].clickTower = true;
					}
					if (!MouseW.getGlobalBounds().intersects(TowerPikachus[i].PicTowerPikachu.getGlobalBounds()) && Mouse == true)
					{
						TowerPikachus[i].clickTower = false;
					}
				}
				for (size_t i = 0; i < TowerCharizards.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerCharizards[i].PicTowerCharizard.getGlobalBounds()) && Mouse == true)
					{
						TowerCharizards[i].clickTower = true;
					}
					if (!MouseW.getGlobalBounds().intersects(TowerCharizards[i].PicTowerCharizard.getGlobalBounds()) && Mouse == true)
					{
						TowerCharizards[i].clickTower = false;
					}
				}
				for (size_t i = 0; i < TowerVaporeons.size(); i++)
				{
					if (MouseW.getGlobalBounds().intersects(TowerVaporeons[i].Vaporeon.getGlobalBounds()) && Mouse == true)
					{
						TowerVaporeons[i].clickTower = true;
					}
					if (!MouseW.getGlobalBounds().intersects(TowerVaporeons[i].Vaporeon.getGlobalBounds()) && Mouse == true)
					{
						TowerVaporeons[i].clickTower = false;
					}
				}


				//StandVaporeon Movement
				TowerVaporeonMovement += 0.05;
				if (TowerVaporeonMovement > 7)
					TowerVaporeonMovement = 0;
				StandVaporeon.Movement(TowerVaporeonMovement);
				//StandCharizardMovement
				TowerCharizardMovement += 0.07;
				if (TowerCharizardMovement > 6)
					TowerCharizardMovement = 0;
				StandCharizard.Movement(TowerCharizardMovement);
				//PikachuTower Movement

				CurrentPikachuFrame1 += 0.05;
				if (CurrentPikachuFrame1 > 7)
					CurrentPikachuFrame1 = 0;
				StandPikachu.Movement(CurrentPikachuFrame1);

				for (size_t i = 0; i < TowerPikachus.size(); i++)
				{
					TowerPikachus[i].Movement(CurrentPikachuFrame1);
				}
				for (size_t i = 0; i < TowerCharizards.size(); i++)
				{
					TowerCharizards[i].Movement(TowerCharizardMovement);
				}

				for (size_t i = 0; i < TowerVaporeons.size(); i++)
				{
					TowerVaporeons[i].Movement(TowerVaporeonMovement);
				}

				//EnimesPikachuMovement

				CurrentPikachuFrame2 += 0.1;
				if (CurrentPikachuFrame2 > 6)
					CurrentPikachuFrame2 = 0;

				for (size_t i = 0; i < enemiesPikachu.size(); i++)
				{
					enemiesPikachu[i].Movement(CurrentPikachuFrame2);
				}
				//BOOL Creation Tower
				if (MouseW.getGlobalBounds().intersects(StandPikachu.PicTowerPikachu.getGlobalBounds()) && Mouse == true &&!CREATECHARIZARD &&!CREATEVAPOREON)
				{
					CREATEPIKACHU = true;
				}
				if (MouseW.getGlobalBounds().intersects(StandCharizard.PicTowerCharizard.getGlobalBounds()) && Mouse == true && !CREATEPIKACHU && !CREATEVAPOREON)
				{
					CREATECHARIZARD = true;
				}
				if (MouseW.getGlobalBounds().intersects(StandVaporeon.Vaporeon.getGlobalBounds()) && Mouse == true &&!CREATECHARIZARD &&!CREATEPIKACHU)
				{
					CREATEVAPOREON = true;
				}
				//bool false Create TOwer ต้องอยู่ล่าง
				if (MouseW.getGlobalBounds().intersects(BackgroundGame.getGlobalBounds()) && Mouse == false)
				{
					MCHARIZARD = false;
					MVAPOREON = false;
					MPIKACHU = false;
					CREATECHARIZARD = false;
					CREATEPIKACHU = false;
					CREATEVAPOREON = false;
				}
				//Mouse Button Sprite
				TowerMouse1.Vaporeon.setPosition(Vector2f(Mouse::getPosition().x - 580.f, Mouse::getPosition().y - 280.f));
				TowerMouse2.PicTowerCharizard.setPosition(Vector2f(Mouse::getPosition().x - 560.f, Mouse::getPosition().y - 280.f));
				TowerMouse3.PicTowerPikachu.setPosition(Vector2f(Mouse::getPosition().x - 560.f, Mouse::getPosition().y - 280.f));

				//UPDATETEXT Score & Money ต้องอยู่ล่างสุด
				stringstream SCORE, MONEY, HealthPoint;
				string REALSCORE1, REALMONEY1, REALSCORE, REALMONEY, RealLife;
				SCORE << Score;
				MONEY << Money;
				HealthPoint << Lifepoint;
				RealLife = HealthPoint.str();
				REALSCORE = SCORE.str();
				REALMONEY = MONEY.str();
				realscore = REALSCORE;
				ShowScore.setString(REALSCORE);
				ShowMoney.setString(REALMONEY);
				ShowLifePoint.setString(RealLife);
				//UPDATE ENEMIRSPIKACHU TEXT TIME
				for (size_t i = 0; i < enemiesPikachu.size(); i++)
					enemiesPikachu[i].UpdateClock(Vector2f(enemiesPikachu[i].PicTowerPikachu.getPosition()));
			}
		//Draw
		window.clear();
		window.draw(BackgroundGame);
		if (Menu)
		{
			window.draw(BACK);
			window.draw(NEWGAME);
			window.draw(CHOOSE);
		}
		if (FeedBack)
		{
			window.draw(Profile);
			window.draw(ProfileBack);
		}
		if (ScoreScreen)
		{
			window.draw(ShowScoreTexure);
			for (size_t i = 0; i < Scores.size(); i++)
			{
				window.draw(Scores[i].ShowScore);
				window.draw(Scores[i].ShowName);
				window.draw(GOBACK);
			}
		}
		if (CREATENAME)
		{
			window.draw(Newgame);
			window.draw(OK);
			window.draw(NAME);
			window.draw(CANCEL);
			window.draw(SetName);
			window.draw(EnterName);
		}
		if (STATESELECT)
		{
			window.draw(CHALLENGE);
			window.draw(STATEPLAIN);
			window.draw(STATEDESSERT);
		}
		if (GameEnd)
		{
			window.draw(ENDSCORE);
			window.draw(SHOWNAME);
			window.draw(SHOWSCORE);
			window.draw(MeNu);
			window.draw(PicGameOver);
		}
		if (STATEP || STATED)
		{    //ศัตรู

			for (size_t i = 0; i < enemiesPikachu.size(); i++)
			{
				window.draw(enemiesPikachu[i].shape);
				window.draw(enemiesPikachu[i].PicTowerPikachu);
			}
			for (size_t i = 0; i < Lands.size(); i++)
				if (!Lands[i].CTower && GAMEPAUSE == false)
				{
					window.draw(Lands[i].shape);
				}
			//กระสุน Pikachu
			for (size_t i = 0; i < TowerPikachus.size(); i++)
			{
				for (size_t k = 0; k < TowerPikachus[i].bullets.size(); k++)
				{
					window.draw(TowerPikachus[i].bullets[k].shape);
				}
			}
			for (size_t i = 0; i < TowerVaporeons.size(); i++)
			{
				for (size_t k = 0; k < TowerVaporeons[i].bullets.size(); k++)
				{
					window.draw(TowerVaporeons[i].bullets[k].shape);
				}
			}
			for (size_t i = 0; i < TowerCharizards.size(); i++)
			{
				for (size_t k = 0; k < TowerCharizards[i].bullets.size(); k++)
				{
					window.draw(TowerCharizards[i].bullets[k].shape);
				}
			}
			if (STATEP || STATED)
			{
				window.draw(StandCharizard.PicTowerCharizard);
				window.draw(StandVaporeon.Vaporeon);
				window.draw(StandPikachu.PicTowerPikachu);
			}
			if (MouseW.getGlobalBounds().intersects(StandVaporeon.Vaporeon.getGlobalBounds()))
				window.draw(StandVaporeon.StandMoney);
			if (MouseW.getGlobalBounds().intersects(StandCharizard.PicTowerCharizard.getGlobalBounds()))
				window.draw(StandCharizard.StandMoney);
			if (MouseW.getGlobalBounds().intersects(StandPikachu.PicTowerPikachu.getGlobalBounds()))
				window.draw(StandPikachu.StandMoney);
			for (size_t i = 0; i < bullets.size(); i++)
			{
				window.draw(bullets[i].shape);
			}
			//Create Tower
			for (size_t i = 0; i < TowerPikachus.size(); i++)
			{
				window.draw(TowerPikachus[i].PicTowerPikachu);
				if (TowerPikachus[i].clickTower == true)
				{
					window.draw(TowerPikachus[i].shape);
					window.draw(TowerPikachus[i].UpgradeText);
					window.draw(TowerPikachus[i].Remove);
					window.draw(TowerPikachus[i].Move);
				}
			}
			for (size_t i = 0; i < TowerCharizards.size(); i++)
			{
				window.draw(TowerCharizards[i].PicTowerCharizard);
				if (TowerCharizards[i].clickTower == true)
				{
					window.draw(TowerCharizards[i].shape);
					window.draw(TowerCharizards[i].UpgradeText);
					window.draw(TowerCharizards[i].Remove);
					window.draw(TowerCharizards[i].Move);
				}
			}
			for (size_t i = 0; i < TowerVaporeons.size(); i++)
			{
				window.draw(TowerVaporeons[i].Vaporeon);
				if (TowerVaporeons[i].clickTower == true)
				{
					window.draw(TowerVaporeons[i].shape);
					window.draw(TowerVaporeons[i].UpgradeText);
					window.draw(TowerVaporeons[i].Remove);
					window.draw(TowerVaporeons[i].Move);
				}
			}
			if (CREATECHARIZARD == true||MCHARIZARD)
				window.draw(TowerMouse2.PicTowerCharizard);
			if (CREATEVAPOREON == true || MVAPOREON)
				window.draw(TowerMouse1.Vaporeon);
			if (CREATEPIKACHU == true || MPIKACHU == true)
				window.draw(TowerMouse3.PicTowerPikachu);
			window.draw(ScoreText);
			window.draw(MoneyText);
			window.draw(ShowScore);
			window.draw(ShowMoney);
			window.draw(ShowLifePoint);
			window.draw(typeLife);
			for (size_t i = 0; i < enemiesPikachu.size(); i++)
				if (enemiesPikachu[i].damageclock < 1.f)
					window.draw(enemiesPikachu[i].ShowDamage);
			if (TextMoney < 3.f)
			{
				window.draw(NotEnouchMoney);
			}
			if (GAMEPAUSE)
			{
				window.draw(Pause);
				window.draw(EXIT);
				window.draw(RETURN);
			}
		}
		window.display();
	}

	return 0;
}