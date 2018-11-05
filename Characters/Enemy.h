#ifndef LEAGUEOFGEMS_ENEMY_H
#define LEAGUEOFGEMS_ENEMY_H


#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>

class Enemy {
private:
    ALLEGRO_BITMAP *image;
    bool attacking;
    int power;
    int maxLife;
    int life;
    int posx;
    int posy;

public:

    Enemy(int, int, std::string);

    ~Enemy();

    void update(int, int);

    void draw();

    void setPower(int);

    void getDamage();

    void startAttack();

    void endAttack();

    bool isAttacking();

    int getLife();

    int getPosx();

    int getPosy();
};


#endif //LEAGUEOFGEMS_ENEMY_H
