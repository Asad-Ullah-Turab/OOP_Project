#include "Frog.h"
#include "Global.h"
#include <iostream>

Frog::Frog()
{
	Reset();
}
void Frog::Draw(RenderWindow &window)
{
	window.draw(sprite);
}
void Frog::Reset() 
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(4.f, 4.f));
	Vector2f startingPos = Vector2f(WINDOW_WIDTH / 2 - sprite.getGlobalBounds().width / 2, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
	sprite.setPosition(startingPos);
}
void Frog::MoveUp()
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.move(Vector2f(0.f, -LANE_HEIGHT));
	if (sprite.getPosition().y < 88)
		sprite.setPosition(sprite.getPosition().x, TOP_BOUND);
		
}
void Frog::MoveDown()
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, 3 * CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.move(Vector2f(0.f, LANE_HEIGHT));
	if (sprite.getPosition().y + sprite.getGlobalBounds().height > WINDOW_HEIGHT)
		sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
}
void Frog::MoveLeft()
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, 2 * CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.move(Vector2f(-LANE_HEIGHT, 0));
	if (sprite.getPosition().x < LEFT_BOUND)
		sprite.setPosition(LEFT_BOUND, sprite.getPosition().y);
}
void Frog::MoveRight()
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, 0, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.move(Vector2f(LANE_HEIGHT, 0));
	if (sprite.getPosition().x > RIGHT_BOUND)
		sprite.setPosition(WINDOW_WIDTH - LEFT_BOUND - sprite.getGlobalBounds().width, sprite.getPosition().y);
}