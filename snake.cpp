#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// Includes for rand# gen
#include <stdlib.h>
#include <time.h>

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
void gameReset(std::vector<sf::RectangleShape>& snakeSections) {
    for(int i = 0; i < snakeSections.size(); i++) {
        snakeSections[i].setPosition(240,240);
    }
}

// Function for adding a tail section to snake
void addTailSection(std::vector<sf::RectangleShape>& snakeSections) {
    sf::RectangleShape tailSection(sf::Vector2f(20,20));
    tailSection.setPosition(snakeSections[0].getPosition());
    snakeSections.push_back(tailSection);
}

// Function for handling all character movement
/* 
Moves the snake head and then updates the tail sections' positions to the
positions that precede them. E.g. the tail section that follows the head will move
to where the head used to be.

Note: This shouldn't work as well as it does, most likely going to need to change it.
*/
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

// Function for generation of random position within boundary
sf::Vector2f randPos() {
    srand (time(NULL));
    sf::Vector2f randPosition(((rand() % 23 + 2) * 20),((rand() % 23 + 2) * 20));
    return randPosition;
}

// Function for handling food generation
void foodGen(std::vector<sf::RectangleShape>& foodSections, sf::RenderWindow& window) {
    sf::RectangleShape foodBit(sf::Vector2f(-20,-20));
    foodBit.setFillColor(sf::Color::Yellow);
    foodBit.setPosition(randPos());
    bool checkNewFood = 0;
    // Checks for creation of a food section on top of another food section
    while (!checkNewFood) {
        for(int i = 0; i < foodSections.size(); i++) {
            if(foodBit.getPosition() == foodSections[i].getPosition()) { checkNewFood = 0; }
            if(i == foodSections.size() - 1) { checkNewFood = 1; }
        }
        if(checkNewFood == 0) { foodBit.setPosition(randPos()); }
    }
    foodSections.push_back(foodBit);
}

// Function for handling food bit draws
void drawFood(std::vector<sf::RectangleShape>& foodSections, sf::RenderWindow& window) {
    for(int i = 0; i < foodSections.size(); i++) {
        window.draw(foodSections[i]);
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
    sf::Text startText("Press Space to Begin",font,55); // Start instruction
    startText.setFillColor(sf::Color::White);
    startText.setStyle(sf::Text::Bold);
    startText.setPosition(32,300);
    // Initialize game state int
    int gameState = 0; // 0 == menu, 1 == game, 2 == pause, 3 == death
    // Initialize game screen objects
    sf::RectangleShape body(sf::Vector2f(20, 20)); // Character test body
    body.setPosition(240,240);
    // Initialize vector for tracking snake sections and two tail sections
    std::vector<sf::RectangleShape> snakeSections;
    snakeSections.push_back(body);
    addTailSection(snakeSections);
    addTailSection(snakeSections);
    // Initialize vector for tracking food sections
    std::vector<sf::RectangleShape> foodSections;
    /*
    protoFood is required to instantiate the foodSections vector so when foodGen checks if
    the created foodBit is at the same position as another food section (to prevent drawing
    to food sections on the same point) there is something to check against. Otherwise foodGen
    checks for bits that don't exist and crashes the game.
    */
    sf::RectangleShape protoFood(sf::Vector2f(-40,-40)); 
    foodSections.push_back(protoFood);
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
                                gameReset(snakeSections); 
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
                        // Dev tool for testing food generation
                        case sf::Keyboard::F:
                            foodGen(foodSections,window);
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
        else if(gameState == 1) { 
            drawSnake(snakeSections,window); 
            drawFood(foodSections,window);
        }
        window.display();
    }
    return 0;
}