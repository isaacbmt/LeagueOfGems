#ifndef LEAGUEOFGEMS_LASER_H
#define LEAGUEOFGEMS_LASER_H


#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include "Player.h"

class Laser {
private:
    ALLEGRO_BITMAP *laser;
    Enemy *enemy;
    int xi;
    int yi;
    int pivot;
    int animationTimer;
    int direction;

public:
    bool isAttacking;

    Laser(int, int, int, Enemy *);
    void draw();
    bool damage(Player *);

    Enemy *getEnemy();

    ~Laser();
};


#endif //LEAGUEOFGEMS_LASER_H
