#include "Frog.h"
#include "Global.h"
#include <iostream>

Frog::Frog(RenderWindow& window) : window(window), texRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE)
{
	Reset();
}

void Frog::Draw()
{
	sprite.setTextureRect(texRect);
	window.draw(sprite);
}
void Frog::Reset() 
{
	texture.loadFromFile("Resources/Images/Frog.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(texRect);
	sprite.setScale(Vector2f(4.f, 4.f));
	Vector2f startingPos = Vector2f(WINDOW_WIDTH / 2 - sprite.getGlobalBounds().width / 2, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
	sprite.setPosition(startingPos);
}
void Frog::MoveUp()
{
	texRect.left = 0;
	texRect.top = CELL_SIZE;
	sprite.move(Vector2f(0.f, -LANE_HEIGHT));
}
void Frog::MoveDown()
{
	texRect.left = 0;
	texRect.top = 3 * CELL_SIZE;
	sprite.move(Vector2f(0.f, LANE_HEIGHT));
	
}
void Frog::MoveLeft()
{
	texRect.left = 0;
	texRect.top = 2 * CELL_SIZE;
	sprite.move(Vector2f(-LANE_HEIGHT, 0));
	
}
void Frog::MoveRight()
{
	texRect.left = 0;
	texRect.top = 0;
	sprite.move(Vector2f(LANE_HEIGHT, 0));
	
}
void Frog::Move(int x, int y)
{
	sprite.move(Vector2f(x * LANE_HEIGHT, y * LANE_HEIGHT));
	if (sprite.getPosition().y < 88)
		sprite.setPosition(sprite.getPosition().x, TOP_BOUND);
	if (sprite.getPosition().y + sprite.getGlobalBounds().height > WINDOW_HEIGHT)
		sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
	if (sprite.getPosition().x < LEFT_BOUND)
		sprite.setPosition(LEFT_BOUND, sprite.getPosition().y);
	if (sprite.getPosition().x > RIGHT_BOUND)
		sprite.setPosition(WINDOW_WIDTH - LEFT_BOUND - sprite.getGlobalBounds().width, sprite.getPosition().y);
}