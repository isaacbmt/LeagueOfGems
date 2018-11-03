#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.cpp"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"
#include "../GreedyAlgorithms/Dijkstra.h"
#include "../Characters/Explosion.h"
#include "../Characters/Sword.h"
#include "../Characters/Bullet.h"
#include "../Characters/Laser.h"
#include "../Characters/Gem.h"

class Game {
private:
    LinkedList<Player *> *playersList;
    LinkedList<Enemy *> *enemyList;
    LinkedList<Explosion *> *explosionList;
    LinkedList<Sword *> *swordList;
    LinkedList<Bullet *> *bulletList;
    LinkedList<Laser *> *laserList;


    ALLEGRO_BITMAP *tiles;
    ALLEGRO_BITMAP *icon1;
    ALLEGRO_BITMAP *icon2;
    ALLEGRO_BITMAP *icon3;
    ALLEGRO_BITMAP *icon4;
    Gem *gem;
    //Player *player;
    int x;
    int y;
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

    void update();//Y en este metodo tambien XD

    void updateCenter(int, int);//Añadi este metodo para definir el centro d calculo para pathfinding

    void updateLevel1(int, int);

    void updateLevel2(int, int);

    void movement1();

    void movement2();

    void attack1();

    void attack2();

    void attack3();

    void enemysAttacks();

    Enemy * searchEnemy(int, int);

    void draw();

    void drawAttackIcons();

    void deleteObjectInGame();

    void setCurrentAttack(int);

    void printM();

    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
