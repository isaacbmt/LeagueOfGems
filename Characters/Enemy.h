#ifndef LEAGUEOFGEMS_ENEMY_H
#define LEAGUEOFGEMS_ENEMY_H


#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>

class Enemy {
private:
    int life;
    int posx;
    int posy;
    ALLEGRO_BITMAP *image;

public:
    Enemy(std::string);
    Enemy(int, int, std::string);
    ~Enemy();
    void update(int, int);
    void draw();
    void getDamage();
    int getLife();
    int getPosx();
    int getPosy();
};


#endif //LEAGUEOFGEMS_ENEMY_H
