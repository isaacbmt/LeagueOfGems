#include <allegro5/allegro.h>
#include <ctime>
#include "Game.h"

Game::Game() {
    playersList = new LinkedList<Player *>;
    enemyList = new LinkedList<Enemy *>;
    swordList = new LinkedList<Sword *>;
    bulletList = new LinkedList<Bullet *>;
    explosionList = new LinkedList<Explosion *>;
    laserList = new LinkedList<Laser *>;
    gemList = new LinkedList<Gem *>;

    //player = new Player("../resources/hetalia.png");
    tiles = al_load_bitmap("../resources/medievaltiles.png");
    icon1 = al_load_bitmap("../resources/icon1.png");
    icon2 = al_load_bitmap("../resources/icon2.png");
    icon3 = al_load_bitmap("../resources/icon3.png");
    icon4 = al_load_bitmap("../resources/icon4.png");

    x = 0;
    y = 0;
    animationTimer = 0;
    currentAttack = 3;
    level = 1;

    createFirstMap();

    dij = Dijkstra(map);// A esta clase nadamas se le debe pasar la matriz del mapa al iniciarla
}

void Game::update() {
    int tmpLevel = level;

    if (level == 1 && animationTimer % 25 == 0)
        movement1();
    else if (level == 2 && animationTimer % 25 == 0)
        movement2();
    else if (level == 3 && animationTimer % 25 == 0)
        movement3();

    animationTimer++;

    if (currentAttack == 1)
        attack1();
    else if (currentAttack == 2)
        attack2();
    else if (currentAttack == 3 && animationTimer % 250 == 0)
        attack3();

    enemysAttacks();

    if (animationTimer % 28 == 0) {
        for (int i = 0; i < laserList->length(); ++i) {
            bool isAttacking = false;

            for (int j = 0; j < playersList->length(); ++j) {
                if (laserList->get(i)->damage(playersList->get(j)))
                    isAttacking = true;
            }

            if (!isAttacking) {
                laserList->get(i)->getEnemy()->endAttack();
                laserList->remove(i);
            }
        }
    }

    bool flag = true;
    for (int k = 0; k < playersList->length(); k++) {
        for (int i = 0; i < level; i++) {
            if (gemList->get(i)->getPosx() == playersList->get(k)->getPosx()
            && gemList->get(i)->getPosy() == playersList->get(k)->getPosy() && !gemList->get(i)->isAcquired) {
                gemList->get(i)->isAcquired = true;
                level++;
                flag = false;
                break;
            }
        }
        if (!flag)
            break;
    }

    deleteObjectInGame();

    if (level != tmpLevel) {
        createNextMap();
    }
}

void Game::updateCenter(int x, int y){
    bool izq = false, der = false, aba = false, arr = false;
    if (x >= 6)
        izq = true;
    else if (x < 6)
        der = true;

    if (y > 16)
        arr = true;
    else if (y <= 16)
        aba = true;

    if (level == 1)
        updateLevel1(x, y, arr, aba, der, izq);
    else if (level == 2)
        updateLevel2(x, y, arr, aba, der, izq);
    else if (level == 3)
        updateLevel3(x, y, arr, aba, der, izq);
}

void Game::updateLevel1(int x, int y, bool arr, bool aba, bool der, bool izq) {
    int xPlayer, yPlayer;
    this->x = x;
    this->y = y;
    int tx = x, column = 0;

    for (int i = 0; i < playersList->length(); i++) {
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        playersList->get(i)->setMapOnGreedy(map);

        xPlayer = playersList->get(i)->getPosx();//posicion actual del jugador
        yPlayer = playersList->get(i)->getPosy();

        bool flag = true;
        while (flag) {
            playersList->get(i)->getDij()->definirPesos(x, y + column);

            if (playersList->get(i)->getDij()->definirRutaOptima(xPlayer, yPlayer) == 1) {
                playersList->get(i)->targetX = x;
                playersList->get(i)->targetY = y + column;
                flag = false;
            }
            if (izq) {
                x--;
            }
            else if (der) {
                x++;
            }
        }
        if ((i + 1) % 5 == 0) {
            x = tx;
            if (aba)
                column++;
            else if (arr)
                column--;
        }
    }
}

