#ifndef LEAGUEOFGEMS_PLAYER_H
#define LEAGUEOFGEMS_PLAYER_H

#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "Enemy.h"
#include "math.h"
#include "../GreedyAlgorithms/Dijkstra.h"

class Player {
private:
    ALLEGRO_BITMAP *image;
    Dijkstra *dij;
    int x;
    int y;
    int direction;
    int movement;
    int attackX;
    bool attack;
    int animationTimer;
    int life;

    void timer();

public:
    int targetX;
    int targetY;

    Player(std::string);

    Player(int, int, std::string);

    void update(int, int);

    void draw();

    int getPosx();

    int getPosy();

    void attacking();

    bool isAttacking();

    Dijkstra *getDij();

    void setDij(int [21][27]);



    int getDirection() const;

    ~Player();
};


#endif //LEAGUEOFGEMS_PLAYER_H
