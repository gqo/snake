#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main() {
    // Initialize popup window, i.e. the game window
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    // Initialize background shape and look
    sf::RectangleShape background(sf::Vector2f(480,480));
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(10);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(10,10);
    // Initialize font for use in menu screen
    sf::Font font;
    if(!font.loadFromFile("Ubuntu-C.ttf")) { // Loads font and checks for error
        std::cout << "Could not load font." << std::endl;
    }
    // Initialize menu screen text
    sf::Text titleText("SNAKE",font,90); // Title
    titleText.setFillColor(sf::Color::Blue);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(135,100);
    sf::Text subText("a game by Graeme & Reece",font,20); // Subtitle
    subText.setFillColor(sf::Color::Blue);
    subText.setPosition(147,200);
    sf::Text startText("Press TBD to Begin",font,60); // Start instruction { TBD }
    startText.setFillColor(sf::Color::White);
    startText.setStyle(sf::Text::Bold);
    startText.setPosition(35,300);
    // Creates game window instance
    while (window.isOpen()) {
        // Tracks interactions with window
        sf::Event event;
        while (window.pollEvent(event)) {
            // Checks if window was closed and then closes window
            if (event.type == sf::Event::Closed) { window.close(); }
        }
        window.clear();
        window.draw(background);
        window.draw(titleText);
        window.draw(subText);
        window.draw(startText);
        window.display();
    }
    return 0;
}