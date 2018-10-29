#include <allegro5/allegro.h>
#include <ctime>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player *>;
    enemyList = new LinkedList<Enemy *>;
    swordList = new LinkedList<Sword *>;
    bulletList = new LinkedList<Bullet *>;
    explosionList = new LinkedList<Explosion *>;

    //player = new Player("../resources/hetalia.png");
    tiles = al_load_bitmap("../resources/medievaltiles.png");
    x = 0;
    y = 0;
    animationTimer = 0;
    currentAttack = 2;
    level = 1;

    createMap();

    dij = Dijkstra(map);// A esta clase nadamas se le debe pazar la matriz del mapa al iniciarla
}

void Game::update() {
    if (level == 1 && animationTimer % 25 == 0)
        movement1();

    animationTimer++;

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
    int xPlayer, yPlayer;

    this->x = x;
    this->y = y;

    for (int i = 0; i < playersList->length(); i++)
    {
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        playersList->get(i)->setDij(map);

        xPlayer = playersList->get(i)->getPosx();//posicion actual del jugador
        yPlayer = playersList->get(i)->getPosy();

        //define los pesos a partir del nodo que se clickeo
        playersList->get(i)->getDij()->definirPesos(x,y);
        //define la ruta desde el la posicion inicial del personaje
        playersList->get(i)->getDij()->definirRutaOptima(xPlayer,yPlayer);
    }
}

void Game::movement1() {
    for (int i = 0; i < playersList->length(); ++i) {
        int nextX, nextY;

        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        Dijkstra *finder = playersList->get(i)->getDij();

        if (finder != nullptr){
            int lastX = playersList->get(i)->getPosx(), lastY = playersList->get(i)->getPosy();

            Vertice next = finder->obtenerSiguienteVertice();//obtiene el siguiente nodo al que debe avanzar
            nextX = (next.posicionXtiles) * 50;
            nextY = (next.posicionYtiles) * 50;
            
        } else {
            nextX = playersList->get(i)->getPosx() * 50;
            nextY = playersList->get(i)->getPosy() * 50;
        }

        if(nextX != -50) {
            playersList->get(i)->update(nextX, nextY);
        }
        else {
            playersList->get(i)->update(x * 50, y * 50);
        }

        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 2;
    }
}

/**
 * Metodo que hace el ataque 1 de los soldados.
 */
void Game::attack1() {
    for (int r = 0; r < playersList->length(); ++r) {
        for (int i = 0; i < enemyList->length(); i++) {
            int playerY = playersList->get(r)->getPosy();
            int playerX = playersList->get(r)->getPosx();

            if (map[playerY][playerX - 1] == 3) {
                if (!playersList->get(r)->isAttacking()) {
                    playersList->get(r)->attacking();
                    swordList->add(new Sword(searchEnemy(playerX - 1, playerY), (playerX - 1) * 50, playerY * 50, 3, 0));
                }
            }
            else if (map[playerY][playerX + 1] == 3) {
                if (!playersList->get(r)->isAttacking()){
                    playersList->get(r)->attacking();
                    swordList->add(new Sword(searchEnemy(playerX + 1, playerY), (playerX + 1) * 50, playerY * 50, 1, 0));
                }
            }
            else if (map[playerY - 1][playerX] == 3) {
                if (!playersList->get(r)->isAttacking()){
                    playersList->get(r)->attacking();
                    swordList->add(new Sword(searchEnemy(playerX, playerY - 1), playerX * 50, (playerY - 1) * 50, 3, 1));
                }
            }
            else if (map[playerY + 1][playerX] == 3) {
                if (!playersList->get(r)->isAttacking()){
                    playersList->get(r)->attacking();
                    swordList->add(new Sword(searchEnemy(playerX, playerY + 1), playerX * 50, (playerY + 1) * 50, 1, 1));
                }
            }
        }
    }
}

void Game::attack2() {
    for (int r = 0; r < playersList->length(); ++r) {
        for (int i = 0; i < enemyList->length(); i++) {
            int playerY = playersList->get(r)->getPosy();
            int playerX = playersList->get(r)->getPosx();

            //Rango de disparo.
            for (int j = 0; j < 5; ++j) {
                if (map[playerY][playerX - (j + 1)] == 3) {
                    if (!playersList->get(r)->isAttacking()) {
                        playersList->get(r)->attacking();
                        bulletList->add(new Bullet(playersList->get(r), (playerX - 5)* 50, playerY * 50));
                    }
                }
                else if (map[playerY][playerX + j] == 3) {
                    if (!playersList->get(r)->isAttacking()){
                        playersList->get(r)->attacking();
                        bulletList->add(new Bullet(playersList->get(r), (playerX + 5)* 50, playerY * 50));
                    }
                }
                else if (map[playerY - (j + 1)][playerX] == 3) {
                    if (!playersList->get(r)->isAttacking()) {
                        playersList->get(r)->attacking();
                        bulletList->add(new Bullet(playersList->get(r), playerX * 50, (playerY - 5) * 50));
                    }
                }
                else if (map[playerY + j][playerX] == 3) {
                    if (!playersList->get(r)->isAttacking()){
                        playersList->get(r)->attacking();
                        bulletList->add(new Bullet(playersList->get(r), playerX * 50, (playerY + 5) * 50));
                    }
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

    //player->draw();
    for (int m = 0; m < playersList->length(); m++) {
        playersList->get(m)->draw();
    }

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
            else if ((di == 19 && dj == 15) || (di == 20 && dj == 15) || (di == 21 && dj == 15)){
                map[dj][di] = 2;
                playersList->add(new Player(di * 50, dj * 50, "../resources/hetalia.png"));
                //player = new Player(di * 50, dj * 50, "../resources/hetalia.png");
            }
            else if (random > 83){
                map[dj][di] = 1;
            }
            else{
                map[dj][di] = 0;
            }
        }
    }
}

void Game::printM() {
    cout << "[ ";
    for (int j = 0; j < 21; j++) {
        cout << "[";
        for (int i = 0; i < 27; ++i) {
            cout << map[j][i] << ", ";
        }
        cout << "]" << endl;
    }
    cout << " ]\n\n" << endl;

}

Game::~Game(){
    delete playersList;
    delete enemyList;
    delete explosionList;
    delete swordList;
    delete bulletList;
    al_destroy_bitmap(tiles);
}