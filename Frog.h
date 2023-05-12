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
	RenderWindow& window;
public:
	IntRect texRect;
	Frog(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Move(int x, int y);
	void Draw();
	void Reset();
};

