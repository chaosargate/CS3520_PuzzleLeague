#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Grid.h"
using namespace puzzle_league;
using namespace sf;

int ts = 32; //tile size
Vector2i offset(224, 80);

Grid grid;

int main() {
    cout << "Created Grid" << endl;
    srand(time(0));

    RenderWindow app(VideoMode(640, 464), "Puzzle League!");
    app.setFramerateLimit(60);

    Texture t1, t2;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/gems.png");

    Sprite background(t1), gems(t2);

    int x0, y0, x, y;
    int click = 0;
    Vector2i pos;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) {
                    if (!grid.getIsMoving())
                        click++;
                    pos = Mouse::getPosition(app) - offset;
                }
        }

        // mouse click
        if (click == 1) {
            x0 = pos.x / ts + 1;
            y0 = pos.y / ts + 1;
        }
        if (click == 2) {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;
            if (abs(x - x0) + abs(y - y0) == 1) {
                Gem *gem1 = grid.getGem(y0, x0);
                Gem *gem2 = grid.getGem(y, x);
                grid.swap(&gem1, &gem2);
                click = 0;
            } else
                click = 1;
        }

        //cout << "Ready to find matches" << endl;
        grid.findMatch();

        //cout << "Found Matches" << endl;

        //Moving animation
        grid.setIsMoving(false);
        grid.moveGems();

        //cout << "Moved Gems" << endl;

        //Deleting amimation
        grid.deleteGems();

        //cout << "Deleted Gems" << endl;
        //Update grid
        grid.update();

        //cout << "Updated Grid" << endl;

        //////draw///////
        app.draw(background);

        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 7; j++) {
                Gem *p = grid.getGem(i, j);
                if (p) {
                    gems.setTextureRect(IntRect(p->getKind() * 32, 0, 32, 32));
                    gems.setColor(Color(255, 255, 255, p->getAlpha()));
                    gems.setPosition(p->getX(), p->getY());
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);
                }
            }

        app.display();
    }
    return 0;
}
