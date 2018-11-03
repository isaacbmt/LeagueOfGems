#include "Laser.h"

Laser::Laser(int xi, int yi, int direction, Enemy *enemy) {
    this->laser = al_load_bitmap("../resources/laserRed.png");
    this->enemy = enemy;
    this->xi = xi;
    this->yi = yi;
    this->direction = direction;
    this->pivot = 0;
    this->isAttacking = true;
    enemy->startAttack();
}

void Laser::draw() {
    float large = 35.7143;

    //Derecha
    if (direction == 0)
        al_draw_bitmap_region(laser, 0, large * pivot, 250, large, xi + 50, yi + 15, 0);
    //Izquierda
    else if (direction == 1)
        al_draw_bitmap_region(laser, 0, large * pivot, 250, large, xi - 250, yi + 15, 0);
    //Arriba
    else if (direction == 2)
        al_draw_bitmap_region(laser, 250 + large * pivot, 0, large, 250, xi + 15, yi - 250, 0);
    //Abajo
    else if (direction == 3)
        al_draw_bitmap_region(laser, 250 + large * pivot, 0, large, 250, xi + 15, yi + 15, 0);

    animationTimer++;
    if (animationTimer % 10 == 0) {
        pivot++;
        if (pivot == 6)
            pivot = 0;
    }

}

bool Laser::damage(Player *player) {
    int playerX = player->getPosx();
    int playerY = player->getPosy();

    for (int i = 0; i < 6; ++i) {
        if (direction == 0 && xi / 50 + i == playerX && playerY == yi / 50) {
            player->getDamage();
            isAttacking = true;
        }
        else if (direction == 1 && xi / 50 - (i + 1) == playerX && playerY == yi / 50) {
            player->getDamage();
            isAttacking = true;
        }
        else if (direction == 2 && xi / 50 == playerX && yi / 50 - (i + 1) == playerY) {
            player->getDamage();
            isAttacking = true;
        }
        else if (direction == 3 && xi / 50 == playerX && yi / 50 + i == playerY) {
            player->getDamage();
            isAttacking = true;
        }
        else {
            isAttacking = false;
        }
    }
    return isAttacking;
}

Enemy *Laser::getEnemy() {
    return enemy;
}

Laser::~Laser() {
    al_destroy_bitmap(laser);
}
