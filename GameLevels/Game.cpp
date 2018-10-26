#include <allegro5/allegro.h>
#include <ctime>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player *>;
    enemyList = new LinkedList<Enemy *>;
    player = new Player("../resources/hetalia.png");
    tiles = al_load_bitmap("../resources/medievaltiles.png");

    createMap();
}

void Game::update(int x, int y) {
    int posx = x / 50, posy = y / 50;

    player->update(x, y);

    for (int i = 0; i < enemyList->length(); ++i) {

        if (map[player->getPosy()][player->getPosx() - 1] == 3) {
            if (!player->isAttacking())
                player->attacking(enemyList->get(i), 3, 0);
        }
        else if (map[player->getPosy()][player->getPosx() + 1] == 3) {
            if (!player->isAttacking())
                player->attacking(enemyList->get(i), 1, 0);
        }
        else if (map[player->getPosy() - 1][player->getPosx()] == 3) {
            if (!player->isAttacking())
                player->attacking(enemyList->get(i), 3, 1);
        }
        else if (map[player->getPosy() + 1][player->getPosx()] == 3) {
            if (!player->isAttacking())
                player->attacking(enemyList->get(i), 1, 1);
        }
    }
}

void Game::draw() {
    drawMap();

    for (int i = 0; i < enemyList->length(); ++i) {
        enemyList->get(i)->draw();
    }
    player->draw();
}

void Game::createPlayers() {

}

void Game::drawMap() {
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 21; ++j) {

            if (map[j][i] == 1){
                al_draw_bitmap_region(tiles, 50 * 1, 50 * 4, 50, 50,
                                      50 * i, 50 * j, 0);
            }
            else{
                al_draw_bitmap_region(tiles, 50 * 1, 50 * 2, 50, 50,
                                      50 * i, 50 * j, 0);
            }
        }
    }
}

void Game::createMap() {
    std::srand(std::time(0));
    int random, enemys = 4;

    for (int dj = 0; dj < 21; dj++) {
        for (int di = 0; di < 27; di++) {
            random = std::rand() % 100;

            if(random > 90 && enemys != 0){
                map[dj][di] = 3;
                enemyList->add(new Enemy(di, dj, "../resources/enemy1.png"));
                enemys -= 1;
            }
            else if (random > 81){
                map[dj][di] = 1;
            }
            else{
                map[dj][di] = 0;
            }
        }
    }
}

Game::~Game(){
    delete player;
    delete playersList;
    delete enemyList;
    al_destroy_bitmap(tiles);
}