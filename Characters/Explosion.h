#ifndef LEAGUEOFGEMS_EXPLOSION_H
#define LEAGUEOFGEMS_EXPLOSION_H


#include <allegro5/bitmap.h>

class Explosion {
private:
    ALLEGRO_BITMAP *boom;
    int posx;
    int posy;
    int pivotX;
    int pivotY;
    int animationTimer;

public:
    Explosion(int, int);
    ~Explosion();
    void draw();
    int getPivotY();
};


#endif //LEAGUEOFGEMS_EXPLOSION_H
