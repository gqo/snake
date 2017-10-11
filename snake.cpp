#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    // Initialize background shape
    sf::RectangleShape background(sf::Vector2f(480,480));
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(10);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(10,10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}