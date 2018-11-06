#ifndef LEAGUEOFGEMS_PLAYER_H
#define LEAGUEOFGEMS_PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "Enemy.h"
#include "math.h"
#include "../GreedyAlgorithms/Dijkstra.h"
#include "../GreedyAlgorithms/AstarDirectory/coordinate.h"
#include "../GreedyAlgorithms/AstarDirectory/MapSearchNode.h"
#include "../GreedyAlgorithms/AstarDirectory/execAStar.h"
#include "../GreedyAlgorithms/Kruskal.h"
#include "../GreedyAlgorithms/Prim/Heap.h"
#include "../GreedyAlgorithms/Prim/PrimSolver.h"
#include "../GreedyAlgorithms/Prim/Grafo.h"

class Player {
private:
    ALLEGRO_BITMAP *image;
    ALLEGRO_BITMAP *healImg;
    Dijkstra *dij;
    vector<coordinate> aStar;
    execAStar ejecutable = ejecutable;
    Kruskal *kruscal;
    Grafo grafo;
    int x;
    int y;
    int direction;
    int movement;
    int attackX;
    bool attack;
    int healX;
    bool healing;
    int animationTimer;
    int aLength;
    int life;

    void timer();

public:
    Heap<pair<int, int>> prim;
    int aIndex;
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

    void getDamage(int);

    Dijkstra *getDij();

    Kruskal *getKruskal();

    void initGreedy(int [21][27]);

    void setMapOnGreedy(int [21][27]);

    void setPathToPrim(Grafo grafo, int destinoX, int destinoY);

    void setAstar(int [21][27], MapSearchNode);

    vector<coordinate> getAstar();

    int getALength() const;

    int getLife();

    void heal();

    void stopHeal();

    int getDirection() const;

    ~Player();
};


#endif //LEAGUEOFGEMS_PLAYER_H
