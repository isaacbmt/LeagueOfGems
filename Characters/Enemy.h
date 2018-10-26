#ifndef LEAGUEOFGEMS_ENEMY_H
#define LEAGUEOFGEMS_ENEMY_H


#include <allegro5/bitmap.h>
#include <string>

class Enemy {
private:
    int posx;
    int posy;
    int life = 3;
    ALLEGRO_BITMAP *image;

public:
    Enemy(std::string);
    Enemy(int, int, std::string);
    void update(int, int);
    void draw();
    void getDamage();
    ~Enemy();
};


#endif //LEAGUEOFGEMS_ENEMY_H
