#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1366, 768), "OOP Project", Style::Default);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Update


        // Draw
        window.clear();
        // Draw Stuff

        // Finished drawing
        window.display();
    }
    
    cout << "Hello World!\n";
    return 0;
}
