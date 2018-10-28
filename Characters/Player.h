#ifndef LEAGUEOFGEMS_PLAYER_H
#define LEAGUEOFGEMS_PLAYER_H

#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "Enemy.h"
#include "math.h"

class Player {
private:
    ALLEGRO_BITMAP *image;
    ALLEGRO_BITMAP *imgAttack;
    int x, y;
    int direction;
    int movement;
    int attackX, attackY;
    bool attack;
    int animationTimer;
    int maxLife;
    int life;

public:
    Player(std::string);
    Player(int, int, std::string);
    void update(int, int);
    void draw();
    int getPosx();
    int getPosy();
    void attacking(Enemy *, int, int);
    bool isAttacking();
    void timer();
    ~Player();
};


#endif //LEAGUEOFGEMS_PLAYER_H
