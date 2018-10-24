#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.cpp"
#include "../Characters/Player.h"

class Game {
private:
    LinkedList<Player> *playersList;
    Player *player;

    void createPlayers();
    void createMap();

public:
    Game();
    void update();
    void draw(int, int);
    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
