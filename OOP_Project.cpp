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

void CarSpawner(int& carSpawnTimer, int& carSpawnCooldown, vector<Car>& cars);
void LogSpawner(int& logSpawnTimer, int& logSpawnCooldown, vector<Log>& logs);

int main()
{
    srand(time(0));
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);

    // Gameobjects Initialization
    Frog player(window);
    Texture backgroundImage;
    Sprite backgroundSprite;
    backgroundImage.loadFromFile("Resources/Images/Background.png");
    backgroundSprite.setTexture(backgroundImage);
    
    // player movement sport
    int KeyCooldown = 5;
    int KeyTimer = 0;
    IntRect texRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE);

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
        player.texRect = texRect;

        // player movement control
        if (Keyboard::isKeyPressed(Keyboard::Up) && KeyTimer >= KeyCooldown)
        {
            texRect.top = 1 * CELL_SIZE;
            texRect.left = 1 * CELL_SIZE;
            player.texRect = texRect;
            texRect.left = 0 * CELL_SIZE;
            player.Move(0, -1);
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && KeyTimer >= KeyCooldown)
        {
            texRect.top = 3 * CELL_SIZE;
            texRect.left = 1 * CELL_SIZE;
            player.texRect = texRect;
            texRect.left = 0 * CELL_SIZE;
            player.Move(0, 1);
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) && KeyTimer >= KeyCooldown)
        {
            texRect.top = 2 * CELL_SIZE;
            texRect.left = 1 * CELL_SIZE;
            player.texRect = texRect;
            texRect.left = 0 * CELL_SIZE;
            player.Move(-1, 0);
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && KeyTimer >= KeyCooldown)
        {
            texRect.top = 0 * CELL_SIZE;
            texRect.left = 1 * CELL_SIZE;
            player.texRect = texRect;
            texRect.left = 0 * CELL_SIZE;
            player.Move(1, 0);
            KeyTimer = 0;
        }
        else
        {
            KeyTimer++;
        }
        CarSpawner(carSpawnTimer, carSpawnCooldown, cars);
        LogSpawner(logSpawnTimer, logSpawnCooldown, logs);
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
    return 0;
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
    // collision free spawning
    if (logs.size() > 0)
    {
        int tries = 0;
        while (Log(randomLogType, randomLane).getSprite().getGlobalBounds().intersects(logs.back().getSprite().getGlobalBounds()) && tries < 4)
        {
            if (randomLane == 3)
                randomLane = 0;
            else
                randomLane++;
            tries++;
        }
    }
	logs.push_back(Log(randomLogType, randomLane));
}