void Game::updateLevel3(int x, int y, bool arr, bool aba, bool der, bool izq) {
    int xPlayer, yPlayer;
    bool flag;
    this->x = x;
    this->y = y;
    int tx = x, column = 0;

    for (int i = 0; i < playersList->length(); i++) {
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;
        playersList->get(i)->setMapOnGreedy(map);

        xPlayer = playersList->get(i)->getPosx();
        yPlayer = playersList->get(i)->getPosy();

        flag = true;
        while(flag) {
            if (map[y + column][x] == 0) {
                playersList->get(i)->getKruskal()->definirCamino(x, y + column, xPlayer, yPlayer);
                playersList->get(i)->targetX = x;
                playersList->get(i)->targetY = y + column;
                flag = false;
            }
            if (izq) {
                x--;
            }
            else if (der) {
                x++;
            }
        }
        if ((i + 1) % 5 == 0) {
            x = tx;
            if (aba)
                column++;
            else if (arr)
                column--;
        }
    }

}

void Game::updateLevel2(int x, int y, bool arr, bool aba, bool der, bool izq) {
    int tx = x, column = 0;

    for (int i = 0; i < playersList->length(); ++i) {
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        bool flag = true;

        while (flag){
            if (map[y + column][x] == 0) {
                MapSearchNode nodeEnd;
                nodeEnd.x = x;
                nodeEnd.y = y + column;

                playersList->get(i)->setAstar(map, nodeEnd);
                playersList->get(i)->targetX = x;
                playersList->get(i)->targetY = y  + column;
                playersList->get(i)->aIndex = 0;
                flag = false;
            }

            if (izq)
                x--;
            else if (der)
                x++;
        }

        if ((i + 1) % 5 == 0) {
            x = tx;
            if (aba)
                column++;
            else if (arr)
                column--;
        }
    }
}

void Game::movement1() {
    for (int i = 0; i < playersList->length(); ++i) {
        int nextX , nextY;

        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        Dijkstra *finder = playersList->get(i)->getDij();

        if (finder != nullptr) {
            Vertice next = finder->obtenerSiguienteVertice();//obtiene el siguiente nodo al que debe avanzar
            nextX = (next.posicionXtiles) * 50;
            nextY = (next.posicionYtiles) * 50;
        }
        else {
            nextX = playersList->get(i)->getPosx() * 50;
            nextY = playersList->get(i)->getPosy() * 50;
        }

        if(nextX != -50) {
            playersList->get(i)->update(nextX, nextY);
        }
        else {
            playersList->get(i)->update(playersList->get(i)->targetX * 50, playersList->get(i)->targetY * 50);
        }

        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 2;
    }
}

void Game::movement3() {
    for (int i = 0; i < playersList->length(); i++) {
        int nextX, nextY;
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        Kruskal *finder = playersList->get(i)->getKruskal();

        if (finder != nullptr) {
            Nodo next = finder->obtenerSiguienteVertice();
            nextX = (next.posicionX) * 50;
            nextY = (next.posicionY) * 50;
        }
        else {
            nextX = playersList->get(i)->getPosx() * 50;
            nextY = playersList->get(i)->getPosy() * 50;
        }

        if(nextX != -50) {
            playersList->get(i)->update(nextX, nextY);
        }
        else {
            playersList->get(i)->update(playersList->get(i)->targetX * 50, playersList->get(i)->targetY * 50);
        }

        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 2;
    }
}

