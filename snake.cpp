#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

/*
To-do: { [] = not done; [x] = done; }
    Snake tail implementation [x]
    Snake constant movement [] { Snake should save last direction and continuing moving that way }
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

// (Hopefully) extensible function for character movement of one section
void moveSection(int direction, sf::RectangleShape& section) {
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

// Function for adding a tail section to snake
void addTailSection(std::vector<sf::RectangleShape>& snakeSections) {
    sf::RectangleShape tailSection(sf::Vector2f(20,20));
    snakeSections.push_back(tailSection);
}

// Function for handling all character movement
void moveSnake(int direction, std::vector<sf::RectangleShape>& snakeSections) {
    sf::Vector2f leadPos = snakeSections[0].getPosition();
    sf::Vector2f trailPos;
    moveSection(direction, snakeSections[0]);
    for(int i = 1; i < snakeSections.size(); i++) {
        trailPos = snakeSections[i].getPosition();
        snakeSections[i].setPosition(leadPos);
        leadPos = trailPos;
    }
}

// Function for handling all character draws
void drawSnake(std::vector<sf::RectangleShape>& snakeSections, sf::RenderWindow& window) {
    for(int i = 0; i < snakeSections.size(); i++) {
        window.draw(snakeSections[i]);
    }
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
    // Initialize game state int
    int gameState = 0; // 0 == menu, 1 == game, 2 == pause, 3 == death
    // Initialize game screen objects
    sf::RectangleShape body(sf::Vector2f(20, 20)); // Character test body
    body.setPosition(240,240);
    // Initialize vector for tracking snake sections
    std::vector<sf::RectangleShape> snakeSections;
    snakeSections.push_back(body);
    addTailSection(snakeSections);
    addTailSection(snakeSections);
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
                            if(gameState == 1) { 
                                gameState = 0;
                                gameReset(body); 
                            }
                            else { window.close(); }
                            break;
                        // Starts game
                        case sf::Keyboard::Space:
                            gameState = 1;
                            break;
                        // Character movement handling
                        case sf::Keyboard::Up:
                            moveSnake(0,snakeSections);
                            break;
                        case sf::Keyboard::Down:
                            moveSnake(1,snakeSections);
                            break;
                        case sf::Keyboard::Left:
                            moveSnake(2,snakeSections);
                            break;
                        case sf::Keyboard::Right:
                            moveSnake(3,snakeSections);
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
        if(gameState == 0) {
            window.draw(titleText);
            window.draw(subText);
            window.draw(startText);
        }
        // Draws game screen
        else if(gameState == 1) { drawSnake(snakeSections,window); }
        window.display();
    }
    return 0;
}