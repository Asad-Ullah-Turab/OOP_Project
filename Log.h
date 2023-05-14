#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
class Log
{
private:
	int type;
	int direction;
	int startingPos;
	Sprite sprite;
	Texture* texture;
	IntRect texRect;
	int laneNo;
	float speed = 5;
public:
	Log(int type, int laneNo);
	Sprite getSprite() { return sprite; }
	void SetTexRect();
	void Initialize();
	void SetLane();
	void Move();
};

