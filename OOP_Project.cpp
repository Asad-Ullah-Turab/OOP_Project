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
    // creating window
    RenderWindow window(VideoMode(800, 600), "OOP Project", Style::Default);
    window.setFramerateLimit(30);

    CircleShape circle(50.f);
    circle.setFillColor(Color(145, 219, 124, 167));
    circle.setOrigin(Vector2f(25.f, 25.f));

    RectangleShape rectangle(Vector2f(30.f, 45.f));
    rectangle.setPosition(Vector2f(50.f, 134.f));
    rectangle.setOrigin(25.f, 134 / 2);

    CircleShape triangle(30, 3);
    triangle.setFillColor(Color(0, 0, 0, 0));
    triangle.setOutlineThickness(5.f);
    triangle.setOutlineColor(Color(12, 45, 129, 255));

    ConvexShape convex(3);
    convex.setPoint(0, Vector2f(45, 12));
    convex.setPoint(0, Vector2f(34, 2));
    convex.setPoint(0, Vector2f(56, 124));
    convex.setFillColor(Color::Cyan);

    Vertex line[] = { Vertex(Vector2f(45, 13)) ,Vertex(Vector2f(100,600)) };

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

        circle.move(Vector2f(1.f, 5.f));
        circle.rotate(12.f);
        rectangle.move(Vector2f(1.f, 2.f));
        rectangle.rotate(23.f);

        // Clear
        window.clear();

        // Draw Stuff
        window.draw(rectangle);
        window.draw(circle);
        window.draw(triangle);
        window.draw(convex);
        window.draw(line, 2, Lines);

        // Display
        window.display();
    }
    return 0;
}
