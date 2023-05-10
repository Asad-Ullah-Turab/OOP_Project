#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
class Frog
{
private:
	Sprite sprite;
	Texture texture;
public:
	Frog();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Draw(RenderWindow &window);
	void Reset();
};

