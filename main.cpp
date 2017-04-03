#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <chrono>
#include "Grid.h"
using namespace puzzle_league;
using namespace sf;

int ts = 32; //tile size
Vector2f offset(224, 80);

Grid grid;

int main() {
    srand(time(0));

    RenderWindow app(VideoMode(640, 464), "Puzzle League!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/gems.png");
    t3.loadFromFile("images/cursor.png");

    Sprite background(t1), gems(t2), cursor(t3);
    cursor.setPosition(284, 430);

    Text time;
    Font font;
    if (!font.loadFromFile("ScoreFont.ttf")) {
    } else {
        // set the font
        time.setFont(font);

        // set the string to display
        time.setString("Time: ");

        // set the character size
        time.setCharacterSize(44); // in pixels, not points!

        // set the color
        time.setColor(sf::Color::Red);

    }

    int row, col;
    Vector2f pos;
    bool hasMoved = false;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            // update the position of the cursor
            pos = cursor.getPosition() - offset;
            if (e.type == Event::Closed) {
                app.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !hasMoved) {

                col = pos.x / ts + 2;
                row = pos.y / ts + 2;
                Gem *gem1 = grid.getGem(row, col);
                Gem *gem2 = grid.getGem(row, col + 1);
                grid.swap(&gem1, &gem2);
                hasMoved = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    and !hasMoved) {
                // Move cursor Left
                col = pos.x / ts + 2;

                if (col > 1) {
                    cursor.move(ts * -1, 0);
                    hasMoved = true;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    and !hasMoved) {
                // Move cursor Right
                col = pos.x / ts + 2;

                if (col < 5) {
                    cursor.move(ts * 1, 0);
                    hasMoved = true;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                    and !hasMoved) {
                // Move cursor Up
                row = pos.y / ts + 2;

                if (row > 1) {
                    cursor.move(0, ts * -1);
                    hasMoved = true;
                }

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                    and !hasMoved) {
                // Move cursor Down
                row = pos.y / ts + 2;

                if (row < 12) {
                    cursor.move(0, ts * 1);
                    hasMoved = true;
                }
            }

            // When any key is released, allow movement again.
            if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
                hasMoved = false;
            }
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

        //grid.raiseGems();

        app.draw(background);

        for (int i = 1; i < 13; i++)
            for (int j = 1; j < 7; j++) {
                Gem *p = grid.getGem(i, j);
                if (p) {
                    gems.setTextureRect(IntRect(p->getKind() * 32, 0, 32, 32));
                    gems.setColor(Color(255, 255, 255, p->getAlpha()));
                    gems.setPosition(p->getX(), p->getY());
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);
                }
            }

        app.draw(cursor);
        time += time
        app.draw(time);

        app.display();
    }
    return 0;
}
