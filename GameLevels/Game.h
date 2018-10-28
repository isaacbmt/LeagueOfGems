#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.cpp"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"
#include "../GreedyAlgorithms/Dijkstra.h"
#include "../Characters/Explosion.h"
#include "../Characters/Sword.h"
#include "../Characters/Bullet.h"

class Game {
private:
    LinkedList<Player *> *playersList;
    LinkedList<Enemy *> *enemyList;
    LinkedList<Explosion *> *explosionList;
    LinkedList<Sword *> *swordList;
    LinkedList<Bullet *> *bulletList;

    ALLEGRO_BITMAP *tiles;
    Player *player;
    int map[21][27];
    Dijkstra dij = Dijkstra();//Agregue esta variable
    int animationTimer;
    int currentAttack;
    int level;

    void createPlayers();
    void drawMap();
    void createMap();

public:
    Game();//Hice un cambio en este metodo
    void update(int, int);//Y en este metodo tambien XD
    void updateCenter(int, int);//Añadi este metodo para definir el centro d calculo para pathfinding
    void attack1();
    void attack2();
    Enemy * searchEnemy(int, int);
    void draw();
    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
