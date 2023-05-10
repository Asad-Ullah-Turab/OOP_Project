#include "Frog.h"
#include "Global.h"

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
}
void Frog::MoveDown()
{
	texture.loadFromFile("Resources/Images/Frog.png", IntRect(0, 3 * CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sprite.setTexture(texture);
	sprite.move(Vector2f(0.f, LANE_HEIGHT));
}