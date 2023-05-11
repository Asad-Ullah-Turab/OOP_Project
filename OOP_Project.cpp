#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Frog.h"
#include "Global.h"

using namespace sf;
using namespace std;

int main()
{
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);

    // Gameobjects Initialization
    Frog player(window);

    // player movement sport
    int KeyCooldown = 5;
    int KeyTimer = 0;
    IntRect texRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE);

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
            KeyTimer++;
            

        // Clear
        window.clear();

        // Draw Stuff
        player.Draw();
        // Display
        window.display();
    }
    return 0;
}
