#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.h"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"
#include "../GreedyAlgorithms/Dijkstra.h"
#include "../Characters/Explosion.h"
#include "../Characters/Sword.h"
#include "../Characters/Bullet.h"
#include "../Characters/Laser.h"
#include "../Characters/Gem.h"
#include "../DataStructures/AlgoritmoGen.h"

class Game {
private:
    LinkedList<Player *> *playersList;
    LinkedList<Enemy *> *enemyList;
    LinkedList<Explosion *> *explosionList;
    LinkedList<Sword *> *swordList;
    LinkedList<Bullet *> *bulletList;
    LinkedList<Laser *> *laserList;
    LinkedList<Gem *> *gemList;
    AlgoritmoGen *generic;

    ALLEGRO_BITMAP *tiles;
    ALLEGRO_BITMAP *icon1;
    ALLEGRO_BITMAP *icon2;
    ALLEGRO_BITMAP *icon3;
    ALLEGRO_BITMAP *icon4;

    int map[21][27];
    int animationTimer;
    int currentAttack;
    int numero_oleada;
    int level;
    int defeated;
    int x;
    int y;

    void createFirstMap();
    void createNextMap();
    void drawMap();

    void updateLevel1(int x, int y, bool arr, bool aba, bool der, bool izq);
    void updateLevel2(int x, int y, bool arr, bool aba, bool der, bool izq);
    void updateLevel3(int x, int y, bool arr, bool aba, bool der, bool izq);
    void updateLevel4(int x, int y, bool arr, bool aba, bool der, bool izq);

    void movement1();
    void movement2();
    void movement3();
    void movement4();

    void attack1();
    void attack2();
    void attack3();

    Enemy * searchEnemy(int, int);

    void enemysAttacks();

    void drawAttackIcons();
    void deleteObjectInGame();

public:
    Game();//Hice un cambio en este metodo
    void updateCenter(int, int);//Añadi este metodo para definir el centro d calculo para pathfinding
    void update();//Y en este metodo tambien
    void draw();
    void setCurrentAttack(int);
    int getState();
    void printM();

    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
