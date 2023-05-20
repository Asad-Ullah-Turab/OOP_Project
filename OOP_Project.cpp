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

// Function Prototypes
void StartScreen(RenderWindow& window);
void StartGame(RenderWindow& window);
void PlayerMovement(Frog& player, IntRect& texRect, int& keyCooldown, int& keyTimer);
void CarSpawner(int& carSpawnTimer, int& carSpawnCooldown, vector<Car>& cars);
void ObjectRemover(vector<Car>& cars);
void ObjectRemover(vector<Log>& logs);
void LogSpawner(int& logSpawnTimer, int& logSpawnCooldown, vector<Log>& logs);
bool GameOver(RenderWindow& window, bool hasWon);


int main()
{
    srand(time(0));
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);
    StartScreen(window);
    StartGame(window);
    return 0;
}
void StartScreen(RenderWindow& window)
{
	// Gameobjects Initialization
	Texture backgroundImage;
	Sprite backgroundSprite;
    if (!backgroundImage.loadFromFile("Resources/Images/StartScreen.png"))
        cout << "could not load main menu image" << endl;
	backgroundSprite.setTexture(backgroundImage);
    // Font initialization
    Font mainMenuFont;
    if (!mainMenuFont.loadFromFile("Resources/Fonts/Goldman-Regular.ttf"))
        cout << "could not load main menu font" << endl;
    Text startGameText;
    startGameText.setCharacterSize(50);
    startGameText.setFillColor(Color::White);
    startGameText.setFont(mainMenuFont);
    Text creditsText = startGameText;
    Text exitText = startGameText;

    // Text initialization
    startGameText.setString("Start Game");  
    startGameText.setPosition((WINDOW_WIDTH - startGameText.getGlobalBounds().width)/2, 300);
    creditsText.setString("Credits");
    creditsText.setPosition((WINDOW_WIDTH - creditsText.getGlobalBounds().width)/2, 370);
    exitText.setString("Exit");
    exitText.setPosition((WINDOW_WIDTH - exitText.getGlobalBounds().width)/2, 440);


    int choice = 0;
    int keyTimer = 0;
    int keyCooldown = 10;
    
	// Main game loop
    while (window.isOpen())
    {
		Event event;
        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed)
				window.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter) && choice == 0)
            {
				return;
			}
            else if (Keyboard::isKeyPressed(Keyboard::Enter) && choice == 1)
            {
				// credits
			}
            else if (Keyboard::isKeyPressed(Keyboard::Enter) && choice == 2)
            {
				window.close();
			}
		}
        // Menu selection
        if (Keyboard::isKeyPressed(Keyboard::Up) && keyTimer >= keyCooldown)
        {
			choice--;
			if (choice < 0)
				choice = 2;
            keyTimer = 0;
		}
        else if (Keyboard::isKeyPressed(Keyboard::Down) && keyTimer >= keyCooldown)
        {
            choice++;
            if(choice > 2)
				choice = 0;
            keyTimer = 0;
        }
        keyTimer++;
        switch (choice)
        {
        case 0:
            startGameText.setFillColor(Color::Red);
            creditsText.setFillColor(Color::White);
            exitText.setFillColor(Color::White);
            break;
        case 1:
            startGameText.setFillColor(Color::White);
            creditsText.setFillColor(Color::Red);
            exitText.setFillColor(Color::White);
            break;
        case 2:
            startGameText.setFillColor(Color::White);
            creditsText.setFillColor(Color::White);
            exitText.setFillColor(Color::Red);
            break;
        }

		// Clear
		window.clear();
		// Draw Stuff
		window.draw(backgroundSprite);
        window.draw(startGameText);
        window.draw(creditsText);
        window.draw(exitText);
		// Display
		window.display();
	}
}
void StartGame(RenderWindow& window)
{
    bool isGameOver = false;
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
        // Collision detection with cars
        for (int i = 0; i < cars.size(); i++)
        {
            if (player.getSprite().getGlobalBounds().intersects(cars[i].getSprite().getGlobalBounds()))
                isGameOver = true;
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
        if (isGameOver == true || player.hasWon)
        {
            if (GameOver(window, player.hasWon))
            {
                for (int i = logs.size() - 1; i >= 0; i--)
                {
                    logs.erase(logs.begin() + i);
                }
                for (int i = cars.size() - 1; i >= 0; i--)
                {
                    cars.erase(cars.begin() + i);
                }
                player.Reset();
                isGameOver = false;
            }
            else
            {
                break;
            }
        }
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
bool GameOver(RenderWindow& window, bool hasWon)
{
    // Game Over background sprite initialization
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("Resources/Images/Background.png");
    backgroundTexture.update(window);
    Sprite gameOverSprite;
    gameOverSprite.setTexture(backgroundTexture);

    // initializing game over rectangle
    RectangleShape gameOverRectangele;
    gameOverRectangele.setSize(Vector2f(500, 400));
    gameOverRectangele.setFillColor(Color(0, 0, 0, 200));
    gameOverRectangele.setPosition((WINDOW_WIDTH - gameOverRectangele.getGlobalBounds().width) / 2, (WINDOW_HEIGHT - gameOverRectangele.getGlobalBounds().height) / 2);

    // font initialization
    Font gameOverFont;
    if (!gameOverFont.loadFromFile("Resources/Fonts/Goldman-Regular.ttf"))
        cout << "could not load game over menu font" << endl;
    // game over menu button text initialization
    Text retryText;
    retryText.setCharacterSize(50);
    retryText.setFillColor(Color::White);
    retryText.setFont(gameOverFont);
    Text exitText = retryText;

    retryText.setString("Retry");
    retryText.setPosition((WINDOW_WIDTH - retryText.getGlobalBounds().width) / 2, 300);
    exitText.setString("Exit");
    exitText.setPosition((WINDOW_WIDTH - exitText.getGlobalBounds().width) / 2, 370);

    // GameOver Text initialization
    Text gameOverText;
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::Green);
    gameOverText.setFont(gameOverFont);
    if (hasWon)
        gameOverText.setString("You Won");
    else
        gameOverText.setString("Game Over");
    gameOverText.setPosition((WINDOW_WIDTH - gameOverText.getGlobalBounds().width) / 2, 130);

    int choice = 0;
    int keyTimer = 0;
    int keyCooldown = 10;

    while (true)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (choice == 0)
                    return true;
                if (choice == 1)
                    return false;
            }
        }
        // Menu selection
        if (Keyboard::isKeyPressed(Keyboard::Up) && keyTimer >= keyCooldown)
        {
            choice--;
            if (choice < 0)
                choice = 1;
            keyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && keyTimer >= keyCooldown)
        {
            choice++;
            if (choice > 1)
                choice = 0;
            keyTimer = 0;
        }
        keyTimer++;
        switch (choice)
        {
        case 0:
            retryText.setFillColor(Color::Red);
            exitText.setFillColor(Color::White);
            break;
        case 1:
            retryText.setFillColor(Color::White);
            exitText.setFillColor(Color::Red);
            break;
        }

        // Draw
        window.draw(gameOverSprite);
        window.draw(gameOverRectangele);
        window.draw(gameOverText);
        window.draw(retryText);
        window.draw(exitText);
        // display 
        window.display();
    }
}