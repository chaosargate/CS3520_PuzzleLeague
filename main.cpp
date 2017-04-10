#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include "Grid.h"
using namespace puzzle_league;
using namespace sf;

/**
 * @namespace puzzle_league Implementation of Puzzle League game.
 *
 * @author Fiona Hasanaj, Aaron Hoang
 */

// Offset to center the sprites inside the outline of the background.
Vector2f offset(224, 80);

// Grid to be populated with gems.
Grid grid;

/**
 * Main program for running Puzzle League game.
 * @return The exit status.  Normal status is 0.
 */
int main() {
    // Start time of the game.
    auto startTime = std::chrono::system_clock::now();
    // Allows to produce a different pseudo-random series each time the program is run.
    // Used for randomizing the gems in the grid.
    srand(time(0));

    RenderWindow app(VideoMode(640, 464), "Puzzle League!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/gems.png");
    t3.loadFromFile("images/cursor.png");

    // Create the background, gem and cursor sprites.
    Sprite background(t1), gems(t2), cursor(t3);

    // Set initial position of the cursor.
    cursor.setPosition(284, 430);
    // Index of the row and column of the position of the cursor.
    int cursorRow, cursorCol;
    // Offset of the position of the cursor.
    Vector2f cursorPos;

    // If Left, Right, Up, Down, Space buttons are released.
    bool isReleased = true;
    // Offset value to increase the Y position of all gems by.
    int offsetAmount = 4;
    int lastTime;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            // Update the position of the cursor.
            cursorPos = cursor.getPosition() - offset;
            if (e.type == Event::Closed) {
                app.close();
            }

            // When space is pressed, swap the gems inside the cursor.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isReleased) {
                // Read the position of the cursor.
                cursorCol = cursorPos.x / grid.getTileSize() + 2;
                cursorRow = cursorPos.y / grid.getTileSize() + 2;
                Gem *gem1 = grid.getGem(cursorRow, cursorCol);
                Gem *gem2 = grid.getGem(cursorRow, cursorCol + 1);
                grid.swap(&gem1, &gem2);
                isReleased = false;

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    and isReleased) {
                // Move cursor Left
                cursorCol = cursorPos.x / grid.getTileSize() + 2;

                if (cursorCol > 1) {
                    cursor.move(grid.getTileSize() * -1, 0);
                    isReleased = false;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    and isReleased) {
                // Move cursor Right
                cursorCol = cursorPos.x / grid.getTileSize() + 2;

                if (cursorCol < 5) {
                    cursor.move(grid.getTileSize() * 1, 0);
                    isReleased = false;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                    and isReleased) {
                // Move cursor Up
                cursorRow = cursorPos.y / grid.getTileSize() + 2;

                if (cursorRow > 1) {
                    cursor.move(0, grid.getTileSize() * -1);
                    isReleased = false;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                    and isReleased) {
                // Move cursor Down
                cursorRow = cursorPos.y / grid.getTileSize() + 2;

                if (cursorRow < 12) {
                    cursor.move(0, grid.getTileSize() * 1);
                    isReleased = false;
                }
            }

            // When any key is released, allow movement again.
            if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
                isReleased = true;
            }
        }

        // Calculate the elapsed time in seconds since the start of the game.
        auto now = std::chrono::system_clock::now();
        auto dur = now - startTime;
        auto secs = std::chrono::duration_cast<std::chrono::duration<int>>(dur);

        // Convert duration to hh:mm:ss format
        int seconds = secs.count();
        int minutes = (int) ((seconds / 60) % 60);
        int hours = (int) ((seconds / (60 * 60)) % 24);
        seconds = (int) (seconds % 60);

        // Set the value of the elapsed time.
        string timeText = "TIME ";
        std::stringstream sstm;
        if (hours < 10) {
            sstm << "0" << hours;
        } else {
            sstm << hours;
        }
        if (minutes < 10) {
            sstm << ":0" << minutes;
        } else {
            sstm << ":" << minutes;
        }
        if (seconds < 10) {

            sstm << ":0" << seconds;
        } else {
            sstm << ":" << seconds;
        }
        timeText += sstm.str();

        // Clear stringstream
        sstm.str(std::string());
        sstm.clear();

        // Set the value of the score.
        sstm << "SCORE " << grid.getScore();
        string scoreText = sstm.str();

        // Text of the score.
        Text score;
        // Text of the elapsed time.
        Text time;
        // Font style for score and elapsed time.
        Font font;
        if (!font.loadFromFile("ScoreFont.ttf")) {
            // Throw error
        } else {
            // Set the font.
            time.setFont(font);
            score.setFont(font);

            // Set the string to display.
            time.setString(timeText);
            score.setString(scoreText);

            // Set the character size.
            time.setCharacterSize(35); // in pixels, not points!
            score.setCharacterSize(45);

            // Set the color.
            time.setColor(sf::Color::Red);
            score.setColor(sf::Color::Blue);

            score.setPosition(450, 0);
        }

        // Find matches between gems in the grid.
        grid.findMatch();

        // Move the gems.
        grid.setIsMoving(false);
        grid.moveGems();

        // Fade the gems that are matches.
        grid.deleteGems();

        // Update grid.
        grid.update();

        // If time has passed, update the offset value.
        if (seconds != lastTime) {
            grid.updateOffset(offsetAmount);
            cursor.move(0, -1 * offsetAmount);
            lastTime = seconds;
        }

        // Get the current offset of the grid.
        int gridOffset = grid.getOffset();

        // Check if the gems have reached the top of the grid, if so then GAME OVER!
        for (int j = 1; j < 7; ++j) {
            if (grid.getGem(1, j)->getAlpha() == 255) {
                if (gridOffset >= 16) {
                    cout << "GAME OVER" << endl;
                    break;
                }
            }
        }

        // Otherwise, update gems if the offset has reached 32 pixels.
        if (gridOffset >= grid.getTileSize()) {
            grid.raiseGems();
        }

        // Draw the background.
        app.draw(background);

        // Draw the gems.
        for (int i = 1; i <= 13; i++) {
            for (int j = 1; j < 7; j++) {
                Gem *p = grid.getGem(i, j);
                if (p) {
                    gems.setTextureRect(IntRect(p->getKind() * 32, 0, 32, 32));
                    gems.setColor(Color(255, 255, 255, p->getAlpha()));
                    gems.setPosition(p->getX(), p->getY());
                    gems.move(offset.x - grid.getTileSize(),
                            offset.y - grid.getTileSize());
                    app.draw(gems);
                }
            }
        }

        // Draw the cursor.
        app.draw(cursor);

        // Draw elapsed time.
        app.draw(time);

        // Draw score.
        app.draw(score);

        // Display the game.
        app.display();
    }
    return 0;
}
