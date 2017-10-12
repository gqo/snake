#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>



int main() {
    bool inGame = 0; //are you in game?
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
    sf::Text startText("Press Space to Begin",font,55); // Start instruction { TBD }
    startText.setFillColor(sf::Color::White);
    startText.setStyle(sf::Text::Bold);
    startText.setPosition(32,300);
    sf::RectangleShape body(sf::Vector2f(20, 20)); //Snake body
    body.setPosition(240,240);
    // Creates game window instance
    while (window.isOpen()) {
        // Tracks interactions with window
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // Window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                // Key pressed
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        // Close window if escape is pressed
                        case sf::Keyboard::Escape:
                            if(inGame ==1){ inGame = 0; }
                            else{ window.close(); }
                            break;
                        // Starts game
                        case sf::Keyboard::Space:
                            inGame = 1;
                        // Default for unhandled keypress
                        default:
                            break;
                    }
                    break;
                // Default for unhandled event type
                default:
                    break;
            }
        }
        window.clear();
        
        if(inGame == 0) {
            window.draw(background);
            window.draw(titleText);
            window.draw(subText);
            window.draw(startText);
        }
        else {
            window.draw(body);   
        }
        window.display();
    }
    return 0;
}