#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main() {
    // Initialize popup window, i.e. the game window
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    // Initialize background shape and look
    sf::RectangleShape background(sf::Vector2f(480,480));
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(10);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(10,10);
    // Initialize font for use in menu screen
    sf::Font font;
    if(!font.loadFromFile("Ubuntu-C.ttf")) { // Loads font and checks for error
        std::cout << "Could not load font." << std::endl;
    }
    // Initialize menu screen text { UNDER CONSTRUCTION }
    sf::String sentence = "menu";
    sf::Text menuText(sentence,font,30);
    menuText.setFillColor(sf::Color::Blue);
    // Creates game window instance
    while (window.isOpen()) {
        // Tracks interactions with window
        sf::Event event;
        while (window.pollEvent(event)) {
            // Checks if window was closed and then closes window
            if (event.type == sf::Event::Closed) { window.close(); }
        }
        window.clear();
        //window.draw(background);
        window.draw(menuText);
        window.display();
    }
    return 0;
}