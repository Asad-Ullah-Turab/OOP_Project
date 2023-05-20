#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include "Frog.h"
#include "Global.h"
#include "Car.h"
#include "Log.h"

using namespace sf;
using namespace std;

void StartGame(RenderWindow& window);
void PlayerMovement(Frog& player, IntRect& texRect, int& keyCooldown, int& keyTimer);
void CarSpawner(int& carSpawnTimer, int& carSpawnCooldown, vector<Car>& cars);
void ObjectRemover(vector<Car>& cars);
void ObjectRemover(vector<Log>& logs);
void LogSpawner(int& logSpawnTimer, int& logSpawnCooldown, vector<Log>& logs);


int main()
{
    srand(time(0));
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);
    StartGame(window);
    return 0;
}
void StartGame(RenderWindow& window)
{
    // Gameobjects Initialization
    Frog player(window);
    Texture backgroundImage;
    Sprite backgroundSprite;
    backgroundImage.loadFromFile("Resources/Images/Background.png");
    backgroundSprite.setTexture(backgroundImage);

    // player movement support
    IntRect texRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE);
    int keyCooldown = 5;
    int keyTimer = 0;
    // car spawner support
    vector<Car> cars;
    int carSpawnCooldown = 20;
    int carSpawnTimer = 0;
    // Log spawner support
    vector<Log> logs;
    int logSpawnCooldown = 20;
    int logSpawnTimer = 0;

    // Main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Update

        // player movement control
        player.texRect = texRect;
        PlayerMovement(player, texRect, keyCooldown, keyTimer);

        // Collison detection with logs
        for (int i = 0; i < logs.size(); i++)
        {
            if (player.getSprite().getGlobalBounds().intersects(logs[i].getSprite().getGlobalBounds()))
            {
                player.MoveWithLog(logs[i]);
            }
        }
        // spawners
        CarSpawner(carSpawnTimer, carSpawnCooldown, cars);
        ObjectRemover(cars);
        LogSpawner(logSpawnTimer, logSpawnCooldown, logs);
        ObjectRemover(logs);
        // Clear
        window.clear();

        // Draw Stuff
        window.draw(backgroundSprite);
        // drawing logs
        for (int i = 0; i < logs.size(); i++)
        {
            logs[i].Move();
            window.draw(logs[i].getSprite());
        }
        player.Draw();
        // drawing cars
        for (int i = 0; i < cars.size(); i++)
        {
            cars[i].Move();
            window.draw(cars[i].getSprite());
        }
        // Display
        window.display();
    }
}
void PlayerMovement(Frog &player,IntRect &texRect, int& keyCooldown, int& keyTimer)
{

    if (Keyboard::isKeyPressed(Keyboard::Up) && keyTimer >= keyCooldown)
    {
        texRect.top = 1 * CELL_SIZE;
        texRect.left = 1 * CELL_SIZE;
        player.texRect = texRect;
        texRect.left = 0 * CELL_SIZE;
        player.Move(0, -1);
        keyTimer = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && keyTimer >= keyCooldown)
    {
        texRect.top = 3 * CELL_SIZE;
        texRect.left = 1 * CELL_SIZE;
        player.texRect = texRect;
        texRect.left = 0 * CELL_SIZE;
        player.Move(0, 1);
        keyTimer = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left) && keyTimer >= keyCooldown)
    {
        texRect.top = 2 * CELL_SIZE;
        texRect.left = 1 * CELL_SIZE;
        player.texRect = texRect;
        texRect.left = 0 * CELL_SIZE;
        player.Move(-1, 0);
        keyTimer = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && keyTimer >= keyCooldown)
    {
        texRect.top = 0 * CELL_SIZE;
        texRect.left = 1 * CELL_SIZE;
        player.texRect = texRect;
        texRect.left = 0 * CELL_SIZE;
        player.Move(1, 0);
        keyTimer = 0;
    }
    else
    {
        keyTimer++;
    }
}
void CarSpawner(int& carSpawnTimer, int& carSpawnCooldown, vector<Car>& cars)
{
    if (carSpawnTimer < carSpawnCooldown)
    {
        carSpawnTimer++;
        return;
    }
    carSpawnTimer = 0;
    int randomCarType = rand() % 6;
    int randomLane = (rand() % 4) + 4;
    cars.push_back(Car(randomCarType, randomLane));
}
void ObjectRemover(vector<Car>& cars)
{
    for (int i = 0; i < cars.size(); i++)
    {
        if ((cars[i].getSprite().getPosition().x > 900) || (cars[i].getSprite().getPosition().x + cars[i].getSprite().getGlobalBounds().width < 0))
        {
			cars.erase(cars.begin() + i);
		}
	}
}
void ObjectRemover(vector<Log>& logs)
{
    for (int i = 0; i < logs.size(); i++)
    {
        if ((logs[i].getSprite().getPosition().x > 800 + logs[i].getSprite().getGlobalBounds().width) || (logs[i].getSprite().getPosition().x + logs[i].getSprite().getGlobalBounds().width < 0))
        {
			logs.erase(logs.begin() + i);
		}
	}
}
void LogSpawner(int& logSpawnTimer, int& logSpawnCooldown, vector<Log>& logs)
{
    if (logSpawnTimer < logSpawnCooldown)
    {
		logSpawnTimer++;
		return;
	}
	logSpawnTimer = 0;
	int randomLogType = rand() % 3;
	int randomLane = rand() % 4;
    int tries = 0;
    // collision free spawning
    bool isIntersecting = true;
    if (logs.size() > 0)
    {   
        for (int i = 0; i < logs.size(); i++)
        {
            if (Log(randomLogType, randomLane).getSprite().getGlobalBounds().intersects(logs[i].getSprite().getGlobalBounds()))
            {
                if (randomLane == 3)
                    randomLane = 0;
                else
                    randomLane++;
                isIntersecting = true;
            }
            else
                isIntersecting = false;
        }
    }
    else
        logs.push_back(Log(randomLogType, randomLane));
    if (isIntersecting == false)
    {
        logs.push_back(Log(randomLogType, randomLane));
    }
}