#include <allegro5/allegro.h>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player>;
    player = new Player("../resources/sprite.png");
}

void Game::update() {

}

void Game::draw(int x, int y) {
    createMap();

    player->draw(x, y);

}

void Game::createPlayers() {

}

void Game::createMap() {
    int map[21][27];
    for (int dj = 0; dj < 21; dj++) {
        for (int di = 0; di < 27; di++) {
            map[dj][di] = 0;
        }
    }

    ALLEGRO_BITMAP *tiles = al_load_bitmap("../resources/tiles2.png");

    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 21; ++j) {
            al_draw_bitmap_region(tiles, 50 * 3, 50 * 1 + 4, 50, 50,
                    50 * i, 50 * j, 0);
        }
    }
}

Game::~Game(){
    delete player;
    delete playersList;
}