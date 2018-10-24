#include <allegro5/allegro.h>
#include <ctime>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player>;
    player = new Player("../resources/hetalia.png");

    std::srand(std::time(0));
    int random;

    for (int dj = 0; dj < 21; dj++) {
        for (int di = 0; di < 27; di++) {
            random = std::rand() % 100;

            if (random > 84){
                map[dj][di] = 1;
            }
            else{
                map[dj][di] = 0;
            }
        }
    }
}

void Game::update(int x, int y) {
    player->update(x, y);
}

void Game::draw() {
    createMap();
    player->draw();
}

void Game::createPlayers() {

}

void Game::createMap() {
    ALLEGRO_BITMAP *tiles = al_load_bitmap("../resources/medievaltiles.png");

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

Game::~Game(){
    delete player;
    delete playersList;
}