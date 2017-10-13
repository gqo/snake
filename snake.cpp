#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

/*
To-do: { [] = not done; [x] = done; }
    Snake tail implementation []
    Death screen []
    Border wall collision []
    Food generation []
    Food collision []
    Snake growth []
    Snake collision []
    Pause implementation []

Ideas:
    Points?
    High scores?
    Snake sprites? { I.e. no more blocks }
    Settings?
        Difficulty?
        Artistic styles? { I.e. block mode, sprite mode, visual settings in general }
        Wall collision on/off?
    Levels? { I.e. different maps with different walls }
*/

// (Hopefully) extensible function for character movement
void movement(int direction, sf::RectangleShape& section) {
    switch(direction) {
        // Up
        case 0:
            section.move(0,-20);
            break;
        // Down
        case 1:
            section.move(0,20);
            break;
        // Left
        case 2:
            section.move(-20,0);
            break;
        // Right
        case 3:
            section.move(20,0);
            break;
    }
}

// (Hopefully) extensible function for reseting game on escape
void gameReset(sf::RectangleShape& section) {
    section.setPosition(240,240);
}

int main() {
    // Initialize popup window, i.e. the game window
    sf::RenderWindow window(sf::VideoMode(520, 520), "Snake");
    // Initialize background shape and look
    sf::RectangleShape background(sf::Vector2f(480,480));
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(20);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(20,20);
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
    // Initialize game on/off bool
    bool inGame = 0; // 0 == off
    // Initialize game pause bool
    bool pause = 0; // 0 == not paused
    // Initialize game screen objects
    sf::RectangleShape body(sf::Vector2f(20, 20)); // Character test body
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
                        // At menu, close window; in game, return to menu
                        // Resets game to start
                        case sf::Keyboard::Escape:
                            if(inGame == 1) { 
                                inGame = 0;
                                gameReset(body); 
                            }
                            else { window.close(); }
                            break;
                        // Starts game
                        case sf::Keyboard::Space:
                            inGame = 1;
                            break;
                        // Character movement handling
                        case sf::Keyboard::Up:
                            movement(0,body);
                            break;
                        case sf::Keyboard::Down:
                            movement(1,body);
                            break;
                        case sf::Keyboard::Left:
                            movement(2,body);
                            break;
                        case sf::Keyboard::Right:
                            movement(3,body);
                            break;
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
        // Draws background
        window.draw(background);
        // Draws menu screen
        if(inGame == 0) {
            window.draw(titleText);
            window.draw(subText);
            window.draw(startText);
        }
        // Draws game screen
        else { window.draw(body); }
        window.display();
    }
    return 0;
}