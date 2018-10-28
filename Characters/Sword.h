#ifndef LEAGUEOFGEMS_SWORD_H
#define LEAGUEOFGEMS_SWORD_H


#include <allegro5/bitmap.h>
#include "Enemy.h"

class Sword {
private:
    ALLEGRO_BITMAP *sword;
    bool attack;
    int x;
    int y;
    int attackX;
    int attackY;
    int animationTimer;

public:
    Sword(Enemy*, int, int, int, int);
    ~Sword();
    void draw();
    void timer();
    bool isAttacking();
};


#endif //LEAGUEOFGEMS_SWORD_H