void Game::movement2() {
    for (int i = 0; i < playersList->length(); ++i) {
        int nextX, nextY;
        map[playersList->get(i)->getPosy()][playersList->get(i)->getPosx()] = 0;

        if (playersList->get(i)->aIndex < playersList->get(i)->getAstar().size()) {
            nextX = playersList->get(i)->getAstar()[playersList->get(i)->aIndex].x * 50;
            nextY = playersList->get(i)->getAstar()[playersList->get(i)->aIndex].y * 50;
        } else {
            nextX = playersList->get(i)->getPosx() * 50;
            nextY = playersList->get(i)->getPosy() * 50;
        }

        if (playersList->get(i)->aIndex >= playersList->get(i)->getAstar().size()) {
            playersList->get(i)->update(playersList->get(i)->targetX * 50, playersList->get(i)->targetY * 50);
        } else {
            playersList->get(i)->update(nextX, nextY);
        }

        playersList->get(i)->aIndex++;
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

void Game::enemysAttacks() {
    for (int i = 0; i < enemyList->length(); ++i) {
        for (int j = 0; j < playersList->length(); ++j) {
            int robotX = enemyList->get(i)->getPosx();
            int robotY = enemyList->get(i)->getPosy();

            for (int k = 0; k < 6; ++k) {
                if (map[robotY][robotX + k] == 2){
                    if (!enemyList->get(i)->isAttacking()) {
                        laserList->add(new Laser(robotX * 50, robotY * 50, 0, enemyList->get(i)));
                    }
                }
                if (map[robotY][robotX - (k + 1)] == 2){
                    if (!enemyList->get(i)->isAttacking()) {
                        laserList->add(new Laser(robotX * 50, robotY * 50, 1, enemyList->get(i)));
                    }
                }
                if (map[robotY - (k + 1)][robotX] == 2){
                    if (!enemyList->get(i)->isAttacking()) {
                        laserList->add(new Laser(robotX * 50, robotY * 50, 2, enemyList->get(i)));
                    }
                }
                if (map[robotY + k][robotX] == 2){
                    if (!enemyList->get(i)->isAttacking()) {
                        laserList->add(new Laser(robotX * 50, robotY * 50, 3, enemyList->get(i)));
                    }
                }
            }
        }
    }
}

void Game::attack3() {
    for (int i = 0; i < playersList->length(); ++i) {
        playersList->get(i)->heal();
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
    drawAttackIcons();

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

    for (int n = 0; n < laserList->length(); n++) {
        if (laserList->get(n) != nullptr)
            laserList->get(n)->draw();
    }

    for (int k = 0; k < swordList->length(); k++) {
        swordList->get(k)->draw();
    }

    for (int l = 0; l < bulletList->length(); ++l) {
        bulletList->get(l)->draw();
    }

    for (int g = 0; g < level; g++) {
        gemList->get(g)->draw();
    }
}

void Game::drawAttackIcons() {
    al_draw_filled_rectangle(525 + 80 * (currentAttack - 1), 1070, 525 + 80 * (currentAttack - 1) + 60, 1130,
            al_map_rgb(218,165,32));

    al_draw_bitmap(icon1, 525, 1070, 0);
    al_draw_bitmap(icon2, 605, 1070, 0);
    al_draw_bitmap(icon3, 685, 1070, 0);
    al_draw_bitmap(icon4, 765, 1070, 0);
}

void Game::createPlayers() {

}

void Game::drawMap() {
    int xObstaculo = 0, yObstaculo = 0, xTile = 0, yTile = 0;

    if (level == 1) {
        xObstaculo = 1;
        yObstaculo = 4;
        xTile = 1;
        yTile = 2;
    }
    else if (level == 2) {
        xObstaculo = 2;
        yObstaculo = 1;
        xTile = 0;
        yTile = 5;
    }
    else if (level == 3) {
        xObstaculo = 1;
        yObstaculo = 0;
        xTile = 4;
        yTile = 5;
    }

    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (map[j][i] == 1){
                al_draw_bitmap_region(tiles, 50 * xObstaculo, 50 * yObstaculo, 50, 50,
                                      50 * i, 50 * j, 0);
            }
            else{
                al_draw_bitmap_region(tiles, 50 * xTile, 50 * yTile, 50, 50,
                                      50 * i, 50 * j, 0);
            }
        }
    }
}

void Game::createFirstMap() {
    std::srand(std::time(0));
    int random, enemys = 4, players = 0;

    for (int dj = 0; dj < 21; dj++) {
        for (int di = 0; di < 27; di++) {
            random = std::rand() % 100;

            if (dj == 2 && di == 2) {
                for (int i = 0; i < 4; i++) {
                    if (i == 0)
                        gemList->add(new Gem(di, dj, 6, i, "../resources/gem" + to_string(i + 1) +".png"));
                    else if (i == 1)
                        gemList->add(new Gem(di, dj, 8, i, "../resources/gem" + to_string(i + 1) +".png"));
                    else
                        gemList->add(new Gem(di, dj, 4, i, "../resources/gem" + to_string(i + 1) +".png"));
                }
                map[dj][di] = 0;
            }
            else if(random > 90 && enemys != 0 && dj != 0) {
                map[dj][di] = 3;
                enemyList->add(new Enemy(di, dj, "../resources/enemy1.png"));
                enemys -= 1;
            }
            else if (16 < di && di < 22 && 16 < dj && dj < 20) {
                map[dj][di] = 2;
                //playersList->add(new Player(di * 50, dj * 50, "../resources/hetalia.png"));
                playersList->add(new Player(di * 50, dj * 50, "../resources/sprite" + to_string(players) + ".png"));

                playersList->get(players)->targetX = di;
                playersList->get(players)->targetY = dj;
                playersList->get(players)->initGreedy(map);
                players++;
                //player = new Player(di * 50, dj * 50, "../resources/hetalia.png");
            }
            else if (random > 88) {
                map[dj][di] = 1;
            }
            else {
                map[dj][di] = 0;
            }
        }
    }
}

void Game::createNextMap() {
    playersList->clear();
    enemyList->clear();
    laserList->clear();

    std::srand(std::time(0));
    int random, enemys = 4, players = 0;

    for (int j = 0; j < 21; j++) {
        for (int i = 0; i < 27; i++) {
            random = std::rand() % 100;

            if (i == 2 && j == 2) {
                map[j][i] = 0;
            } else if (random > 90 && enemys != 0 && j != 0) {
                map[j][i] = 3;
                enemyList->add(new Enemy(i, j, "../resources/enemy" + to_string(level) + ".png"));
                enemys -= 1;
            } else if (16 < i && i < 22 && 16 < j && j < 20) {
                map[j][i] = 2;
                //playersList->add(new Player(di * 50, dj * 50, "../resources/hetalia.png"));
                playersList->add(new Player(i * 50, j * 50, "../resources/sprite" + to_string(players) + ".png"));

                playersList->get(players)->targetX = i;
                playersList->get(players)->targetY = j;
                playersList->get(players)->initGreedy(map);
                players++;
            }
            else if (random > 88) {
                map[j][i] = 1;
            }
            else {
                map[j][i] = 0;
            }
        }
    }
}

void Game::setCurrentAttack(int current) {
    if (currentAttack != current) {
        if (currentAttack == 3 && current != 3) {
            for (int i = 0; i < playersList->length(); ++i) {
                playersList->get(i)->stopHeal();
            }
        }
        currentAttack = current;
        cout << "Ataque actual: " << currentAttack << endl;
    }
}

void Game::deleteObjectInGame() {
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
        int enemyX = enemyList->get(k)->getPosx();
        int enemyY = enemyList->get(k)->getPosy();
        map[enemyY][enemyX] = 3;

        if (enemyList->get(k)->getLife() <= 0){
            map[enemyY][enemyX] = 0;
            explosionList->add(new Explosion(enemyX, enemyY));
            enemyList->remove(k);
        }
    }

    for (int m = 0; m < playersList->length(); ++m) {
        if (playersList->get(m)->getLife() <= 0){
            int playerX = playersList->get(m)->getPosx();
            int playerY = playersList->get(m)->getPosy();

            map[playerY][playerX] = 0;
            playersList->remove(m);
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
    delete laserList;
    delete gem;
    al_destroy_bitmap(tiles);
}