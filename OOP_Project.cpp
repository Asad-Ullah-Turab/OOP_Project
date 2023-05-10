#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Frog.h"

using namespace sf;
using namespace std;

int main()
{
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);

    // player movement sport
    int KeyCooldown = 5;
    int KeyTimer = 0;

    // Gameobjects Initialization
    Frog player;

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
        if (Keyboard::isKeyPressed(Keyboard::Up) && KeyTimer >= KeyCooldown)
        {
            player.MoveUp();
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && KeyTimer >= KeyCooldown)
        {
            player.MoveDown();
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) && KeyTimer >= KeyCooldown)
        {
            player.MoveLeft();
            KeyTimer = 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && KeyTimer >= KeyCooldown)
        {
            player.MoveRight();
            KeyTimer = 0;
        }
        else
            KeyTimer++;
            

        // Clear
        window.clear();

        // Draw Stuff
        player.Draw(window);
        // Display
        window.display();
    }
    return 0;
}
