#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.cpp"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"

class Game {
private:
    LinkedList<Player *> *playersList;
    LinkedList<Enemy *> *enemyList;
    ALLEGRO_BITMAP *tiles;
    Player *player;
    int map[21][27];

    void createPlayers();
    void drawMap();
    void createMap();

public:
    Game();
    void update(int, int);
    void draw();
    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
