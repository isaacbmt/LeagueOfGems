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
    LinkedList<Gem *> *gemList;

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
    void createFirstMap();
    void createNextMap();

    void updateLevel1(int x, int y, bool arr, bool aba, bool der, bool izq);
    void updateLevel2(int x, int y, bool arr, bool aba, bool der, bool izq);
    void updateLevel3(int x, int y, bool arr, bool aba, bool der, bool izq);

    void movement1();
    void movement2();
    void movement3();

    void attack1();
    void attack2();
    void attack3();

    Enemy * searchEnemy(int, int);

    void enemysAttacks();

    void drawAttackIcons();
    void deleteObjectInGame();

public:

    Game();//Hice un cambio en este metodo

    void update();//Y en este metodo tambien

    void updateCenter(int, int);//Añadi este metodo para definir el centro d calculo para pathfinding

    void draw();

    void setCurrentAttack(int);

    void printM();

    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
