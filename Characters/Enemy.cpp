#include <iostream>
#include "Enemy.h"

Enemy::Enemy(std::string path) {
    image = al_load_bitmap(path.c_str());
}

Enemy::Enemy(int x, int y, std::string path) {
    image = al_load_bitmap(path.c_str());
    this->posx = x;
    this->posy = y;
    this->maxLife = 50;
    this->life = 50;
}

void Enemy::update(int dx, int dy) {
    posx = dx;
    posy = dy;
}

void Enemy::draw() {
    al_draw_rectangle(posx * 50 , posy * 50 - 7, posx * 50 + maxLife, posy * 50 - 2, al_map_rgb(255, 0, 0), 1.0);
    al_draw_filled_rectangle(posx * 50 , posy * 50 - 7, posx * 50 + life, posy * 50 - 2, al_map_rgb(255, 0, 0));

    al_draw_bitmap_region(image, 50 * 0, 50 * 0, 50, 50, posx * 50, posy * 50, 0);
}

void Enemy::getDamage() {
    life -= 4;
}

Enemy::~Enemy() {
    al_destroy_bitmap(image);
}

int Enemy::getLife() {
    return life;
}

int Enemy::getPosx() {
    return posx;
}

int Enemy::getPosy() {
    return posy;
}
