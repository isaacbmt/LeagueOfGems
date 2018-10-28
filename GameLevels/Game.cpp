#include <allegro5/allegro.h>
#include <ctime>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player *>;
    enemyList = new LinkedList<Enemy *>;
    swordList = new LinkedList<Sword *>;
    bulletList = new LinkedList<Bullet *>;
    explosionList = new LinkedList<Explosion *>;

    player = new Player("../resources/hetalia.png");
    tiles = al_load_bitmap("../resources/medievaltiles.png");
    animationTimer = 0;
    currentAttack = 2;
    level = 1;

    createMap();

    dij = Dijkstra(map);// A esta clase nadamas se le debe pazar la matriz del mapa al iniciarla
}

void Game::update(int x, int y) {
    int nextX, nextY;

    if (animationTimer % 15 == 0) {
        Vertice next = dij.obtenerSiguienteVertice();//obtiene el siguiente nodo al que debe avanzar
        nextX = (next.posicionXtiles) * 50;
        nextY = (next.posicionYtiles) * 50;
    } else {
        nextX = player->getPosx() * 50;
        nextY = player->getPosy() * 50;
    }

    animationTimer++;

    if(nextX != -50) {
        player->update(nextX, nextY);
    } else {
        player->update(x * 50, y * 50);
    }

    if (currentAttack == 1)
        attack1();
    else if (currentAttack == 2)
        attack2();

    for (int i = 0; i < swordList->length(); ++i) {
        if (!swordList->get(i)->isAttacking())
            swordList->remove(i);
    }

    for (int j = 0; j < explosionList->length(); ++j) {
        if (explosionList->get(j)->getPivotY() == 2)
            explosionList->remove(j);
    }

    for (int l = 0; l < bulletList->length(); ++l) {
        if (bulletList->get(l)->getTimer() == 1)
            bulletList->remove(l);
        else if (map[bulletList->get(l)->getY() / 50][bulletList->get(l)->getX() / 50] == 3){
            Enemy * tmp = searchEnemy(bulletList->get(l)->getX() / 50, bulletList->get(l)->getY() / 50);
            if (tmp != nullptr)
                tmp->getDamage();
            bulletList->remove(l);
        }
    }

    //Busca los enemigos muertos
    for (int k = 0; k < enemyList->length(); ++k) {
        if (enemyList->get(k)->getLife() <= 0){
            int enemyX = enemyList->get(k)->getPosx();
            int enemyY = enemyList->get(k)->getPosy();

            map[enemyY][enemyX] = 0;
            explosionList->add(new Explosion(enemyX, enemyY));
            enemyList->remove(k);
        }
    }
}

void Game::updateCenter(int x, int y){
    int xPlayer,yPlayer;
    xPlayer = player->getPosx();//posicion actual del jugador
    yPlayer = player->getPosy();
    dij.definirPesos(x,y);//define los pesos a partir del nodo que se clickeo
    dij.definirRutaOptima(xPlayer,yPlayer);//define la ruta desde el la posicion inicial del personaje
}

/**
 * Metodo que hace el ataque 1 de los soldados.
 */
void Game::attack1() {
    for (int i = 0; i < enemyList->length(); i++) {
        int playerY = player->getPosy();
        int playerX = player->getPosx();

        if (map[playerY][playerX - 1] == 3) {
            if (!player->isAttacking()) {
                player->attacking();
                swordList->add(new Sword(searchEnemy(playerX - 1, playerY), (playerX - 1) * 50, playerY * 50, 3, 0));
            }
        }
        else if (map[playerY][playerX + 1] == 3) {
            if (!player->isAttacking()){
                player->attacking();
                swordList->add(new Sword(searchEnemy(playerX + 1, playerY), (playerX + 1) * 50, playerY * 50, 1, 0));
            }
        }
        else if (map[playerY - 1][playerX] == 3) {
            if (!player->isAttacking()){
                player->attacking();
                swordList->add(new Sword(searchEnemy(playerX, playerY - 1), playerX * 50, (playerY - 1) * 50, 3, 1));
            }
        }
        else if (map[playerY + 1][playerX] == 3) {
            if (!player->isAttacking()){
                player->attacking();
                swordList->add(new Sword(searchEnemy(playerX, playerY + 1), playerX * 50, (playerY + 1) * 50, 1, 1));
            }
        }
    }
}

void Game::attack2() {
    for (int i = 0; i < enemyList->length(); i++) {
        int playerY = player->getPosy();
        int playerX = player->getPosx();

        //Rango de disparo.
        for (int j = 0; j < 5; ++j) {
            if (map[playerY][playerX - (j + 1)] == 3) {
                if (!player->isAttacking()) {
                    player->attacking();
                    bulletList->add(new Bullet(player, (playerX - 5)* 50, playerY * 50));
                }
            }
            else if (map[playerY][playerX + j] == 3) {
                if (!player->isAttacking()){
                    player->attacking();
                    bulletList->add(new Bullet(player, (playerX + 5)* 50, playerY * 50));
                }
            }
            else if (map[playerY - (j + 1)][playerX] == 3) {
                if (!player->isAttacking()) {
                    player->attacking();
                    bulletList->add(new Bullet(player, playerX * 50, (playerY - 5) * 50));
                }
            }
            else if (map[playerY + j][playerX] == 3) {
                if (!player->isAttacking()){
                    player->attacking();
                    bulletList->add(new Bullet(player, playerX * 50, (playerY + 5) * 50));
                }
            }
        }
    }
}

Enemy *Game::searchEnemy(int x, int y) {
    for (int i = 0; i < enemyList->length(); ++i) {
        if (enemyList->get(i)->getPosx() == x && enemyList->get(i)->getPosy() == y){
            return enemyList->get(i);
        }
    }

    return nullptr;
}

void Game::draw() {
    drawMap();

    player->draw();

    for (int i = 0; i < enemyList->length(); i++) {
        if (enemyList->get(i) != nullptr) {
            enemyList->get(i)->draw();
        }
    }

    for (int j = 0; j < explosionList->length(); j++) {
        explosionList->get(j)->draw();
    }

    for (int k = 0; k < swordList->length(); k++) {
        swordList->get(k)->draw();
    }

    for (int l = 0; l < bulletList->length(); ++l) {
        bulletList->get(l)->draw();
    }

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

            if(random > 90 && enemys != 0 && dj != 0){
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
    delete explosionList;
    delete swordList;
    delete bulletList;
    al_destroy_bitmap(tiles);
}