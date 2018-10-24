#ifndef LEAGUEOFGEMS_ENEMY_H
#define LEAGUEOFGEMS_ENEMY_H


#include <allegro5/bitmap.h>
#include <string>

class Enemy {
private:
    int x;
    int y;
    ALLEGRO_BITMAP *image;

public:
    Enemy(std::string);
    Enemy(int, int, std::string);
    void update(int, int);
    void draw();
    ~Enemy();
};


#endif //LEAGUEOFGEMS_ENEMY_H
