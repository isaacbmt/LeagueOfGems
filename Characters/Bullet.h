#ifndef LEAGUEOFGEMS_BULLET_H
#define LEAGUEOFGEMS_BULLET_H

#include <allegro5/bitmap.h>
#include "Player.h"

class Bullet {
private:
    ALLEGRO_BITMAP *arrow;
    Player *player;
    int xi;
    int yi;
    int x;
    int y;
    int direction;
    int timer;

public:
    Bullet(Player *, int, int);
    void draw();
    int getTimer();
    int getX();
    int getY();
};


#endif //LEAGUEOFGEMS_BULLET_H
