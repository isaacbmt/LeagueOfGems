#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_draw.h>
#include <iostream>
#include "Enemy.h"

Enemy::Enemy(std::string path) {
    image = al_load_bitmap(path.c_str());
}

Enemy::Enemy(int x, int y, std::string path) {
    image = al_load_bitmap(path.c_str());
    this->posx = x;
    this->posy = y;
}

void Enemy::update(int dx, int dy) {
    posx = dx;
    posy = dy;
}

void Enemy::draw() {
    al_draw_bitmap_region(image, 50 * 0, 50 * 0, 50, 50, posx * 50, posy * 50, 0);
}

void Enemy::getDamage() {
    life -= 1;
}

Enemy::~Enemy() {
    al_destroy_bitmap(image);
}
